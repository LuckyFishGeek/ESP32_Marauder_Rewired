#pragma once
#include <Arduino.h>

namespace Custom {

// Example utility: safe logging
void logln(const char* msg);

// Example: startup banner
void showBanner();

// Example: free heap report
void printHeapInfo();

// Add more helpers here...

} // namespace Custom