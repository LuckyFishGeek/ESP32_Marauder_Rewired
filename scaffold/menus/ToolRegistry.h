#pragma once
#include "MenuTypes.h"
#include <vector>

// Simple global registry API (C++ style). This provides compatibility
// with code expecting either a class-based or free-function based API.
namespace ToolRegistry {
    void registerTool(const SimpleMenuItem& item);
    const std::vector<SimpleMenuItem>& getTools();
    void clearTools();
}
