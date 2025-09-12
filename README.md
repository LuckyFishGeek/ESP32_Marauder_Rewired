# ESP32 Marauder Rewired  
**Official Release v1.0.0**  

---
 
## 🔥 Overview  
This is the **first official release** of **ESP32 Marauder Rewired (v1.0.0)** — a complete rebuild of the Marauder firmware system with modern GitHub Actions automation, manifest-driven board definitions, and modular CSV-based feature profiles.  

This project started as an attempt to adapt the **original Marauder source code**, but after many dead ends (compile errors, outdated libs, unsupported boards, messy defines), we took the radical decision to **strip it down and rebuild from scratch**.  

Now, everything is driven by clean manifests and profiles — no more hard-coded spaghetti or random board hacks.  

---

## 🧪 The Journey (Trials & Errors)  

- **Tried direct porting of the original source** → too many legacy issues.  
- **Attempted partial rebuilds** → hit endless compiler errors, missing defines, and broken TFT headers.  
- **Stripped the build system down** to a minimal Arduino-CLI workflow.  
- **Introduced JSON manifest (`manifest.json`)** to centralize board definitions (FQBN, flags, defaults, TFT headers).  
- **Added CSV presets (`modules_presets.csv`)** for feature selection: WiFi, BLE, GPS, SD, TFT, etc.  
- **Refactored GitHub Actions** to be manifest-driven with **pretty dropdowns** for boards, filesystems, and partitions.  
- **Tested with multiple boards** (OG Marauder, v6, v6.1, v7, M5StickC, Flipper Zero boards, ESP32-S2/S3/C5, etc).  
- **Partition chaos solved** → standardized on a clean `marauder_default.csv` plus compatibility with all legacy CSVs.  

---

## ✅ What Works Now (v1.0.0)  

- **Manifest-driven build system**  
  - Every supported board is declared in `manifest.json`.  
  - Defaults for filesystem, partition scheme, and TFT header all set per board.  

- **Custom CSV Profiles**  
  - `modules_presets.csv` defines “Minimal”, “Full”, “Wardriver”, “Scanner”, “Displayless”, etc.  
  - Users can also supply **Custom CSV** flags for advanced builds.  

- **Arduino-CLI GitHub Actions**  
  - Fully automated firmware builds via workflow dispatch.  
  - Dropdown menus for board, filesystem, partition scheme, and profile.  
  - Works across **esp32, esp32-s2, esp32-s3, esp32-c5** families.  

- **Partition support**  
  - Includes: `hugeapp_1m_fs.csv`, `marauder_littlefs.csv`, `marauder_spiffs_ota.csv`,  
    `min_littlefs_ota.csv`, `min_spiffs_ota.csv`, `ota_1m_fs.csv`, and the new **`marauder_default.csv`**.  
  - All selectable with **pretty labels** in the workflow dropdown.  

- **TFT header injection**  
  - TFT_eSPI auto-configured per board via manifest.  
  - Headers like `User_Setup_og_marauder.h`, `User_Setup_marauder_mini.h`, etc.  

---

## ⚠️ Known Issues / Not Yet Implemented  

- **Feature parity with legacy Marauder** → not all menu/UI features restored yet.  
- **BLE and GPS modules** work only with certain profiles/boards; testing ongoing.  
- **Some partitions (hugeapp, ota) need stress testing** for stability.  
- **Not all TFT headers included upstream** → some require manual tweaking.  
- **M5Stack ecosystem** → partial support, needs polish.  

---

## 🚀 What’s Coming Next  

- Full **feature parity with legacy Marauder** (all menus & modules).  
- Additional **partition profiles** (bigger FS, OTA dual-bank layouts).  
- Smarter **Auto-profile selection** from manifest → board picks its best feature set.  
- **Custom pin menu** → assign GPIO pins directly from the firmware UI.  
- More polished **documentation & examples** (how to extend manifest, how to add new profiles).  
- Potential **PlatformIO support** alongside Arduino-CLI.  
- **Community presets** → share and merge your module CSVs easily.  

---

## 🏆 Advantages of This Rewired Build  

- **Cleaner structure** → no more mystery macros; every board is defined in JSON.  
- **Portable** → easily add new boards or profiles without hacking C++ headers.  
- **Automated builds** → GitHub Actions outputs firmware for all boards at once.  
- **Future-proof** → Arduino-ESP32 2.x core supported out of the box.  
- **Customizable** → profiles and partitions selectable at build time.  

---

## 📂 Repository Structure  

```
/scaffold
 +-- configs/
 ¦    +-- manifest.json         # All board definitions
 +-- registry/                  # Registry library sources
 +-- *.ino                      # Main sketch entry points

/partitions
 +-- marauder_default.csv       # NEW standard partition
 +-- marauder_spiffs_ota.csv
 +-- marauder_littlefs.csv
 +-- min_spiffs_ota.csv
 +-- min_littlefs_ota.csv
 +-- hugeapp_1m_fs.csv
 +-- ota_1m_fs.csv

/modules_presets.csv            # Feature profiles

/.github/workflows              # Build workflows (premade + custom modes)
```

---

## 🛠 Build Modes  

There are now **two build paths** supported:  

### 1. Premade Build Mode  
- Select a **board** from the workflow dropdown.  
- Workflow auto-loads the board’s defaults from `manifest.json`.  
- Profile, filesystem, and partition are auto-populated.  
- Best choice if you just want a working firmware without tweaking.  

### 2. Custom Build Mode  
- Select `"Other (enter FQBN)"` or choose **Custom CSV**.  
- Provide your own `fqbn_override` or `modules_csv`.  
- **Pick exactly which modules you want** (WiFi, BLE, GPS, SD, TFT, Buttons, NRF24, etc).  
- Supports experimental setups, unusual dev boards, or personal module mixes.  
- Best choice for advanced users who need to experiment.  

---

## 📌 Versioning  

This release is tagged as:  
**`v1.0.0` — The Manifest Era**  

The next milestone will be **`v1.1.0`** once feature parity and testing expand across all boards.  

---

✅ This README marks the official start of the **rewired Marauder firmware project**.  
We went from **“impossible to build”** → to a **clean, extensible, automated system**.  
