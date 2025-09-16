#pragma once
#include "MenuTypes.h"
#include <vector>

namespace ToolRegistry {
  void registerTool(const SimpleMenuItem& item);
  const std::vector<SimpleMenuItem>& getTools();
  void clearTools();
}
