#pragma once
#include <Arduino.h>
#include <functional>
#include <vector>

// A minimal, single source of truth for menu item types.
struct SimpleMenuItem {
    String label;
    std::function<void(void)> onSelect;
};
