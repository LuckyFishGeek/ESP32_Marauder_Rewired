#!/usr/bin/env python3
import json, os, sys

MANIFEST = "scaffold/configs/boards/boards_manifest.json"
flag = (os.environ.get("BOARD_FLAG") or "").strip()
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

def safe_print(env_k, env_v):
    # Only ASCII-ish to be safe for $GITHUB_ENV
    print(f"{env_k}={env_v}")

def main():
    # Default fallbacks so later steps don't explode if config is missing
    if flag: safe_print("FLAG", flag)
    if label: safe_print("BOARD_LABEL", label)

    try:
        with open(MANIFEST, "r", encoding="utf-8") as f:
            rows = json.load(f)
            if not isinstance(rows, list):
                eprint(f"[exporter] {MANIFEST} did not contain a JSON array.")
                return  # keep job alive
    except Exception as ex:
        eprint(f"[exporter] Could not read {MANIFEST}: {ex}")
        return  # keep job alive

    row = pick(rows, flag, label)
    if not row:
        eprint(f"[exporter] Board not found. FLAG='{flag}', LABEL='{label}'. "
               f"Available flags: {[r.get('flag') for r in rows if r.get('flag')]}")
        return  # keep job alive

    # Top-level keys
    for k in ("board_label","fqbn","flag","filesystem","partition","addr","core_version"):
        v = row.get(k)
        if v is not None:
            safe_print(k.upper(), v)

    # Display / libs (flattened)
    disp = row.get("display") or {}
    for k, v in flatten("display", disp):
        safe_print(k, v)
    libs = row.get("libs") or {}
    for k, v in flatten("libs", libs):
        safe_print(k, v)

if __name__ == "__main__":
    main()
