#include <Arduino.h>

#include "menus/MenuTypes.h"
#include "menus/MenuFromRegistry.h"
#include "menus/ToolRegistry.h"
#include "menus/RegistryInit.h"

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println(F("=== ESP32 Marauder Rewired ==="));
  Serial.println(F("Booting menu/registry system..."));
  init_tool_registry();
  showMainMenu();
}

void loop() {
  delay(50);
}
