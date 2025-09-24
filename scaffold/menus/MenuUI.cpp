#include "config.h"
#include "MenuUI.h"

void MenuUI::begin(TFT_eSPI* tft, uint8_t rotation) {
  _tft = tft;
  _tft->init();
  _tft->setRotation(rotation);
  _w = _tft->width();
  _h = _tft->height();
  _tft->fillScreen(C_BLACK);
}

void MenuUI::showSplash(const char* titleTop, const char* titleMid, const char* version) {
  _tft->fillScreen(C_BLACK);

  _tft->setTextDatum(MC_DATUM);
  _tft->setTextColor(C_WHITE, C_BLACK);

  // Top line
  _tft->setTextFont(2);
  _tft->setTextSize(2);
  _tft->drawString(titleTop, _w/2, _h/2 - 36);

  // Middle line (brand)
  _tft->setTextFont(4);
  _tft->setTextSize(1);
  _tft->setTextColor(C_WHITE, C_BLACK);
  _tft->drawString(titleMid, _w/2, _h/2 - 6);

  // Version
  _tft->setTextFont(2);
  _tft->setTextSize(1);
  _tft->setTextColor(C_GRAY, C_BLACK);
  _tft->drawString(String("{") + "Show version" + "}: " + version, _w/2, _h/2 + 16);

  // Initializing…
  _tft->setTextColor(C_GRAY, C_BLACK);
  _tft->drawString("Initializing", _w/2, _h/2 + 36);

  _tft->drawRect(6, 6, _w-12, _h-12, C_GRAY);
}

void MenuUI::showMainMenu() {
  _tft->fillScreen(C_BLACK);
  _tft->setTextDatum(TL_DATUM);

  // Title
  _tft->setTextColor(C_WHITE, C_BLACK);
  _tft->setTextFont(4);
  _tft->setTextSize(1);
  _tft->drawString("ESP32", 10, 6);

  // Grid of tiles (2 columns x 3 rows; last row centered)
  const int16_t pad = 10;
  const int16_t tileW = (_w - pad*3) / 2;
  const int16_t tileH = (_h - 48 - pad*4) / 3; // leave space for title

  int16_t x1 = pad, x2 = pad*2 + tileW;
  int16_t y0 = 40, y1 = y0 + pad + tileH, y2 = y1 + pad + tileH;

  // Row 1
  drawTile(x1, y0, tileW, tileH, "WIFI",     C_GREEN,  C_GREEN);
  iconWiFi(x1 + tileW/2, y0 + tileH/2 - 6, C_GREEN);

  drawTile(x2, y0, tileW, tileH, "Bluetooth", C_LBLUE,  C_LBLUE);
  iconBT(x2 + tileW/2, y0 + tileH/2 - 6, C_LBLUE);

  // Row 2
  drawTile(x1, y1, tileW, tileH, "GPS",      C_RED,    C_RED);
  iconGPS(x1 + tileW/2, y1 + tileH/2 - 2, C_RED);

  drawTile(x2, y1, tileW, tileH, "Device",   C_BLUE,   C_BLUE);
  iconDevice(x2 + tileW/2, y1 + tileH/2 - 4, C_BLUE);

  // Row 3 (center the reboot tile)
  int16_t rx = (_w - tileW)/2;
  drawTile(rx, y2, tileW, tileH, "Reboot",   C_WHITE,  C_WHITE);
  iconReboot(rx + tileW/2, y2 + tileH/2 - 4, C_WHITE);
}

/* ---------- helpers ---------- */

void MenuUI::drawTile(int16_t x, int16_t y, int16_t w, int16_t h,
                      const char* label, uint16_t fg, uint16_t border) {
  _tft->drawRoundRect(x, y, w, h, 8, border);
  // label
  _tft->setTextDatum(MC_DATUM);
  _tft->setTextFont(2);
  _tft->setTextSize(1);
  _tft->setTextColor(fg, C_BLACK);
  _tft->drawString(label, x + w/2, y + h - 12);
}

// Simple vector-ish icons (no bitmaps needed)
void MenuUI::iconWiFi(int16_t cx, int16_t cy, uint16_t color) {
  _tft->drawArc(cx, cy, 26, 24, 40, 140, color, C_BLACK);
  _tft->drawArc(cx, cy, 20, 18, 40, 140, color, C_BLACK);
  _tft->drawArc(cx, cy, 14, 12, 40, 140, color, C_BLACK);
  _tft->fillCircle(cx, cy+10, 3, color);
}

void MenuUI::iconBT(int16_t cx, int16_t cy, uint16_t color) {
  // A simple BT rune
  int16_t s = 12;
  _tft->drawLine(cx, cy-16, cx, cy+16, color);
  _tft->drawLine(cx, cy-16, cx+s, cy-6, color);
  _tft->drawLine(cx+s, cy-6, cx, cy+2, color);
  _tft->drawLine(cx, cy+2, cx+s, cy+12, color);
  _tft->drawLine(cx+s, cy+12, cx, cy+16, color);
}

void MenuUI::iconGPS(int16_t cx, int16_t cy, uint16_t color) {
  _tft->drawCircle(cx, cy, 10, color);
  _tft->drawLine(cx-12, cy, cx+12, cy, color);
  _tft->drawLine(cx, cy-12, cx, cy+12, color);
  _tft->fillCircle(cx, cy, 3, color);
}

void MenuUI::iconDevice(int16_t cx, int16_t cy, uint16_t color) {
  // a stylized "M"
  _tft->setTextDatum(MC_DATUM);
  _tft->setTextColor(color, C_BLACK);
  _tft->setTextFont(4);
  _tft->setTextSize(1);
  _tft->drawString("M", cx, cy);
}

void MenuUI::iconReboot(int16_t cx, int16_t cy, uint16_t color) {
  _tft->drawCircle(cx, cy, 12, color);
  _tft->drawLine(cx+12, cy, cx+6, cy-6, color);
  _tft->drawLine(cx+12, cy, cx+6, cy+6, color);
}
