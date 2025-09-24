#pragma once
#include ".autogen/config.h"
#include <TFT_eSPI.h>

// Brand/Version shown on splash
#ifndef FW_VERSION
#define FW_VERSION "v0.1"
#endif

// Colors
#define C_WHITE    TFT_WHITE
#define C_BLACK    TFT_BLACK
#define C_GREEN    TFT_GREEN
#define C_LBLUE    0x7D7C   // light-ish blue
#define C_RED      TFT_RED
#define C_BLUE     TFT_BLUE
#define C_GRAY     0xC618   // 50% gray

class MenuUI {
public:
  void begin(TFT_eSPI* tft, uint8_t rotation = 1);
  void showSplash(const char* titleTop = "esp32 marauder",
                  const char* titleMid = "AirysDark",
                  const char* version  = FW_VERSION);
  void showMainMenu();

  // future: handle touches / navigation, etc.

private:
  TFT_eSPI* _tft = nullptr;
  int16_t   _w = 0, _h = 0;

  // icon helpers
  void drawTile(int16_t x, int16_t y, int16_t w, int16_t h,
                const char* label, uint16_t fg, uint16_t border);
  void iconWiFi(int16_t cx, int16_t cy, uint16_t color);
  void iconBT(int16_t cx, int16_t cy, uint16_t color);
  void iconGPS(int16_t cx, int16_t cy, uint16_t color);
  void iconDevice(int16_t cx, int16_t cy, uint16_t color);
  void iconReboot(int16_t cx, int16_t cy, uint16_t color);
};
