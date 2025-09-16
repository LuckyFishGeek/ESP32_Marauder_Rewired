#include <Arduino.h>
#include <MarauderMenu.h>  // pulls in menus headers from the staged local lib

// Weak fallbacks so the link never fails if the library side is missing.
// The real non-weak versions from the library will override these.
extern "C" {
  __attribute__((weak)) void init_tool_registry() { /* no-op */ }
  __attribute__((weak)) void showMainMenu()       { Serial.println(F("[menu] (stub)")); }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  init_tool_registry();
  showMainMenu();
}

void loop() {
  delay(10);
}
