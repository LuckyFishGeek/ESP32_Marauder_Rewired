#include "ToolRegistry.h"

static std::vector<ToolEntry> g_tools;

void registry_clear() {
  g_tools.clear();
}

void registry_add(const ToolEntry& tool) {
  // Deduplicate by id.
  for (auto& t : g_tools) {
    if (t.id == tool.id) {
      t = tool;
      return;
    }
  }
  g_tools.push_back(tool);
}

bool registry_has(const String& id) {
  for (auto& t : g_tools) {
    if (t.id == id) return true;
  }
  return false;
}

const ToolEntry* registry_get(const String& id) {
  for (auto& t : g_tools) {
    if (t.id == id) return &t;
  }
  return nullptr;
}

const std::vector<ToolEntry>& registry_all() {
  return g_tools;
}
