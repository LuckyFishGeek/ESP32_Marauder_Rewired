# ESP32 Marauder Rewired

*A modular, menu-accurate scaffold of the ESP32 Marauder firmware for incremental rebuilding.*

---

## Overview

ESP32 Marauder Rewired is a **deconstructed + rewired scaffold** of the original ESP32 Marauder firmware.  
It preserves the **exact menu tree** while separating each tool into its own module (`.h` / `.cpp`),  
so you can rebuild features **step by step** without wrestling the full monolith.

- ✅ All original menu entries (Sniffers, Scanners, Wardriving, Attacks, Device)  
- ✅ Duplicates removed (`Spoof Airtag`, `Select EP HTML File`)  
- ✅ Minimal `ToolRegistry` system to populate menus  
- ✅ PlatformIO-ready project (`platformio.ini`, `src/`, `include/`)  
- ✅ Every tool has its own stub file waiting to be implemented  

---

## Build-Out Checklist

### Core
- [x] Menu tree, registry, stubs
- [x] PlatformIO project wired

### Milestones
**M1 — Passive Wi-Fi sniffers**  
ProbeSniffer → BeaconSniffer → DeauthSniffer → PacketMonitor → EAPOL/PMKID Scan → ChannelAnalyzer → RawCapture

**M2 — Bluetooth sniffers**  
BluetoothSniffer → FlipperSniff → AirtagSniff → DetectCardSkimmers → BluetoothAnalyzer

**M3 — Scanners**  
PingScan (ICMP), ArpScan, PortScanAll, SshScan, TelnetScan

**M4 — Wardriving**  
Wardrive, StationWardrive + GPS loggers (CSV/GPX/JSON)

**M5 — Device utilities**  
DeviceInfo, Settings, Save/Load Files, Language, Delete SD, GPS tools

**M6 — Wi-Fi General**  
Generate/Select/Add/Clear SSIDs, Select APs/Stations, View AP Info, Join WiFi, Join Saved WiFi, Set MACs, Shutdown WiFi

**M7 — (Optional) Attacks**  
Stubbed until everything else is stable; gate behind compile-time flag.

---

## Repo Name & Tagline

**ESP32 Marauder Rewired**  
> *“A modular, menu-accurate scaffold of the ESP32 Marauder firmware for incremental rebuilding.”*

---

## Quick Start

1. Open `platformio_project/` in VS Code with PlatformIO.  
2. Build & upload to an ESP32 board.  
3. Open Serial Monitor @ 115200 baud.  
4. Navigate menus using:
   - `w` = up  
   - `s` = down  
   - `e` = select  
   - `b` = back  

Each tool currently prints a stub message like:  
```
[Tool] Ping Scan launched (stub)
```

Implement tool logic gradually by editing the matching `.cpp` in `platformio_project/src/...`.

---
