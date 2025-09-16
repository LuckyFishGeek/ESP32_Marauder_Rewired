#pragma once
#include <functional>
#include <Arduino.h>

// (keep your existing struct SimpleMenuItem and the rest of the header below)

struct SimpleMenuItem { String label; std::function<void(void)> onSelect; };
struct SimpleMenu { String path; std::vector<SimpleMenuItem> items; };

SimpleMenu buildMenuFromRegistry(const String& path);
// Serial UI: w=up, s=down, e=enter, b=back
void runSerialMenu(const String& path);
