#include <Arduino.h>
#include "CustomFunctions.h"

namespace {
// accept RAM strings
void _log(const char* s) { Serial.print(s); }
void _logln(const char* s) { Serial.println(s); }
// accept flash strings F("…")
void _log(const __FlashStringHelper* s) { Serial.print(s); }
void _logln(const __FlashStringHelper* s) { Serial.println(s); }

// little banner
void _banner() {
  _logln(F("=== Menu ==="));
}

// draw a basic menu (project-agnostic)
void _drawMenu() {
  _banner();
  _logln(F("1) Sub: Wi-Fi"));
  _logln(F("2) Sub: Bluetooth"));
  _logln(F("3) Sub: Storage"));
  _logln(F("4) Sub: Settings"));
  _logln(F("--------------------------"));
  _logln(F("Type a number or 'menu' to redraw."));
}
} // anon ns

// --------- public global logging wrappers -----------
void log(const char* s) { _log(s); }
void logln(const char* s) { _logln(s); }
void log(const __FlashStringHelper* s) { _log(s); }
void logln(const __FlashStringHelper* s) { _logln(s); }

// --------- library-owned global menu function -----------
void showMainMenu() {
  _drawMenu();
}
//--------void init_tool_registry();---------
void init_tool_registry() {
  static bool initialized = false;
  if (initialized) return;
  initialized = true;
}
// --------- namespaced helpers -----------
namespace Custom {

void init() {
  if (!Serial) {
    Serial.begin(115200);
    delay(50);
  }
}

void tick() {
  // place periodic tasks here if you want
}

uint32_t uptimeSeconds() {
  return static_cast<uint32_t>(millis() / 1000);
}

void handleCommand(const String& cmdIn) {
  String cmd = cmdIn;
  cmd.trim();
  cmd.toLowerCase();

  if (cmd == "menu" || cmd == "m") {
    ::showMainMenu();
    return;
  }

  if (cmd == "1") {
    _logln(F("[Custom] Wi-Fi selected"));
  } else if (cmd == "2") {
    _logln(F("[Custom] Bluetooth selected"));
  } else if (cmd == "3") {
    _logln(F("[Custom] Storage selected"));
  } else if (cmd == "4") {
    _logln(F("[Custom] Settings selected"));
  } else {
    _logln(F("[Custom] Unknown command. Type 'menu'."));
  }
}

} // namespace Custom