#pragma once
#include <Arduino.h>
#include <functional>

struct SimpleMenuItem {
    String label;
    std::function<void(void)> onSelect;
};
