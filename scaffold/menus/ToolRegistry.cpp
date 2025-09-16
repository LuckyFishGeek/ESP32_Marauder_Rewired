#include "ToolRegistry.h"

namespace {
  static std::vector<SimpleMenuItem> tools;
}

namespace ToolRegistry {
  void registerTool(const SimpleMenuItem& item) { tools.push_back(item); }
  const std::vector<SimpleMenuItem>& getTools() { return tools; }
  void clearTools() { tools.clear(); }
}
