#include "MenuFromRegistry.h"
#include "RegistryInit.h"   // if needed
#include "ToolRegistry.h"   // if you plan to fetch items

// If you already have some renderer function, call it here.
// For now, keep it trivial so the build passes; we can expand later.
void showMainMenu() {
  // Minimal placeholder so compile succeeds
  Serial.println(F("[menu] showMainMenu() placeholder"));
  // TODO: pull items from registry and draw them when display stack is ready
  // Example (later):
  // auto items = getMainMenuItems();
  // drawMenu(items);
}
