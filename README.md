# ESP32 Marauder Scaffold (Clean v3, No Duplicates)

This package is a **clean scaffold** of the ESP32 Marauder menu system, with all tools split into their own stub modules.
It preserves the **original menu structure** while removing duplicate entries (`Spoof Airtag` and `Select EP HTML File`).

## Structure

- `MENU_TREE.md` / `MENU_TREE.json`
  - Human-readable and machine-readable copies of the complete menu tree.
- `scaffold/registry/`
  - `ToolRegistry.*` — lightweight registry system to hold menu entries and their associated tool launchers.
- `scaffold/example_integration/`
  - `RegistryInit.*` — registers all tools into the registry.
  - `MenuFromRegistry.*` — builds menus from the registry.
  - `main_demo_snippet.ino` — Arduino demo showing how to render and navigate menus via Serial.
- `scaffold/wifi/*`, `scaffold/bluetooth/*`, `scaffold/device/`
  - Each subfolder corresponds to a **menu category** (e.g., WiFi / Sniffers, Bluetooth / Attacks).
  - Each tool has its own `.h`/`.cpp` pair with empty `setup()` / `loop()` stubs.
  - Each folder contains a `README.md` describing its section.

## How to Use

1. Open `example_integration/main_demo_snippet.ino` in Arduino IDE (with ESP32 board installed).
2. Flash to your ESP32 and open Serial Monitor at 115200 baud.
3. Use the Serial UI to navigate menus (`w`=up, `s`=down, `e`=enter, `b`=back).
4. When you select a tool, a stub message will be printed (e.g., `[Tool] Ping Scan launched (stub)`).
5. Implement tool logic gradually by editing each `.cpp` file.

## Notes

- This scaffold is **non-functional** by default — all tools are stubs.
- It is meant as a safe starting point to **rebuild features bit by bit**.
- Menu duplicates from the original Marauder source have been **removed**.

