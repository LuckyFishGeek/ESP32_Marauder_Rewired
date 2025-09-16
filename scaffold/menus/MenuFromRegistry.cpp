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

// Minimal top-level showMainMenu - prints to Serial and lets user pick by index
void showMainMenu() {
  const auto& tools = ToolRegistry::getTools();
  if (tools.empty()) {
    Serial.println(F("[Menu] No registered tools.")); 
    return;
  }

  Serial.println(F("\n[Menu] Main Menu - Select by number (serial-only):"));
  for (size_t i = 0; i < tools.size(); ++i) {
    printItem(tools[i], i);
  }

  Serial.println(F("(Menu is serial-only in CI; send selection via serial when interactive)"));
  // No blocking input in CI; this is a safe stub that doesn't attempt to read Serial.
  // In a real device you would read Serial or the input layer and call tools[idx].onSelect()
}
