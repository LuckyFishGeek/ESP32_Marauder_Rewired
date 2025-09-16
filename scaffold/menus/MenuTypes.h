#pragma once
#include <functional>
#include <Arduino.h>

struct SimpleMenuItem {
  String label;
  std::function<void(void)> onSelect;
};
