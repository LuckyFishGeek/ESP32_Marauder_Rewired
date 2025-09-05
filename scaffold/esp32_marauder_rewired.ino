#include <Arduino.h>
#include "RegistryInit.h"
#include "MenuFromRegistry.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  init_tool_registry();
  runSerialMenu("Main Menu");
}

void loop() {}
