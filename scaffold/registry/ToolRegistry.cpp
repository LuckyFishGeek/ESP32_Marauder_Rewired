#include "ToolRegistry.h"

ToolRegistry& ToolRegistry::instance(){ static ToolRegistry r; return r; }

void ToolRegistry::registerTool(const String& menuPath, const ToolEntry& entry){
  tree[menuPath].push_back(entry);
}

const std::vector<ToolEntry>& ToolRegistry::getTools(const String& menuPath) const {
  static const std::vector<ToolEntry> empty;
  auto it = tree.find(menuPath);
  if (it==tree.end()) return empty;
  return it->second;
}

std::vector<String> ToolRegistry::getPaths() const {
  std::vector<String> v; v.reserve(tree.size());
  for (auto &kv : tree) v.push_back(kv.first);
  return v;
}

std::vector<String> ToolRegistry::getChildPaths(const String& prefix) const {
  std::vector<String> out;
  const String needle = prefix.length() ? (prefix + "/") : String();
  for (auto &kv : tree){
    const String &p = kv.first;
    if (prefix.length()==0){
      int slash = p.indexOf('/');
      String top = (slash >= 0) ? p.substring(0, slash) : p;
      bool seen=false; for(auto &s: out) if (s==top) { seen=true; break; }
      if (!seen) out.push_back(top);
    } else {
      if (p.startsWith(needle)){
        int nextSlash = p.indexOf('/', needle.length());
        String child = (nextSlash >= 0) ? p.substring(0, nextSlash) : p;
        bool seen=false; for(auto &s: out) if (s==child) { seen=true; break; }
        if (!seen) out.push_back(child);
      }
    }
  }
  return out;
}
