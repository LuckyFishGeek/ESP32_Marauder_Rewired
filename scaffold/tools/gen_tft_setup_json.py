#!/usr/bin/env python3
import os, sys, json, re, argparse, pathlib, shlex

# ---------- Helpers ----------

def tokens_from_defines(s):
    s = (s or "").strip()
    if not s:
        return []
    parts = re.split(r'[;, \t]+', s)
    return [p for p in parts if p]

def load_json(path, default=None):
    try:
        with open(path, "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception:
        return default

def normalize_listish(obj, key=None):
    """
    Accept list or dict with a list under 'key'. If dict with 'presets', return that.
    """
    if isinstance(obj, list):
        return obj
    if isinstance(obj, dict):
        if key and isinstance(obj.get(key), list):
            return obj[key]
        if isinstance(obj.get("presets"), list):
            return obj["presets"]
    return []

def load_display_row(displays_json_path, model):
    rows_raw = load_json(displays_json_path, default=[])
    rows = normalize_listish(rows_raw) or normalize_listish(rows_raw, key="displays")
    # Accept dict-map form: { "ILI9341": {...}, "ST7789": {...} }
    if isinstance(rows_raw, dict) and not rows:
        if model in rows_raw:
            return rows_raw[model]
        # common nested form: { "presets": { "ILI9341": {...} } }
        if "presets" in rows_raw and isinstance(rows_raw["presets"], dict):
            return rows_raw["presets"].get(model, {})
    # list rows
    for r in rows:
        if (str(r.get("model") or "").strip() == model):
            return r
    return {}

def normalize_pin_rows(pin_presets_path):
    data = load_json(pin_presets_path, default=[])
    if isinstance(data, dict) and "combined" in data and isinstance(data["combined"], list):
        return data["combined"]
    if isinstance(data, list):
        return data
    return []

def find_pins(pin_presets_path, board_label=None, board_flag=None):
    """
    Find a best-effort pin record. First try exact match for board label/flag with _source='display'.
    Fallback to first record that looks like a TFT mapping.
    """
    combined = normalize_pin_rows(pin_presets_path)
    candidates = []
    for rec in combined:
        src = rec.get("_source","")
        bl = (rec.get("board_label") or rec.get("name") or "").strip()
        fl = (rec.get("board_flag") or rec.get("flag") or "").strip()
        if src == "display" and ((board_label and bl==board_label) or (board_flag and fl==board_flag)):
            candidates.append(rec)
    if not candidates:
        for rec in combined:
            # fallback: any record containing TFT_* pins
            if any(str(k).upper().startswith("TFT_") for k in rec.keys()):
                candidates.append(rec)
                break
    return candidates[0] if candidates else {}

def parse_pins_override(s):
    """
    Parse space-separated key=value pairs. Values may be CSV.
    Examples:
      "gps_pin=34,33"
      "tft_pin=19,23,18,5,21,22 touch_cs=27 touch_irq=36"
      "tft_mosi=23 tft_sclk=18 tft_dc=21 tft_rst=22 tft_cs=5 tft_bl=4"
    Returns a dict normalized to TFT_* and TOUCH_* keys where possible.
    """
    if not s:
        return {}
    parts = shlex.split(s)
    kv = {}
    for part in parts:
        if "=" not in part:
            continue
        k, v = part.split("=", 1)
        k = k.strip().lower()
        vals = [x.strip() for x in v.split(",") if x.strip()]
        if not k or not vals:
            continue
        kv[k] = vals

    # Map common aliases → canonical TFT_* / TOUCH_* keys
    # If user provided a block "tft_pin=" with SPI order, assume: MOSI,MISO,SCLK,CS,DC,RST,(BL optional)
    out = {}
    alias_map_single = {
        "tft_mosi": "TFT_MOSI",
        "tft_miso": "TFT_MISO",
        "tft_sck":  "TFT_SCLK",
        "tft_sclk": "TFT_SCLK",
        "tft_clk":  "TFT_SCLK",
        "tft_cs":   "TFT_CS",
        "tft_dc":   "TFT_DC",
        "tft_rs":   "TFT_DC",
        "tft_rst":  "TFT_RST",
        "tft_reset":"TFT_RST",
        "tft_bl":   "TFT_BL",
        "backlight":"TFT_BL",
        "touch_cs": "TOUCH_CS",
        "touch_ss": "TOUCH_CS",
        "touch_irq":"TOUCH_IRQ",
        "touch_int":"TOUCH_IRQ",
    }

    for k, vals in kv.items():
        if k in alias_map_single:
            out[alias_map_single[k]] = vals[0]  # single value
        elif k == "tft_pin":
            # Expect MOSI,MISO,SCLK,CS,DC,RST,(BL?)
            if len(vals) >= 1: out["TFT_MOSI"] = vals[0]
            if len(vals) >= 2: out["TFT_MISO"] = vals[1]
            if len(vals) >= 3: out["TFT_SCLK"] = vals[2]
            if len(vals) >= 4: out["TFT_CS"]   = vals[3]
            if len(vals) >= 5: out["TFT_DC"]   = vals[4]
            if len(vals) >= 6: out["TFT_RST"]  = vals[5]
            if len(vals) >= 7: out["TFT_BL"]   = vals[6]
        # Allow raw upper-case keys too (e.g., TFT_CS=5)
        elif k.upper().startswith("TFT_") or k.upper().startswith("TOUCH_"):
            out[k.upper()] = ",".join(vals) if len(vals) > 1 else vals[0]

    return out

def write_headers(out_dir, defines_tokens, tft_pins, touch_pins):
    out_dir = pathlib.Path(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    autogen = out_dir / "User_Setup_Autogen.h"
    select  = out_dir / "User_Setup_Select.h"

    lines = ["// Autogenerated by gen_tft_setup_json.py"]

    # Emit driver tokens and map "TFT_<MODEL>" → "<MODEL>_DRIVER"
    for tok in defines_tokens:
        tok = str(tok).strip()
        if not tok:
            continue
        lines.append(f"#define {tok}")
        if tok.startswith("TFT_"):
            model = re.sub(r'[^A-Za-z0-9_]', '', tok[len("TFT_"):])
            if model:
                lines.append(f"#define {model}_DRIVER")

    def add_pin(name, val):
        if val is None or val == "" or str(val).lower() == "nan":
            return
        lines.append(f"#define {name} {val}")

    # Map from gathered pin dicts → TFT_eSPI macros
    mapping = [
        ("TFT_MISO","TFT_MISO"),
        ("TFT_MOSI","TFT_MOSI"),
        ("TFT_SCK","TFT_SCLK"),
        ("TFT_SCLK","TFT_SCLK"),
        ("TFT_CS","TFT_CS"),
        ("TFT_DC","TFT_DC"),
        ("TFT_RST","TFT_RST"),
        ("TFT_BL","TFT_BL"),
    ]
    for src, dst in mapping:
        v = tft_pins.get(src) or tft_pins.get(dst)
        add_pin(dst, v)

    tc = touch_pins.get("TOUCH_CS") or touch_pins.get("CS") or touch_pins.get("TOUCH_CS_PIN")
    if tc:
        add_pin("TOUCH_CS", tc)
    for k in ("TOUCH_IRQ","TOUCH_INT","TOUCH_IRQ_PIN"):
        iv = touch_pins.get(k) or touch_pins.get("IRQ")
        if iv:
            add_pin("TOUCH_IRQ", iv)
            break

    autogen.write_text("\n".join(lines) + "\n", encoding="utf-8")
    select.write_text("// Auto-selected\n#include <User_Setup_Autogen.h>\n", encoding="utf-8")

# ---------- Main ----------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--boards-json",   default="scaffold/configs/boards/boards_manifest.json")
    ap.add_argument("--displays-json", default="scaffold/configs/displays/display_presets.json")
    ap.add_argument("--pins-json",     default="scaffold/configs/pins/pin_presets.json")

    ap.add_argument("--board-label", default="")
    ap.add_argument("--board-flag",  default="")
    ap.add_argument("--model",       default="")
    ap.add_argument("--tft-enabled", default="true")

    # NEW: free-form overrides coming from workflow input
    ap.add_argument("--pins-override", default="")

    ap.add_argument("--out-dir", required=True)
    args = ap.parse_args()

    tft_enabled = str(args.tft_enabled).strip().lower() in ("1","true","yes","y","on")
    model = (args.model or "").strip()
    if not tft_enabled or model.upper() in ("", "NONE", "SERIAL_ONLY"):
        write_headers(args.out_dir, [], {}, {})
        print("[INFO] Serial-only or TFT disabled: generated minimal TFT selector.")
        return

    # Load display row (model-driven)
    disp_row = load_display_row(args.displays_json, model)
    defines = disp_row.get("defines") or ""
    if isinstance(defines, list):
        tokens = [str(x) for x in defines]
    else:
        tokens = tokens_from_defines(defines)

    # Base pins from presets (board label/flag)
    pins_row = find_pins(args.pins_json, args.board_label, args.board_flag)
    tft_pins = {k: v for k, v in pins_row.items() if str(k).upper().startswith("TFT_")}
    touch_pins = {k: v for k, v in pins_row.items() if "TOUCH" in str(k).upper()}

    # Apply free-form overrides last (highest priority)
    overrides = parse_pins_override(args.pins_override)
    for k, v in overrides.items():
        if k.startswith("TFT_"):
            tft_pins[k] = v
        elif k.startswith("TOUCH_"):
            # normalize single strings
            touch_pins[k] = v if isinstance(v, str) else (",".join(v) if isinstance(v, list) else v)

    write_headers(args.out_dir, tokens, tft_pins, touch_pins)
    print("[OK] Wrote TFT_eSPI autogen headers.")

if __name__ == "__main__":
    main()
