#include "ToolRegistry.h"
#include <vector>

static std::vector<SimpleMenuItem> REGISTRY;

void register_tool(const SimpleMenuItem& item) {
  REGISTRY.push_back(item);
}

size_t tool_count() {
  return REGISTRY.size();
}

const SimpleMenuItem& tool_at(size_t idx) {
  return REGISTRY.at(idx);
}
