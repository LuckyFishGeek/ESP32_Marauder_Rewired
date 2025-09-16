#include <Arduino.h>
#include <MarauderMenu.h>   // this brings in all menus/registries

void setup() {
  Serial.begin(115200);
  delay(100);

  // initialize registry
  init_tool_registry();

  // show main menu
  showMainMenu();
}

void loop() {
  // placeholder loop
  delay(10);
}
