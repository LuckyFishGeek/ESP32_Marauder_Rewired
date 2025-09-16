#include <Arduino.h>
#include <vector>
#include "ToolRegistry.h"

static std::vector<SimpleMenuItem> g_registry;

std::vector<SimpleMenuItem>& tool_registry() {
  return g_registry;
}

void register_tool(const String& label, std::function<void(void)> onSelect) {
  g_registry.push_back({label, onSelect});
}
