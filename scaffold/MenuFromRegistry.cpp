#include <Arduino.h>
#include "MenuFromRegistry.h"
#include "MenuTypes.h"

// If/when you expose a real registry (vector<SimpleMenuItem>), use it here.
// This stub just proves linkage and avoids duplicate type definitions.
void MenuFromRegistry::buildMenu() {
  // Example: render or wire up a minimal "Menu"
  // In your real implementation, iterate the registry and create UI entries.
  #if defined(SERIAL_DEBUG) || defined(ARDUINO)
    Serial.println(F("[MenuFromRegistry] buildMenu() called"));
  #endif

  // TODO:
  // extern const std::vector<SimpleMenuItem>& getRegistry();
  // for (const auto& item : getRegistry()) { /* add to menu */ }
}
