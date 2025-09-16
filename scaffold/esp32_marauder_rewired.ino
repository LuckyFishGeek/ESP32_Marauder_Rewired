// esp32_marauder_rewired.ino
#include <Arduino.h>

// Pull from scaffold/menu/
#include "menu/RegistryInit.h"     // getRegistry()
#include "menu/MenuTypes.h"        // SimpleMenuItem
#include "menu/ToolRegistry.h"     // registerTools()
#include "menu/MenuFromRegistry.h" // buildMenuFromRegistry()

void setup() {
  Serial.begin(115200);
  delay(100);

  // 1) Register all tools into the shared registry
  registerTools();

  // 2) Build the UI menu from the registry
  buildMenuFromRegistry();

  Serial.println(F("[Marauder] Boot complete"));
}

void loop() {
  // TODO: add your UI tick/input handling here
  // For now, just idle so the sketch runs cleanly
  delay(10);
}
