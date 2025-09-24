#include "RegistryInit.h"
#include "ToolRegistry.h"
#include "MenuTypes.h"

// Example no-op handlers (replace with your actual handlers as desired)
static void noop_action() {
  // placeholder
}

void init_tool_registry() {
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

  registry_clear();

  // Register a couple of safe placeholder tools so menu population has content.
  registry_add(ToolEntry("about", "About / Info", ToolKind::Page, noop_action));
  registry_add(ToolEntry("wifi_scan", "WiFi Scanner", ToolKind::Action, noop_action));
  registry_add(ToolEntry("ble_scan", "BLE Scanner", ToolKind::Action, noop_action));
}
