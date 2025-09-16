#include "ToolRegistry.h"

std::vector<Tool> toolRegistry;

void register_tool(const Tool &tool) {
  toolRegistry.push_back(tool);
}
