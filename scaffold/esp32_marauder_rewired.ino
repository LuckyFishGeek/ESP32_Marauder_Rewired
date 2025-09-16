#include <Arduino.h>
#include <CustomFunctions.h>   // <-- custom helpers (from your zipped libs)

#include "menus/MenuTypes.h"
#include "menus/ToolRegistry.h"
#include "menus/RegistryInit.h"
#include "menus/MenuFromRegistry.h"

void setup() {
  Serial.begin(115200);
  delay(100);

  // If your CustomFunctions library has an initializer, uncomment:
  // Custom::init();

  init_tool_registry();
  showMainMenu();
}

void loop() {
  // If your custom lib expects serial commands, you can forward them:
  // if (Serial.available()) {
  //   String cmd = Serial.readStringUntil('\n');
  //   Custom::handleCommand(cmd);
  // }

  delay(10);
}
