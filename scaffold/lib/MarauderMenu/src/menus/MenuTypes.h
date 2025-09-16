#pragma once
#include <Arduino.h>
#include <functional>
#include <vector>

struct SimpleMenuItem {
    String label;
    std::function<void(void)> onSelect;
};
