#include "MenuFromRegistry.h"
#include "ToolRegistry.h"

void showMainMenu() {
  Serial.println(F("=== Main Menu ==="));
  for (size_t i = 0; i < toolRegistry.size(); i++) {
    Serial.printf("%d: %s\n", (int)i + 1, toolRegistry[i].name.c_str());
  }
}
