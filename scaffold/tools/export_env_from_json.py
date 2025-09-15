#!/usr/bin/env python3
import json, os, sys

MANIFEST = "scaffold/configs/boards/boards_manifest.json"
flag = os.environ.get("BOARD_FLAG","").strip()
label = os.environ.get("BOARD_LABEL","").strip()

def flatten(prefix, obj):
    lines = []
    if isinstance(obj, dict):
        for k,v in obj.items():
            lines += flatten(f"{prefix}_{k}".upper(), v)
    elif isinstance(obj, list):
        if all(not isinstance(x,(dict,list)) for x in obj):
            lines.append((prefix.upper(), ",".join(str(x) for x in obj)))
        else:
            lines.append((prefix.upper(), json.dumps(obj, separators=(',',':'))))
    elif obj is None:
        pass
    else:
        lines.append((prefix.upper(), str(obj)))
    return lines

def pick(rows):
    if flag:
        for r in rows:
            if r.get("flag")==flag:
                return r
    if label:
        for r in rows:
            if r.get("board_label")==label:
                return r
    return None

def main():
    try:
        rows = json.load(open(MANIFEST,"r",encoding="utf-8"))
    except Exception as e:
        print(f"::error ::cannot read {MANIFEST}: {e}")
        sys.exit(2)

    row = pick(rows)
    if not row:
        print(f"::error ::board not found (flag='{flag}', label='{label}')")
        sys.exit(1)

    for k in ("board_label","fqbn","flag","filesystem","partition","addr","core_version"):
        if k in row and row[k] is not None:
            print(f"{k.upper()}={row[k]}")

    if "display" in row:
        for k,v in flatten("display", row["display"]):
            print(f"{k}={v}")
    if "libs" in row:
        for k,v in flatten("libs", row["libs"]):
            print(f"{k}={v}")

if __name__=="__main__":
    main()
