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

def pick(rows, flag, label):
    if flag:
        for r in rows:
            if (r.get("flag") or "").strip() == flag:
                return r
    if label:
        for r in rows:
            if (r.get("board_label") or "").strip() == label:
                return r
    return None

def safe_print(k, v):
    print(f"{k}={v}")

def main():
    # Always record the requested selectors so later steps can see them
    if flag:  safe_print("FLAG", flag)
    if label: safe_print("BOARD_LABEL", label)

    try:
        rows = json.load(open(MANIFEST, "r", encoding="utf-8"))
        if not isinstance(rows, list):
            eprint(f"[exporter] {MANIFEST} is not a JSON array.")
            return
    except Exception as ex:
        eprint(f"[exporter] Could not read {MANIFEST}: {ex}")
        return

    row = pick(rows, flag, label)
    if not row:
        avail = [r.get('flag') for r in rows if r.get('flag')]
        eprint(f"[exporter] Board not found. FLAG='{flag}' LABEL='{label}'. Available flags: {avail}")
        return

    # Top-level keys (normalize fbqn?FQBN)
    # Accept either 'fqbn' or 'fbqn' in the manifest; always export FQBN
    top_keys = ("board_label","fqbn","fbqn","flag","filesystem","partition","addr","core_version")
    mapped   = {"fbqn": "fqbn"}  # normalization map
    for k in top_keys:
        v = row.get(k)
        if v is None: 
            continue
        key = mapped.get(k, k).upper()
        safe_print(key, v)

    # Display / libs (flattened)
    disp = row.get("display") or {}
    for k, v in flatten("display", disp):
        safe_print(k, v)

    libs = row.get("libs") or {}
    # normalize legacy names from manifest (nimble_ver / esp_async_ver) into *_VERSION
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
