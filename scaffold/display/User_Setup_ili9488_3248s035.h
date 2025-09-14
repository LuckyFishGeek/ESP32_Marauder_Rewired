// =======================================================
// TFT_eSPI setup for ESP32-3248S035 LCD (ILI9488 480x320)
// =======================================================

#define USER_SETUP_ID 3248

// Display driver
#define ILI9488_DRIVER

// Pins
#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST   4

// Touch not used by default, define if needed
// #define TOUCH_CS <pin>

// Colors and rotation
#define TFT_RGB_ORDER TFT_BGR
#define TFT_BACKLIGHT_ON HIGH

// Fonts
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

// Smooth fonts
#define SMOOTH_FONT
