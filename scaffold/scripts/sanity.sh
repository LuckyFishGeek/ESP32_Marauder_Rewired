#!/usr/bin/env bash
# Sanity checks for CSV configs and partitions
# Usage: ./scaffold/scripts/sanity.sh
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

pass()  { printf "[OK]   %s\n"  "$*"; }
warn()  { printf "[WARN] %s\n" "$*" >&2; }
fail()  { printf "[ERR]  %s\n" "$*" >&2; exit 1; }

normalize_crlf() {
  local f="$1"
  [ -f "$f" ] || fail "Missing file: $f"
  sed -i 's/\r$//' "$f" || true
}

require_header_starts_with() {
  local f="$1" expect="$2"
  local hdr
  hdr="$(head -n1 "$f" | tr -d '[:space:]' | tr '[:upper:]' '[:lower:]')"
  if [[ "$hdr" == $expect* ]]; then
    pass "Header OK: $(basename "$f") starts with '$expect'"
  else
    fail "$(basename "$f") header invalid. Saw: '$(head -n1 "$f")'  Expected to start with: '$expect'"
  fi
}

list_first_col() {
  local f="$1" title="$2"
  echo "$title"
  tail -n +2 "$f" | cut -d',' -f1 | nl -ba || true
}

check_exists_and_nonempty() {
  local f="$1"
  [ -f "$f" ] || fail "Missing file: $f"
  [ -s "$f" ] || fail "Empty file: $f"
  pass "Exists: $f"
}

# ---- Paths to check ----
BOARDS_CSV="$ROOT/scaffold/configs/boards_manifest.csv"
LIBS_CSV="$ROOT/scaffold/configs/lib_list.csv"
MODULES_CSV="$ROOT/scaffold/configs/modules_presets.csv"
PINS_CSV="$ROOT/scaffold/configs/pins/pins_presets.csv"
DISPLAYS_CSV="$ROOT/scaffold/configs/displays/display_presets.csv"
BUILD_CSV="$ROOT/scaffold/configs/build_defines.csv"

PART_DIR="$ROOT/partitions"
PARTS=(
  "$PART_DIR/hugeapp_1m_fs.csv"
  "$PART_DIR/marauder_default.csv"
  "$PART_DIR/marauder_littlefs.csv"
  "$PART_DIR/marauder_spiffs_ota.csv"
  "$PART_DIR/min_littlefs_ota.csv"
  "$PART_DIR/min_spiffs_ota.csv"
  "$PART_DIR/ota_1m_fs.csv"
  # --- new additions ---
  "$PART_DIR/app_2m_fs_2m.csv"
  "$PART_DIR/ota_dual_1m_1m.csv"
  "$PART_DIR/wifi_capture_bigfs.csv"
)

echo "=== CSV Sanity ==="

# Boards manifest
check_exists_and_nonempty "$BOARDS_CSV"
normalize_crlf "$BOARDS_CSV"
require_header_starts_with "$BOARDS_CSV" "board_label,fqbn"
list_first_col "$BOARDS_CSV" "Boards detected:"

# Soft-check board rows (warn if profile missing/empty)
awk -F',' 'NR==1{next}
{
  label=$1; prof=$6;
  if (prof=="" || prof ~ /^[[:space:]]*$/) {
    printf("[WARN] board \"%s\" has empty profile column (col 6); workflow may fallback.\n", label) > "/dev/stderr"
  }
}' "$BOARDS_CSV"

# Libraries list (allow either `zip` or `zip,desc`)
check_exists_and_nonempty "$LIBS_CSV"
normalize_crlf "$LIBS_CSV"
lib_hdr="$(head -n1 "$LIBS_CSV" | tr -d '[:space:]' | tr '[:upper:]' '[:lower:]')"
if [[ "$lib_hdr" == "zip" || "$lib_hdr" == "zip,desc" ]]; then
  pass "Header OK: $(basename "$LIBS_CSV") = '$lib_hdr'"
else
  warn "Unexpected header in $(basename "$LIBS_CSV"): '$(head -n1 "$LIBS_CSV")' (expected 'zip' or 'zip,desc')"
fi
list_first_col "$LIBS_CSV" "Library ZIP entries:"

# Modules presets
check_exists_and_nonempty "$MODULES_CSV"
normalize_crlf "$MODULES_CSV"
require_header_starts_with "$MODULES_CSV" "profilename,modules"
list_first_col "$MODULES_CSV" "Module profiles:"

# Pins presets (optional)
if [ -f "$PINS_CSV" ]; then
  normalize_crlf "$PINS_CSV"
  if [ -s "$PINS_CSV" ]; then
    pass "Pins CSV present and non-empty: $PINS_CSV"
    echo "Pins header: $(head -n1 "$PINS_CSV")"
  else
    warn "Pins CSV exists but is empty: $PINS_CSV"
  fi
else
  warn "Pins CSV not found (optional): $PINS_CSV"
fi

# Display presets
check_exists_and_nonempty "$DISPLAYS_CSV"
normalize_crlf "$DISPLAYS_CSV"
require_header_starts_with "$DISPLAYS_CSV" "profile,model,header,defines"
list_first_col "$DISPLAYS_CSV" "Display profiles:"

# build_defines.csv (optional) ? accept either schema
if [ -f "$BUILD_CSV" ]; then
  normalize_crlf "$BUILD_CSV"
  b_hdr="$(head -n1 "$BUILD_CSV" | tr -d '[:space:]' | tr '[:upper:]' '[:lower:]')"
  case "$b_hdr" in
    token,define*|key,value* )
      pass "Header OK: $(basename "$BUILD_CSV") = '$b_hdr'"
      ;;
    * )
      warn "Unexpected header in $(basename "$BUILD_CSV"): '$(head -n1 "$BUILD_CSV")' (expected 'token,define' or 'key,value')"
      ;;
  esac
else
  warn "Optional CSV not found (skipping): $BUILD_CSV"
fi

# Partition CSVs ? light validation
echo "=== Partition CSVs ==="
for f in "${PARTS[@]}"; do
  if [ ! -f "$f" ]; then
    fail "Missing partition CSV: $f"
  fi
  normalize_crlf "$f"
  # Require at least one non-comment, non-empty line with 5+ fields
  if awk -F',' '
      BEGIN{ok=0}
      /^[[:space:]]*#/ {next}
      /^[[:space:]]*$/ {next}
      { if (NF>=5) ok=1 }
      END{ exit(ok?0:1) }
    ' "$f"; then
    pass "Partition CSV looks sane: $(basename "$f")"
  else
    warn "Partition CSV might be malformed: $(basename "$f")"
  fi
done

echo "=== Sanity complete ==="
