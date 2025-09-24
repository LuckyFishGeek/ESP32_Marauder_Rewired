#include ".autogen/config.h"
#include <Arduino.h>
#include "MenuFromRegistry.h"
#include "ToolRegistry.h"

void showMainMenu() {
  Serial.println();
  Serial.println(F("==== ESP32 Marauder (menus in sketch) ===="));
  for (const auto& it : tool_registry()) {
    Serial.println(it.label);
  }
  Serial.println(F("-----------------------------------------"));
  Serial.println(F("Type 1..4 in Serial Monitor to simulate a pick."));
}
