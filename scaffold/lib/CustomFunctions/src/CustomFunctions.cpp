#include "CustomFunctions.h"

namespace Custom {

void logln(const char* msg) {
  Serial.println(msg);
}

void showBanner() {
  Serial.println(F("=== CustomFunctions Active ==="));
}

void printHeapInfo() {
  Serial.printf("[Heap] Free: %u bytes\n", ESP.getFreeHeap());
}

} // namespace Custom