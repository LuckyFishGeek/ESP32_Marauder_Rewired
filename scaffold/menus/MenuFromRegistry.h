#pragma once
<<<<<<< Updated upstream
#include <Arduino.h>
// If you need menu types or registries, include them here:
#include "MenuTypes.h"
#include "ToolRegistry.h"

// Public API used by the .ino
void showMainMenu();
=======
#include "MenuTypes.h"

// Primary entry point used by the .ino
void showMainMenu();

// Convenience: render a simple serial-only menu for debugging
void dumpRegisteredMenuToSerial();
>>>>>>> Stashed changes
