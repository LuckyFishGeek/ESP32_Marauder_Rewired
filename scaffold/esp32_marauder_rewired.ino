#include "config.h"              // must come first so TFT_eSPI sees width/height
#include <Arduino.h>
#include <CustomFunctions.h>     // declares void showMainMenu();
#include "menus/MenuTypes.h"
#include "menus/ToolRegistry.h"
#include "menus/RegistryInit.h"
#include "menus/MenuFromRegistry.h"
#include "menus/MenuUI.h"

void setup() {
  // Usual serial bring-up for debugging
  Serial.begin(115200);
  delay(100);
  Serial.println("\n[Boot] ESP32 Marauder Rewired (linked build)");

  // Initialize the registry (menu tools)
  init_tool_registry();

  // Hand off to the library UI entrypoint (implemented in CustomFunctions lib)
  showMainMenu();
}

void loop() {
  // Your CustomFunctions-driven UI typically manages its own loop via tasks/callbacks.
  // Keep loop lean.
  delay(10);
}
