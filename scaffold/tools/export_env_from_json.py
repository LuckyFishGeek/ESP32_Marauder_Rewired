#!/usr/bin/env python3
import json, os, sys

MANIFEST = "scaffold/configs/boards/boards_manifest.json"
flag  = (os.environ.get("BOARD_FLAG")  or "").strip()
label = (os.environ.get("BOARD_LABEL") or "").strip()

def eprint(*a): print(*a, file=sys.stderr)

def flatten(prefix, obj):
    items = []
    if isinstance(obj, dict):
        for k, v in obj.items():
            items += flatten(f"{prefix}_{k}".upper(), v)
    elif isinstance(obj, list):
        if all(not isinstance(x, (dict, list)) for x in obj):
            items.append((prefix.upper(), ",".join(str(x) for x in obj)))
        else:
            items.append((prefix.upper(), json.dumps(obj, separators=(',',':'))))
    elif obj is None:
        pass
    else:
        items.append((prefix.upper(), str(obj)))
    return items

def load_rows():
    try:
        data = json.load(open(MANIFEST, "r", encoding="utf-8"))
    except Exception as ex:
        eprint(f"[exporter] Could not read {MANIFEST}: {ex}")
        return []
    if isinstance(data, list):
        return data
    if isinstance(data, dict):
        if isinstance(data.get("boards"), list):
            return data["boards"]
        if all(isinstance(v, dict) for v in data.values()):
            out = []
            for k, v in data.items():
                vv = dict(v); vv.setdefault("flag", k); out.append(vv)
            return out
    eprint(f"[exporter] Unrecognized JSON shape in {MANIFEST}.")
    return []

def pick(rows, flag, label):
    # CSV behavior: prefer board_label exact match
    if label:
        for r in rows:
            if (r.get("board_label") or "").strip() == label:
                return r
        # also try common aliases
        for r in rows:
            if (r.get("name") or "").strip() == label:
                return r
    if flag:
        for r in rows:
            if (r.get("flag") or "").strip() == flag:
                return r
    return None

def safe_print(k, v): print(f"{k}={v}")

def main():
    # Always emit selectors
    if flag:  safe_print("FLAG", flag)
    if label: safe_print("BOARD_LABEL", label)

    rows = load_rows()
    if not rows: return

    row = pick(rows, flag, label)
    if not row:
        avail = [r.get('flag') for r in rows if r.get('flag')]
        eprint(f"[exporter] Board not found. FLAG='{flag}' LABEL='{label}'. Available flags: {avail}")
        return

    # Normalize fbqn?FQBN; accept case variations
    top_keys = ("board_label","fqbn","fbqn","FQBN","flag","filesystem","partition","addr","core_version")
    mapped   = {"fbqn": "fqbn", "FQBN": "fqbn"}
    for k in top_keys:
        if k in row and row[k] is not None:
            key = mapped.get(k, k).upper()
            safe_print(key, row[k])

    # Base defines: always add -D<FLAG> like your CSV
    fl = (row.get("flag") or "").strip() or flag
    if fl:
        safe_print("DEFINES_BASE", f"-D{fl}")

    # Display / libs (normalize nimble_ver, esp_async.ver)
    disp = row.get("display") or {}
    for k, v in flatten("display", disp):
        safe_print(k, v)

    libs = row.get("libs") or {}
    if "nimble_ver" in libs and "nimble_version" not in libs:
        libs["nimble_version"] = libs["nimble_ver"]
    if "esp_async" in libs and isinstance(libs["esp_async"], dict):
        ea = libs["esp_async"]
        if "ver" in ea and "version" not in ea:
            ea["version"] = ea["ver"]
    for k, v in flatten("libs", libs):
        safe_print(k, v)

if __name__ == "__main__":
    main()
