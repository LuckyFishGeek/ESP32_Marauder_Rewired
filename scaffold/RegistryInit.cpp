#include "RegistryInit.h"
#include "ToolRegistry.h"
#include "MenuFromRegistry.h"

void RegistryInit::init() {
  // Register all tools
  ToolRegistry::registerTools();

  // Build menus from the registry
  MenuFromRegistry::buildMenu();
}
