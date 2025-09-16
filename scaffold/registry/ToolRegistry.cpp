#include <Arduino.h>
#include "ToolRegistry.h"
#include "MenuTypes.h"

// If you want a global registry later, we can expose it via a getter.
// For now, keep this minimal and compile-safe.
void ToolRegistry::registerTools() {
  // TODO: push your tools into a shared registry here, e.g.:
  // extern std::vector<SimpleMenuItem>& getRegistry();
  // auto& reg = getRegistry();
  // reg.push_back({ "WiFi Scanner", [](){ /* launch scanner */ } });
  // reg.push_back({ "Bluetooth Scan", [](){ /* launch BLE scan */ } });

  // Temporary breadcrumb so you can see it ran:
  #if defined(SERIAL_DEBUG) || defined(ARDUINO)
    Serial.println(F("[ToolRegistry] registerTools() called"));
  #endif
}
