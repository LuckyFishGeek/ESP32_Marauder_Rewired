#pragma once
#include <Arduino.h>
#include <vector>
#include <functional>
#include "../registry/ToolRegistry.h"

struct SimpleMenuItem { String label; std::function<void(void)> onSelect; };
struct SimpleMenu { String path; std::vector<SimpleMenuItem> items; };

SimpleMenu buildMenuFromRegistry(const String& path);
// Serial UI: w=up, s=down, e=enter, b=back
void runSerialMenu(const String& path);
