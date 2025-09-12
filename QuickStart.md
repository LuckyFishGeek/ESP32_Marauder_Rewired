
# Quick Start — ESP32 Marauder Rewired

This guide walks you from **zero → flashed firmware** using the repo’s GitHub Actions workflow.

---

## 1) Fork or Use the Repo
- Click **Fork** on GitHub to copy the repo to your account (recommended), **or**
- Use the upstream repo directly if you have write access to run Actions.

> *Why fork?* You’ll keep your builds and artifacts separate, and you can save your own presets.

---

## 2) Open GitHub Actions
- Go to your fork → **Actions** tab.
- Select **“Build (Custom CSV Profiles - ESP32 Marauder Rewired)”**.
- Click **“Run workflow”** (top-right).

---

## 3) Fill the Workflow Inputs
You’ll see a set of dropdowns and text inputs. Here’s what each does:

### Required-ish
- **board_label** – Your dev board (e.g., *Generic ESP32 Dev Module*, *ESP32-S3 Dev Module*, *M5StickC*).  
  - If your board isn’t listed, pick **Other (enter FQBN)** and fill **fqbn_override** (e.g., `esp32:esp32:nodemcu-32s`).

### Feature profile
- **profile_name** – Feature set from `modules_presets.csv` (e.g., *Minimal*, *Standard*, *Full*, *Wardriver*, *Displayless*, etc.).  
  - Choose **Custom** only if you plan to type `modules_csv` (e.g., `WIFI,BLE,SD,TFT_ON,LVGL`).

### Optional file-system / partitions
- **filesystem** – Override default FS (`spiffs` or `littlefs`).  
- **partition** – Human-friendly labels for the bundled CSV layouts (e.g., *Marauder Default*, *Huge App + 1MB FS*).

### Display
- **tft_model** – Pick a screen from `scaffold/configs/displays/display_presets.csv`.  
  - **Auto** (default) = use manifest defaults.  
  - **None** = displayless build.  
  - Examples: `ILI9341`, `ST7789`, `SSD1306`, `RA8875`, etc.

### Pin overrides (simple, free-form)
- **custom_pins** – Type **space-separated** entries like `key=comma,list`.  
  Supported keys (order matters):
  - `gps_pin=RX,TX[,PPS,EN]`  
    - Example: `gps_pin=34,33` or `gps_pin=34,33,2`
  - `i2c_pin=SDA,SCL`  
    - Example: `i2c_pin=21,22`
  - `tft_pin=MISO,MOSI,SCK,CS,DC,RST`  
    - Example: `tft_pin=19,23,18,5,21,22`
  - `sd_pin=MISO,MOSI,SCK,CS`  
    - Example: `sd_pin=19,23,18,5`
  - `neopixel_pin=DATA`  
    - Example: `neopixel_pin=27`
  - `buzzer_pin=PIN`  
    - Example: `buzzer_pin=4`
  - `buttons_pin=BTN1,BTN2,BTN3`  
    - Example: `buttons_pin=32,33,25`
  - `wifi_pin=MISO,MOSI,SCK,CS` (for external SPI Wi‑Fi modules only)

  You can combine multiple entries by separating with **spaces** (or `;`):  
  ```
  gps_pin=34,33 tft_pin=19,23,18,5,21,22 sd_pin=19,23,18,5 neopixel_pin=27
  ```

> The workflow also reads **board defaults** from `scaffold/configs/pins/pins_presets.csv` and converts them to `-D` macros automatically. Your **custom_pins** override takes precedence when you provide it.

### Extra compile flags (advanced)
- **extra_defines** – Space-separated extras that become `-D` macros.  
  - Example: `DEBUG VERBOSE_LOGGING=1`

---

## 4) Run the Build
- Click **Run workflow**.
- Wait for the job to finish (status turns green).

---

## 5) Download the Artifact
- Open the finished run → **Artifacts** (bottom) → download the ZIP.  
- Inside, you’ll find `*.bin` files under `build/<fqbn>/` (Arduino CLI export).

---

## 6) Flash the Firmware

### Option A: esptool.py (CLI)
1. Put ESP32 into bootloader (hold BOOT, tap EN, release BOOT; varies by board).
2. Replace `/dev/ttyUSB0` (Linux) or `COM5` (Windows) and offsets accordingly.

**ESP32 (WROOM/WROVER)**
```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600   write_flash -z 0x10000 firmware.bin
```

**ESP32-S2**
```bash
esptool.py --chip esp32s2 --port /dev/ttyUSB0 --baud 921600   write_flash -z 0x10000 firmware.bin
```

**ESP32-S3**
```bash
esptool.py --chip esp32s3 --port /dev/ttyUSB0 --baud 921600   write_flash -z 0x10000 firmware.bin
```

> If your partition layout uses a separate bootloader/partitions/app, flash all three (example addresses):
```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600 write_flash -z   0x1000 bootloader.bin   0x8000 partitions.bin   0x10000 app.bin
```

### Option B: Arduino IDE (GUI)
- Open **Arduino IDE** → **File → Preferences** → add ESP32 board manager URL (per core).
- **Tools → Board** → select your board/FQBN.
- **Sketch → Upload Using Programmer** or standard Upload (choose the right COM/tty port).
- Use the exported `app.bin` if you want to upload via **Tools → Burn Bootloader / Programmer** flows.

---

## Troubleshooting

- **Build fails: Unknown FQBN** → choose *Other (enter FQBN)* and paste the exact fqbn (e.g., `esp32:esp32:esp32s3`).  
- **No artifact** → open the run log to see which step failed (partition CSV path or display preset are common culprits).  
- **TFT shows nothing** → confirm `tft_model` is correct **and** your `tft_pin` order matches the required mapping.  
- **I2C devices not detected** → verify pull-ups and your `i2c_pin=SDA,SCL` match your board wiring.  
- **Permission denied on serial** (Linux) → add your user to `dialout` or run with `sudo`.  

---

## Where Things Live
- **Board manifest**: `scaffold/configs/manifest.json`  
- **Feature profiles**: `modules_presets.csv`  
- **Display presets**: `scaffold/configs/displays/display_presets.csv`  
- **Pin presets (per board)**: `scaffold/configs/pins/pins_presets.csv`  
- **GitHub workflow**: `.github/workflows/*.yml`

---

## Examples

**M5StickC, ST7789 display, I2C scanner, GPS + SD + TFT + NeoPixel**  
- `board_label`: *M5StickC / M5StickC-Plus*  
- `profile_name`: *Full*  
- `tft_model`: `ST7789`  
- `custom_pins`: `i2c_pin=21,22 gps_pin=34,33 sd_pin=19,23,18,5 tft_pin=19,23,18,5,15,18 neopixel_pin=27`

**Generic ESP32 Dev Module, simple wardriver**  
- `board_label`: *Generic ESP32 Dev Module*  
- `profile_name`: *Wardriver*  
- `tft_model`: `ILI9341`  
- `custom_pins`: `tft_pin=19,23,18,5,21,22`

---

Happy hacking! If you get stuck, open an issue with your **workflow inputs**, **board label**, and **build log**.
