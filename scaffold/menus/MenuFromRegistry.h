#pragma once
#include "MenuTypes.h"

// Primary entry point used by the .ino
void showMainMenu();

// Convenience: render a simple serial-only menu for debugging
void dumpRegisteredMenuToSerial();
