#include "ToolRegistry.h"

ToolRegistry& ToolRegistry::instance(){ static ToolRegistry r; return r; }
void ToolRegistry::registerTool(const String& menuPath, const ToolEntry& entry){ tree[menuPath].push_back(entry); }
const std::vector<ToolEntry>& ToolRegistry::getTools(const String& menuPath) const {
  static const std::vector<ToolEntry> empty;
  auto it = tree.find(menuPath);
  if (it==tree.end()) return empty;
  return it->second;
}
