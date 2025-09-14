#!/usr/bin/env bash
set -euo pipefail

# -------------------------------------------------------------------
# gen_configs_h.sh
# Generate configs.h from CSVs (boards + modules [+ pins/display])
# -------------------------------------------------------------------
# Inputs:
#   --board   "<board label>"           (required)
#   --profile "<profile name>"          (required, e.g., Minimal/Full/Custom)
#   --out     "path/to/configs.h"       (required)
#   --modules "WIFI,BLE,SD,..."         (optional, used when profile=Custom)
#   --boards  "path/to/boards_manifest.csv"      (default scaffold/configs/boards_manifest.csv)
#   --mods    "path/to/modules_presets.csv"      (default scaffold/configs/modules_presets.csv)
#   --pins    "path/to/pins/pins_presets.csv"    (optional; ignored if missing)
#   --disp    "path/to/displays/display_presets.csv" (optional; ignored if missing)
#
# Outputs:
#   A self-contained configs.h suitable for inclusion by the sketch.
# -------------------------------------------------------------------

# Defaults
BOARDS_CSV="scaffold/configs/boards_manifest.csv"
MODS_CSV="scaffold/configs/modules_presets.csv"
PINS_CSV="scaffold/configs/pins/pins_presets.csv"
DISP_CSV="scaffold/configs/pins/display_presets.csv"
BOARD_LABEL=""
PROFILE_NAME=""
OUT_PATH=""
CUSTOM_MODULES=""

# Parse args
while [[ $# -gt 0 ]]; do
  case "$1" in
    --board)   BOARD_LABEL="${2:-}"; shift 2 ;;
    --profile) PROFILE_NAME="${2:-}"; shift 2 ;;
    --out)     OUT_PATH="${2:-}"; shift 2 ;;
    --modules) CUSTOM_MODULES="${2:-}"; shift 2 ;;
    --boards)  BOARDS_CSV="${2:-}"; shift 2 ;;
    --mods)    MODS_CSV="${2:-}"; shift 2 ;;
    --pins)    PINS_CSV="${2:-}"; shift 2 ;;
    --disp)    DISP_CSV="${2:-}"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 2 ;;
  esac
done

# Required inputs
[[ -n "$BOARD_LABEL" ]] || { echo "::error ::--board is required"; exit 1; }
[[ -n "$PROFILE_NAME" ]] || { echo "::error ::--profile is required"; exit 1; }
[[ -n "$OUT_PATH"    ]] || { echo "::error ::--out is required"; exit 1; }

# Normalize line endings on the CSVs we will use (if present)
for f in "$BOARDS_CSV" "$MODS_CSV" "$PINS_CSV" "$DISP_CSV"; do
  [[ -f "$f" ]] && sed -i 's/\r$//' "$f" || true
done

# Read board row from boards_manifest.csv
[[ -f "$BOARDS_CSV" ]] || { echo "::error ::Boards CSV not found: $BOARDS_CSV"; exit 1; }

BOARD_LINE="$(awk -F',' -v want="$BOARD_LABEL" 'NR==1{next} $1==want {print; exit}' "$BOARDS_CSV")"
if [[ -z "$BOARD_LINE" ]]; then
  echo "::error ::Board not found in $BOARDS_CSV: $BOARD_LABEL"
  echo "Available:"
  tail -n +2 "$BOARDS_CSV" | cut -d',' -f1 | nl -ba
  exit 1
fi

# Expected columns (current project header):
# board_label,fqbn,flag,filesystem,partition,profile,tft_enabled,tft_header,defines,core_version
IFS=',' read -r _ FQBN BOARD_FLAG DEF_FS DEF_PART DEF_PROFILE TFT_ENABLED TFT_HEADER EXTRA_DEFINES CORE_VER <<<"$BOARD_LINE"

# Resolve modules set
MODULES=""
if [[ "${PROFILE_NAME,,}" == "custom" ]]; then
  if [[ -z "$CUSTOM_MODULES" ]]; then
    echo "::error ::profile=Custom but no --modules provided"
    exit 1
  fi
  MODULES="$CUSTOM_MODULES"
else
  # Lookup modules list from modules_presets.csv (ProfileName,Modules)
  [[ -f "$MODS_CSV" ]] || { echo "::error ::Modules CSV not found: $MODS_CSV"; exit 1; }
  MODULES="$(awk -F',' -v p="$PROFILE_NAME" 'NR==1{next} $1==p {print $2; exit}' "$MODS_CSV")"
  if [[ -z "$MODULES" ]]; then
    echo "::error ::Profile not found in $MODS_CSV: $PROFILE_NAME"
    echo "Available:"
    tail -n +2 "$MODS_CSV" | cut -d',' -f1 | nl -ba
    exit 1
  fi
