// ==========================================================
// User Setup for ESP32-3248S035 with ILI9488 (480x320) TFT
// ==========================================================

#define USER_SETUP_ID 3248

// ---------------- TFT SPI pins ----------------
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4

// TFT parameters
#define ILI9488_DRIVER
#define TFT_RGB_ORDER TFT_BGR
#define SPI_FREQUENCY 40000000   // 40 MHz (safe max for ILI9488)
#define SPI_READ_FREQUENCY 20000000
#define SPI_TOUCH_FREQUENCY 2500000

// ---------------- Touch (XPT2046) ----------------
// Shares SPI bus with TFT
#define TOUCH_CS              33   // Touch chip-select
#define TOUCH_IRQ             36   // Touch IRQ / PENIRQ (optional)
#define SPI_TOUCH_FREQUENCY   2500000  // Reliable touch freq

// ---------------- Display size ----------------
#define TFT_WIDTH  320
#define TFT_HEIGHT 480

// ---------------- Fonts ----------------
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

// Smooth fonts
#define SMOOTH_FONT

// ---------------- Options ----------------
// Enable support for 16-bit parallel (not used here)
// #define TFT_PARALLEL_16_DRIVER