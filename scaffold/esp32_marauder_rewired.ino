#include <Arduino.h>
#include <CustomFunctions.h>   // declares: void showMainMenu();
#include "menus/RegistryInit.h"

// NOTE:
// - Do NOT declare `extern "C"` for showMainMenu() here; the library already
//   declares `void showMainMenu();` (C++ linkage).
// - TFT_eSPI configuration (TFT_WIDTH/HEIGHT etc.) comes from your autogen
//   headers (User_Setup_Autogen.h) included via build flags.

void setup() {
  Serial.begin(115200);
  while (!Serial) { /* wait for USB serial, if applicable */ }
  Serial.println(F("[INIT] ESP32 Marauder Rewired (menu wiring)"));



  // Let the CustomFunctions library draw and drive the main menu.
  showMainMenu();
}

void loop() {
  // Keep the MCU responsive; UI framework may hook its own callbacks/loop.
  delay(10);
}
