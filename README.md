# ESP32 Marauder Rewired  
**Official Release v1.0.1**  

---

## 🚀 Quick Start
👉 [**CLICK ME to open the Quick Start Guide**](./QuickStart.md)

This guide walks you step-by-step:
- Fork this repo
- Run the GitHub Actions build
- Download your firmware artifact
- Flash it with `esptool.py`

---

## 📝 Overview  
This is the **second official release** of **ESP32 Marauder Rewired (v1.0.1)** — building on the 1.0.0 “Manifest Era”.  
Now with stronger **CSV sanity checks**, **ESP32-C5 support**, and predictable **TFT configuration**.

---

## 🛠️ The Journey (Trials & Errors)  

### From v1.0.0 (old journey)
- **Tried direct porting of the original source** → too many legacy issues.  
- **Attempted partial rebuilds** → hit endless compiler errors, missing defines, and broken TFT headers.  
- **Stripped the build system down** to a minimal Arduino-CLI workflow.  
- **Introduced JSON manifest (`manifest.json`)** to centralize board definitions.  
- **Added CSV presets (`modules_presets.csv`)** for feature selection.  
- **Partition chaos solved** → standardized on `marauder_default.csv` plus all legacy CSVs.  

### Into v1.0.1 (new journey)
- **Killed JSON drift** → Replaced `manifest.json` with a single source of truth: `scaffold/configs/boards_manifest.csv`.  
- **Added CSV sanity checks** for CRLF, headers, and partitions.  
- **Board mapping is CSV-driven** → clean resolve of fqbn, filesystem, partition, tft, defines, core version.  
- **Per-board core versions** → installs right `esp32:esp32@<core_ver>` (2.x or 3.x).  
- **ESP32-C5 support added** (core 3.3.0, no TFT).  
- **TFT setup predictable** → skipped if `tft_enabled=false`; injected if `tft_header` exists.  
- **Cleaner defines** and **partition installs** handled in workflow.  
- **Matrix build retired** → main workflow now single-source.  

---

## ✅ What Works Now (v1.0.1)  
- **Manifest-driven CSV build system** (boards_manifest.csv).  
- **ESP32-C5 builds cleanly** (no TFT, serial-driven).  
- **All TFT boards work** with auto-applied User_Setup headers.  
- **Custom partitions** copied to Arduino core paths.  
- **Library staging & sanity protocol** ensures reliable builds.  

---

## ⚠️ Known Issues  
- **BLE/GPS** modules limited to certain boards.  
- **M5Stack ecosystem** partial support.  
- **Some partitions** (hugeapp, ota) need stress testing.  

---

## 🔮 Next (v1.1.0 plans)  
- Full feature parity with legacy Marauder.  
- Expanded partition schemes.  
- Auto-profile selection by board.  
- GUI pin override menus.  
- More docs/examples.  
- PlatformIO support.  

---

## Sanity protocol

What it checks:
- Normalizes CRLF→LF across CSVs.  
- Validates headers for boards, libs, modules, pins, displays.  
- Lists detected labels and profiles.  
- Light validation of partitions.  

---

## 📂 Repository Structure  

```
/scaffold
 ├── configs/
 │   ├── boards_manifest.csv     # Boards
 │   ├── lib_list.csv            # Libraries
 │   ├── modules_presets.csv     # Features
 │   ├── pins/                   # Pin + Display presets
 ├── partitions/                 # Partition CSVs
 ├── .github/workflows/          # Build workflows
```

---

## 🏷️ Versioning  
**`v1.0.1` — The Sanity Era**  
Next milestone: **`v1.1.0`** for full parity + advanced features.  
