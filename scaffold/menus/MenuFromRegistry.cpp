#include "MenuFromRegistry.h"
#include "ToolRegistry.h"
#include <Arduino.h>

static void printItem(const SimpleMenuItem& it, size_t idx) {
  Serial.print(idx + 1);
  Serial.print(": ");
  Serial.println(it.label);
}

void dumpRegisteredMenuToSerial() {
  Serial.println(F("=== Registered Tools ==="));
  const auto& tools = ToolRegistry::getTools();
  for (size_t i = 0; i < tools.size(); ++i) {
    printItem(tools[i], i);
  }
  Serial.println(F("========================="));
}

// Minimal top-level showMainMenu - prints to Serial and lets user pick later
void showMainMenu() {
  const auto& tools = ToolRegistry::getTools();
  if (tools.empty()) {
    Serial.println(F("[Menu] No registered tools."));
    return;
  }

  Serial.println(F("\n[Menu] Main Menu - (serial listing, no input in CI)"));
  for (size_t i = 0; i < tools.size(); ++i) {
    printItem(tools[i], i);
  }

  // No blocking Serial input in CI. On device, read input and call tools[idx].onSelect()
}
