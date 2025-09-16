#include <Arduino.h>
#include "RegistryInit.h"       // sets up the registry and tool mapping
#include "MenuTypes.h"          // defines SimpleMenuItem and menus
#include "MenuFromRegistry.h"   // builds menus dynamically from registry

// --- Global state ---
MenuFromRegistry mainMenu;

void setup() {
  Serial.begin(115200);

  // Initialize modules/tools registry
  initRegistry();

  // Build menu from registry
  mainMenu.build();

  Serial.println("ESP32 Marauder Rewired initialized.");
}

void loop() {
  // Update the UI/menu system
  mainMenu.update();

  // Your normal Marauder logic goes here (Wi-Fi scanning, attacks, etc.)
  // For example: handleInputs(); processTools();
}