fi

# Helper: map module tokens -> ENABLE_* defines
map_modules_to_defines() {
  local mods="$1"
  local out=""
  IFS=',' read -ra TOKS <<<"$(echo "$mods" | tr -d '[:space:]')"
  for t in "${TOKS[@]}"; do
    case "$t" in
      WIFI)        out+="\n#define ENABLE_WIFI" ;;
      BLE)         out+="\n#define ENABLE_BLE" ;;
      WEB)         out+="\n#define ENABLE_WEB" ;;
      SD)          out+="\n#define ENABLE_SD" ;;
      GPS)         out+="\n#define ENABLE_GPS" ;;
      TOUCH)       out+="\n#define ENABLE_TOUCH" ;;
      LVGL)        out+="\n#define ENABLE_LVGL" ;;
      NEOPIXEL)    out+="\n#define ENABLE_NEOPIXEL" ;;
      BUZZER)      out+="\n#define ENABLE_BUZZER" ;;
      BUTTONS)     out+="\n#define ENABLE_BUTTONS" ;;
      BATTERY)     out+="\n#define ENABLE_BATTERY" ;;
      NRF24)       out+="\n#define ENABLE_NRF24" ;;
      USB_MSC)     out+="\n#define ENABLE_USB_MSC" ;;
      DUAL_WIFI)   out+="\n#define ENABLE_DUAL_WIFI" ;;
      2WIFI)       out+="\n#define ENABLE_2WIFI" ;;
      TFT_ON)      TFT_ENABLED="true" ;;   # force on
      TFT_OFF)     TFT_ENABLED="false" ;;  # force off
      DEBUG)       out+="\n#define ENABLE_DEBUG" ;;
      *)           out+="\n// Unknown module token: $t" ;;
    esac
  done
  printf "%b" "$out"
}

FEATURE_DEFS="$(map_modules_to_defines "$MODULES")"

# Filesystem macro for sketch (SPIFFS/LITTLEFS)
FS_MACRO=""
case "${DEF_FS,,}" in
  littlefs) FS_MACRO="#define USE_LITTLEFS" ;;
  spiffs|"") FS_MACRO="#define USE_SPIFFS" ;;
  *) FS_MACRO="// Unknown FS '$DEF_FS' (defaulting to SPIFFS)\n#define USE_SPIFFS" ;;
esac

# Optional pins: if your pins CSV maps per-board shortcuts, you can emit them
PIN_DEFS=""
if [[ -f "$PINS_CSV" ]]; then
  # Example assumed header (adjust if yours differs):
  # board_label,gps_rx,gps_tx,i2c_sda,i2c_scl,sd_miso,sd_mosi,sd_sck,sd_cs,tft_miso,tft_mosi,tft_sck,tft_cs,tft_dc,tft_rst,neopixel_pin,buzzer_pin,btn1,btn2,btn3
  PINS_LINE="$(awk -F',' -v want="$BOARD_LABEL" 'NR==1{next} $1==want {print; exit}' "$PINS_CSV")" || true
  if [[ -n "$PINS_LINE" ]]; then
    IFS=',' read -r _ GPS_RX GPS_TX I2C_SDA I2C_SCL SD_MISO SD_MOSI SD_SCK SD_CS TFT_MISO TFT_MOSI TFT_SCK TFT_CS TFT_DC TFT_RST NEO_PIN BUZ_PIN BTN1 BTN2 BTN3 <<<"$PINS_LINE"
    [[ -n "${GPS_RX:-}" ]] && PIN_DEFS+="\n#define GPS_PIN_RX $GPS_RX"
    [[ -n "${GPS_TX:-}" ]] && PIN_DEFS+="\n#define GPS_PIN_TX $GPS_TX"
    [[ -n "${I2C_SDA:-}" ]] && PIN_DEFS+="\n#define I2C_SDA_PIN $I2C_SDA"
    [[ -n "${I2C_SCL:-}" ]] && PIN_DEFS+="\n#define I2C_SCL_PIN $I2C_SCL"
    [[ -n "${SD_MISO:-}" ]] && PIN_DEFS+="\n#define SD_MISO_PIN $SD_MISO"
    [[ -n "${SD_MOSI:-}" ]] && PIN_DEFS+="\n#define SD_MOSI_PIN $SD_MOSI"
    [[ -n "${SD_SCK:-}"  ]] && PIN_DEFS+="\n#define SD_SCK_PIN  $SD_SCK"
    [[ -n "${SD_CS:-}"   ]] && PIN_DEFS+="\n#define SD_CS_PIN   $SD_CS"
    [[ -n "${TFT_MISO:-}" ]] && PIN_DEFS+="\n#define TFT_MISO_PIN $TFT_MISO"
    [[ -n "${TFT_MOSI:-}" ]] && PIN_DEFS+="\n#define TFT_MOSI_PIN $TFT_MOSI"
    [[ -n "${TFT_SCK:-}"  ]] && PIN_DEFS+="\n#define TFT_SCK_PIN  $TFT_SCK"
    [[ -n "${TFT_CS:-}"   ]] && PIN_DEFS+="\n#define TFT_CS_PIN   $TFT_CS"
    [[ -n "${TFT_DC:-}"   ]] && PIN_DEFS+="\n#define TFT_DC_PIN   $TFT_DC"
    [[ -n "${TFT_RST:-}"  ]] && PIN_DEFS+="\n#define TFT_RST_PIN  $TFT_RST"
    [[ -n "${NEO_PIN:-}"  ]] && PIN_DEFS+="\n#define NEOPIXEL_PIN $NEO_PIN"
    [[ -n "${BUZ_PIN:-}"  ]] && PIN_DEFS+="\n#define BUZZER_PIN   $BUZ_PIN"
    [[ -n "${BTN1:-}"     ]] && PIN_DEFS+="\n#define BUTTON1_PIN  $BTN1"
    [[ -n "${BTN2:-}"     ]] && PIN_DEFS+="\n#define BUTTON2_PIN  $BTN2"
    [[ -n "${BTN3:-}"     ]] && PIN_DEFS+="\n#define BUTTON3_PIN  $BTN3"
  fi
