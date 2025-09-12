# 🚀 Quick Start Guide

This guide shows you how to build and flash ESP32 Marauder Rewired firmware using GitHub Actions.

---

## 1️⃣ Fork the Repo
- Go to [ESP32 Marauder Rewired](https://github.com/AirysDark/ESP32_Marauder_Rewired)
- Click **Fork** (top right) to create your own copy.

## 2️⃣ Open GitHub Actions
- In your fork, go to the **Actions** tab.
- Select **Build (Custom CSV Profiles - ESP32 Marauder Rewired)**.

## 3️⃣ Run a Build
- Click **Run workflow**.
- Choose your **board**, **profile**, **filesystem**, and **partition scheme**.
- (Optional) Add **custom pin CSV** or extra defines.

## 4️⃣ Download Firmware
- When the job finishes, go to the **Artifacts** section.
- Download your firmware ZIP.
- Inside you’ll find `.bin` files.

## 5️⃣ Flash to ESP32
Use [esptool.py](https://github.com/espressif/esptool):

```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600   write_flash -z 0x1000 firmware.bin
```

(Replace `/dev/ttyUSB0` with your port, and `firmware.bin` with the artifact filename).

---

🎉 Done! Your ESP32 should now boot **ESP32 Marauder Rewired**.
