#include <Arduino.h>
#include <CustomFunctions.h>   // <-- custom helpers (from your zipped libs)

#include "menus/MenuTypes.h"
#include "menus/ToolRegistry.h"
#include "menus/RegistryInit.h"
#include "menus/MenuFromRegistry.h"




void setup() {
  Custom::init();
  showMainMenu();        // global function provided by the library
}

void loop() {
  // optional: forward serial input into the command handler
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    Custom::handleCommand(line);
  }
  Custom::tick();
  delay(10);
}
