#include <Arduino.h>
#include "RegistryInit.h"
#include "MenuFromRegistry.h"

void setup() {
  delay(50);
  Serial.begin(115200);
  while(!Serial) { delay(10); }

  init_tool_registry();   // from RegistryInit.cpp

  // Option A: run a submenu directly
  // runSerialMenu("WiFi/Sniffers");

  // Option B: navigator (recommended)
  runSerialNavigator();
}

void loop() {
  delay(50);
}
