#include <Arduino.h>
#include "menus/MenuFromRegistry.h"
#include "menus/ToolRegistry.h"
#include "menus/RegistryInit.h"
#Include <CustomFunctions.h>

void setup() {
  Serial.begin(115200);
  delay(100);
  init_tool_registry();
  showMainMenu();
}

void loop() {
  // Minimal idle loop for now
  delay(10);
}
