#include <Arduino.h>
#include "config.h"                          // your board/feature flags, OK early

// Must come before TFT_eSPI so the driver & size macros are visible:
#include ".tft_setup/User_Setup_Select.h"

#include <TFT_eSPI.h>
#include <CustomFunctions.h>

#include "menus/MenuTypes.h"
#include "menus/ToolRegistry.h"
#include "menus/RegistryInit.h"
#include "menus/MenuFromRegistry.h"
#include "menus/MenuUI.h"

// Optional sanity checks (fail fast if autogen didn't load)
#ifndef ILI9341_DRIVER
#  warning "ILI9341_DRIVER not set — check .tft_setup/User_Setup_Autogen.h generation."
#endif
#ifndef TFT_WIDTH
#  warning "TFT_WIDTH not set — ensure .tft_setup/User_Setup_Autogen.h is included."
#endif
#ifndef TFT_HEIGHT
#  warning "TFT_HEIGHT not set — ensure .tft_setup/User_Setup_Autogen.h is included."
#endif

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("\n[Boot] ESP32 Marauder Rewired (linked build)");

  // Build/Register all tools before entering menu:
  init_tool_registry();

  // Entry point provided by CustomFunctions library
  showMainMenu();
}

void loop() {
  // Keep loop lean; UI handles its own updates/callbacks
  delay(10);
}
