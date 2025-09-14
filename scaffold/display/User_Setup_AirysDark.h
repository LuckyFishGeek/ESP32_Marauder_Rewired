// -----------------------------------------------------------------------------
// User_Setup_ILI9341_2_8_SPI.h  (for TFT_eSPI)
// 2.8" TFT, 240x320, SPI, ILI9341 controller, optional SD socket.
// Capacitive touch (FT62xx/GT9xx etc.) is I2C and handled by a separate lib.
// -----------------------------------------------------------------------------
// This header is safe with your workflow:
// - You can override any pin here via -D at compile time (from CSV/workflow).
//   e.g. -DTFT_CS=5 -DTFT_DC=2 -DTFT_RST=4 -DTFT_BL=15 -DSPI_FREQUENCY=40000000
// -----------------------------------------------------------------------------

#pragma once

// ---- Panel driver ----
#define ILI9341_DRIVER

// ---- Display size ----
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// ---- SPI host (ESP32) ----
#ifndef TFT_SPI_HOST
  // HSPI is common for external displays; VSPI also works. Leave undefined to use default.
  // #define TFT_SPI_HOST HSPI
#endif

// ---- SPI pins (defaults are common on ESP32; override if needed) ----
// NOTE: SCLK/MOSI/MISO are taken from the SPI host unless you define them.
#ifndef TFT_MOSI
  #define TFT_MOSI 23
#endif
#ifndef TFT_MISO
  #define TFT_MISO 19
#endif
#ifndef TFT_SCLK
  #define TFT_SCLK 18
#endif

#ifndef TFT_CS
  #define TFT_CS 5         // Chip select
#endif
#ifndef TFT_DC
  #define TFT_DC 2         // Data/Command
#endif
#ifndef TFT_RST
  #define TFT_RST 4        // Reset (or set to -1 and tie RST high)
#endif

// ---- Backlight (optional; PWM capable pin recommended) ----
#ifndef TFT_BL
  #define TFT_BL 15        // Set to -1 if your board has fixed backlight
#endif
#ifndef TFT_BACKLIGHT_ON
  #define TFT_BACKLIGHT_ON HIGH
#endif

// ---- SPI clocking ----
#ifndef SPI_FREQUENCY
  #define SPI_FREQUENCY 40000000   // 40 MHz is fine for ILI9341 + quality wiring
#endif
#ifndef SPI_READ_FREQUENCY
  #define SPI_READ_FREQUENCY 20000000
#endif
#ifndef SPI_TOUCH_FREQUENCY
  #define SPI_TOUCH_FREQUENCY 2500000
#endif

// ---- Color / rotation tweaks (optional) ----
// #define TFT_INVERSION_ON
// #define TFT_RGB_ORDER TFT_RGB  // or TFT_BGR

// ---- Font & sprite options (optional, keep light for size) ----
#define LOAD_GLCD   // Font 1
#define LOAD_FONT2  // Small 16
#define LOAD_FONT4  // Medium 26
// #define LOAD_FONT6  // Large 48
// #define LOAD_FONT7  // 7-seg 48
// #define LOAD_FONT8  // Large 75
#define LOAD_GFXFF
#define SMOOTH_FONT

// ---- SD card on the module (optional) ----
// If you use the on-board µSD (typically CS=4 or 5), define it here.
// Override with -DSD_CS=<pin> from workflow if different.
#ifndef SD_CS
  // #define SD_CS 13
#endif

// ---- Touch note ----
// This board says "Capacitive Touch". TFT_eSPI's built-in touch support
// targets XPT2046 (resistive). For capacitive (e.g. FT6236/GT911), use a
// separate library via I2C. Example default I2C pins on ESP32 are SDA=21, SCL=22.
// Define your touch lib pins in your sketch or via a separate config.