fi

# TFT header/macros (HAS_TFT, DISP_HEADER) based on boards CSV + modules override
TFT_BLOCK=""
if [[ "${TFT_ENABLED,,}" == "true" ]]; then
  TFT_BLOCK="#define HAS_TFT"
  if [[ -n "${TFT_HEADER// /}" ]]; then
    TFT_BLOCK+=$'\n'"#define DISP_HEADER \"${TFT_HEADER}\""
  fi
fi

# Extra defines from boards CSV (column 'defines'), turn "A;B;C" into #define A etc.
EXTRA_BLOCK=""
if [[ -n "${EXTRA_DEFINES// /}" ]]; then
  IFS=';' read -ra XTRA <<<"$EXTRA_DEFINES"
  for d in "${XTRA[@]}"; do
    [[ -n "$d" ]] && EXTRA_BLOCK+=$'\n'"#define $d"
  done
fi

# Board flag (e.g., -DMARAUDER_V6_1) as a #define too
BOARD_FLAG_BLOCK=""
if [[ -n "${BOARD_FLAG// /}" ]]; then
  BOARD_FLAG_BLOCK="#define ${BOARD_FLAG}"
fi

# Version (optional): allow env MARAUDER_VERSION, else default
VER="${MARAUDER_VERSION:-v1.0.1}"

# Write configs.h
mkdir -p "$(dirname "$OUT_PATH")"
cat > "$OUT_PATH" <<EOF
#pragma once
// Auto-generated by gen_configs_h.sh
// Board:   ${BOARD_LABEL}
// FQBN:    ${FQBN}
// Core:    ${CORE_VER}
// Profile: ${PROFILE_NAME}
// FS:      ${DEF_FS}
// Part:    ${DEF_PART}
// Modules: ${MODULES}

#define MARAUDER_VERSION "${VER}"

// --- Board selection flag ---
${BOARD_FLAG_BLOCK}

// --- Filesystem selection ---
${FS_MACRO}

// --- Partition (string hint for logs/UI, SDK picks via platform build flags) ---
#define PARTITION_CSV "${DEF_PART}"

// --- Feature toggles from profile/modules ---
${FEATURE_DEFS}

// --- TFT presence & header hint ---
${TFT_BLOCK}

// --- Optional per-board pin mappings (if provided) ---
${PIN_DEFS}

// --- Extra board defines (from CSV 'defines' column) ---
${EXTRA_BLOCK}

// --- Dual WiFi notes ---
// ENABLE_DUAL_WIFI     -> orchestrates builtin + one external
// ENABLE_2WIFI         -> allow two external modules (advanced)

// --- Debug macro (opt-in) ---
// #define ENABLE_DEBUG

EOF

echo "Generated: $OUT_PATH"
