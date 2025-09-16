#pragma once
#include <Arduino.h>
#include <functional>

struct Tool {
  String name;
  std::function<void(void)> action;
};
