#include <Arduino.h>
#include <CustomFunctions.h>

// NOTE: do NOT use extern "C" here. We want normal C++ linkage so calls resolve.
void init_tool_registry();
void showMainMenu();

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println(F("[boot] setup() starting"));
  init_tool_registry();
  showMainMenu();
}

void loop() {
  // Keep it simple for now
  delay(10);
}
