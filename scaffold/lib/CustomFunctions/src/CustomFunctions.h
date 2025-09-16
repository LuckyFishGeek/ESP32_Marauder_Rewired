#pragma once
#include <Arduino.h>

// ---- Namespaced helpers you can call as Custom::init(), etc. ----
namespace Custom {
  void init();                         // call once in setup()
  void tick();                         // call often in loop() if you want
  void handleCommand(const String&);   // parse a serial command
  uint32_t uptimeSeconds();
}

// ---- Legacy/global helpers (intentionally global so old code compiles) ----
void showMainMenu();                   // owned & defined by this library

// Logging helpers that accept both RAM strings and F("…") flash strings.
void log(const char* s);
void logln(const char* s);
void log(const __FlashStringHelper* s);
void logln(const __FlashStringHelper* s);