#include <Arduino.h>

// Menu/registry system
#include "menus/MenuTypes.h"
#include "menus/MenuFromRegistry.h"
#include "menus/ToolRegistry.h"
#include "menus/RegistryInit.h"

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("=== ESP32 Marauder Rewired ===");
  Serial.println("Booting menu/registry system...");

  // Initialize registries
  initRegistries();

  // Example: show menu
  showMainMenu();
}

void loop() {
  // Run menu tasks
  loopMenu();

  // Small delay to avoid WDT
  delay(10);
}
