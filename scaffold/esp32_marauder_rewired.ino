#include <Arduino.h>
#include <MarauderMenu.h>   // <? this is the trigger so Arduino builds the local lib

void setup() {
  Serial.begin(115200);
  delay(100);
  init_tool_registry();
  showMainMenu();
}

void loop() {
  // for now, nothing long-running ? just yield
  delay(10);
}
