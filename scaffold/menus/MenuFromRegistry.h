#pragma once
#include <Arduino.h>
#include "MenuUI.h"

// Build a flat main menu list from the registered tools.
void buildMainMenu(MenuUI& out);

// NOTE: Do NOT declare showMainMenu() here. It is provided by the
// CustomFunctions library (void showMainMenu();). Including a declaration
// here (especially with extern "C") will cause linkage conflicts.
