# Quick Start — ESP32 Marauder Rewired (v1.0.1)

This guide walks you from **zero → flashed firmware** using GitHub Actions.

---

## 1) Fork or Use the Repo
- Fork this repo (recommended) or use upstream if you have write access.

---

## 2) Open GitHub Actions
- Go to **Actions** tab in your fork.  
- Pick **Build (Custom CSV Profiles - ESP32 Marauder Rewired)**.  
- Click **Run workflow**.

---

## 3) Fill the Workflow Inputs

### Required-ish
- **board_label** – Choose your board (from boards_manifest.csv).  
- If not listed, pick **Other (enter FQBN)**.

### Feature profile
- **profile_name** – Pick from `modules_presets.csv` (Minimal, Full, Displayless, etc).  
- **Custom** → type `modules_csv` manually.

### Filesystem / partitions
- **filesystem** – spiffs or littlefs.  
- **partition** – Marauder Default, Huge App + 1MB FS, etc.

### Display
- **tft_model** – Choose from `display_presets.csv`.  
- **Auto** = use CSV defaults, **None** = no display.

### Pin overrides
- **custom_pins** – Free-form like:  
  `gps_pin=34,33 tft_pin=19,23,18,5,21,22 sd_pin=19,23,18,5 neopixel_pin=27`  

### Extra defines
- **extra_defines** – Space-separated flags (`DEBUG`, `LOGGING=1`).

---

## 4) Run the Build
- Click run, wait until green.

---

## 5) Download the Artifact
- Get your bin from **Artifacts**.

---

## 6) Flash the Firmware

**ESP32**  
```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash -z 0x10000 firmware.bin
```

**ESP32-S2/S3/C5** → Replace chip name & offsets as required.

---

## Troubleshooting
- **Unknown FQBN** → use fqbn_override.  
- **TFT blank** → confirm `tft_model` + pins.  
- **I2C fail** → check pull-ups + `i2c_pin`.  
- **No artifact** → see workflow logs.  
- **Linux serial perms** → add user to `dialout` or `sudo`.  

---

## Examples

**M5StickC Full build**  
- `board_label`: M5StickC / M5StickC-Plus  
- `profile_name`: Full  
- `tft_model`: ST7789  
- `custom_pins`: `i2c_pin=21,22 gps_pin=34,33 sd_pin=19,23,18,5 neopixel_pin=27`  

**Generic ESP32 wardriver**  
- `board_label`: Generic ESP32 Dev Module  
- `profile_name`: Wardriver  
- `tft_model`: ILI9341  
- `custom_pins`: `tft_pin=19,23,18,5,21,22`  

---

Happy hacking — v1.0.1 brings sanity, TFT fixes, and C5 support.
