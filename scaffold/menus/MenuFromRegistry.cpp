#include "MenuFromRegistry.h"
#include "ToolRegistry.h"

void showMainMenu() {
  Serial.println();
  Serial.println(F("=== Marauder Main Menu (demo) ==="));
  for (size_t i = 0; i < tool_count(); ++i) {
    const auto& it = tool_at(i);
    Serial.print(F("  "));
    Serial.print(i);
    Serial.print(F(": "));
    Serial.println(it.label);
  }
  Serial.println(F("(Serial-demo only)"));
}
