#pragma once
#include "config.h"
#include <vector>
#include "MenuTypes.h"

// Accessor to the global registry
std::vector<SimpleMenuItem>& tool_registry();

// Helper to add menu entries
void register_tool(const String& label, std::function<void(void)> onSelect);
