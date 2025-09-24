#include "MenuFromRegistry.h"
#include "ToolRegistry.h"

void buildMainMenu(MenuUI& out) {
  out.clear();
  // Convert all registered tools into simple menu items.
  for (const auto& t : registry_all()) {
    out.add(MenuItem(t.label, t.id));
  }
}
