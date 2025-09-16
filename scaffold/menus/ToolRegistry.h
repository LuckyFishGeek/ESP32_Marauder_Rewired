#pragma once
#include "MenuTypes.h"

// Register one tool/menu entry
void register_tool(const SimpleMenuItem& item);

// Query count and fetch by index (0..count-1)
size_t tool_count();
const SimpleMenuItem& tool_at(size_t idx);
