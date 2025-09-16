#include <Arduino.h>

// Menu/registry system
#include "menus/MenuTypes.h"
#include "menus/MenuFromRegistry.h"
#include "menus/ToolRegistry.h"
#include "menus/RegistryInit.h"

void setup() {
  Serial.begin(115200);
  delay(200);

  Serial.println(F("=== ESP32 Marauder Rewired ==="));
  Serial.println(F("Booting menu/registry system..."));

  // Initialize registries
  init_tool_registry();

  // Show the menu (Serial-only for now)
  showMainMenu();
}

void loop() {
  // TODO: when you wire up UI input, poll it here and dispatch selections
  delay(50); // keep WDT happy
}
