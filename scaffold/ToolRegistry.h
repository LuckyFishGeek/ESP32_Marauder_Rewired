#pragma once
#include <Arduino.h>
#include <functional>
#include <map>
#include <vector>

struct ToolEntry {
  String name;
  std::function<void(void)> onLaunch; // user-defined, may create/run static instance
};

class ToolRegistry {
public:
  static ToolRegistry& instance();
  void registerTool(const String& menuPath, const ToolEntry& entry);
  const std::vector<ToolEntry>& getTools(const String& menuPath) const;
private:
  std::map<String, std::vector<ToolEntry>> tree;
};
