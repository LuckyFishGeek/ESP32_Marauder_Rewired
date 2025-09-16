#pragma once
#include <vector>
#include "MenuTypes.h"

extern std::vector<Tool> toolRegistry;
void register_tool(const Tool &tool);
