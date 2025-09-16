#include <Arduino.h>
#include <CustomFunctions.h>

void setup() {
  Serial.begin(115200);
  delay(100);
  Custom::init();
  Custom::showMainMenu();
}

void loop() {
  Custom::tick();
  delay(10);
}
