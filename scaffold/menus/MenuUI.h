#pragma once
#include <Arduino.h>
#include <vector>
#include "MenuTypes.h"

// Minimal UI model for building a menu tree from the registry.
// (Rendering is handled by the CustomFunctions library's showMainMenu().)
// We keep this in case other parts of your code need a list of items.

class MenuUI {
public:
  void clear() { items_.clear(); }
  void add(const MenuItem& mi) { items_.push_back(mi); }
  const std::vector<MenuItem>& items() const { return items_; }
private:
  std::vector<MenuItem> items_;
};
