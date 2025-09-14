#!/usr/bin/env bash
# scaffold/scripts/sanity.sh
set -euo pipefail

RED=$'\e[31m'; GRN=$'\e[32m'; YLW=$'\e[33m'; RST=$'\e[0m'
err(){ echo "${RED}ERROR:${RST} $*" >&2; }
warn(){ echo "${YLW}WARN:${RST}  $*" >&2; }
ok(){ echo "${GRN}OK:${RST}    $*"; }

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

# ---- Required paths ----
CSV="$ROOT/scaffold/configs/boards_manifest.csv"
PART_DIR="$ROOT/partitions"
DISP_DIR_1="$ROOT/scaffold/displays"                 # if you store headers here
DISP_DIR_2="$ROOT/scaffold/configs/displays"         # or here (e.g. with presets)
DISP_USERSETUPS_SUB="User_Setups"                    # common subdir name

[ -f "$CSV" ] || { err "Missing $CSV"; exit 1; }

# ---- BOM/CRLF checks (no auto-fix, just report) ----
MAGIC="$(head -c 3 "$CSV" | od -An -tx1 | tr -d ' \n' || true)"
if [[ "$MAGIC" == "efbbbf" ]]; then
  err "UTF-8 BOM detected in boards_manifest.csv. Remove BOM."
  exit 1
fi
if grep -q $'\r' "$CSV"; then
  err "CRLF line endings detected in boards_manifest.csv. Convert to LF."
  exit 1
fi
ok "boards_manifest.csv has no BOM and uses LF"

# ---- Header validation ----
HDR="$(head -n1 "$CSV" | tr -d '[:space:]' | tr '[:upper:]' '[:lower:]')"
EXP="board_label,fqbn,flag,filesystem,partition,profile,tft_enabled,tft_header,core_version"
if [[ "$HDR" != "$(echo "$EXP" | tr -d '[:space:]')" ]]; then
  err "Header mismatch.
  Saw:    $(head -n1 "$CSV")
  Expect: $EXP"
  exit 1
fi
ok "Header matches expected columns"

# ---- Per-row validation ----
declare -A SEEN
row=1
errors=0

# shellcheck disable=SC2162
tail -n +2 "$CSV" | while IFS=',' read -r LABEL FQBN FLAG FS PART PROFILE TFT_ENABLED TFT_HEADER CORE_VER; do
  row=$((row+1))
  loc="row $row (label='$LABEL')"

  # Basic presence
  if [[ -z "$LABEL" ]]; then err "$loc: board_label is empty"; errors=$((errors+1)); fi
  if [[ -z "$FQBN" ]]; then err "$loc: fqbn is empty"; errors=$((errors+1)); fi
  if [[ -z "$CORE_VER" ]]; then err "$loc: core_version is empty"; errors=$((errors+1)); fi

  # Unique labels
  if [[ -n "${SEEN[$LABEL]+x}" ]]; then
    err "$loc: duplicate board_label '$LABEL'"
    errors=$((errors+1))
  else
    SEEN[$LABEL]=1
  fi

  # FQBN format (vendor:package:board[:opts...])
  if ! [[ "$FQBN" =~ ^[^:]+:[^:]+:[^:,[:space:]]+ ]]; then
    err "$loc: fqbn '$FQBN' looks invalid"
    errors=$((errors+1))
  fi

  # core_version x.y.z
  if ! [[ "$CORE_VER" =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
    err "$loc: core_version '$CORE_VER' must be x.y.z"
    errors=$((errors+1))
  fi

  # FS & partition are optional but warn if odd
  if [[ -n "$FS" ]] && ! [[ "$FS" =~ ^(spiffs|littlefs)$ ]]; then
    warn "$loc: filesystem '$FS' is unusual (expected spiffs|littlefs)"
  fi

  if [[ -n "$PART" ]]; then
    if [[ "$PART" != *.csv ]]; then
      err "$loc: partition '$PART' must end with .csv"
      errors=$((errors+1))
    elif [[ ! -f "$PART_DIR/$PART" ]]; then
      warn "$loc: partition file '$PART' not found under partitions/"
    fi
  fi

  # tft_enabled sanity
  if ! [[ "$TFT_ENABLED" =~ ^(true|false)$ ]]; then
    err "$loc: tft_enabled must be 'true' or 'false' (got '$TFT_ENABLED')"
    errors=$((errors+1))
  fi

  # If tft_enabled=true, a header must be present somewhere
  if [[ "$TFT_ENABLED" == "true" ]]; then
    if [[ -z "$TFT_HEADER" ]]; then
      err "$loc: tft_enabled=true but tft_header empty"
      errors=$((errors+1))
    else
      # Accepted locations for the header (relative structure you use)
      found_header=false
      for base in "$DISP_DIR_1" "$DISP_DIR_2"; do
        [[ -d "$base" ]] || continue
        if [[ -f "$base/$TFT_HEADER" ]]; then found_header=true; break; fi
        if [[ -f "$base/$DISP_USERSETUPS_SUB/$TFT_HEADER" ]]; then found_header=true; break; fi
      done
      if ! $found_header; then
        warn "$loc: tft_header '$TFT_HEADER' was not found in $DISP_DIR_1 or $DISP_DIR_2 (this is OK if provided by the zip at build time)"
      fi
    fi
  else
    # If tft_enabled=false but a header is filled, warn
    if [[ -n "$TFT_HEADER" ]]; then
      warn "$loc: tft_enabled=false but tft_header is set ('$TFT_HEADER') ? usually leave it empty"
    end
  fi

done

# consume while exit code
test ${PIPESTATUS[1]} -eq 0 || { err "Failed reading CSV"; exit 1; }

if (( errors > 0 )); then
  err "Sanity check failed with $errors error(s)."
  exit 1
fi

ok "Sanity check passed"
