#include "MenuFromRegistry.h"
#include "RegistryInit.h"

void buildMenuFromRegistry() {
    auto& reg = getRegistry();
    for (auto& item : reg) {
        Serial.println("Menu item: " + item.label);
        // Replace this with actual GUI rendering, e.g. addMenuItem(item.label, item.onSelect);
    }
}
