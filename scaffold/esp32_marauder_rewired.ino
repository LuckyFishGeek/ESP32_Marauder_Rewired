#include <Arduino.h>
#include <TFT_eSPI.h>          // will pull pins + BL from User_Setup_Autogen.h
#include <CustomFunctions.h>   // your custom helpers (menu, registry, etc.)

// Forward-declare the menu function exposed by your custom lib
extern "C" void showMainMenu(void);

// Global TFT instance
TFT_eSPI tft;

static void splash() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.setTextFont(2); tft.setTextSize(2);
  tft.drawString("esp32 marauder", tft.width()/2, tft.height()/2 - 36);

  tft.setTextFont(4); tft.setTextSize(1);
  tft.drawString("AirysDark",      tft.width()/2, tft.height()/2 - 6);

#ifndef FW_VERSION
#define FW_VERSION "v0.1"
#endif
  tft.setTextFont(2); tft.setTextSize(1); tft.setTextColor(0xC618 /*gray*/, TFT_BLACK);
  tft.drawString(String("{Show version}: ") + FW_VERSION, tft.width()/2, tft.height()/2 + 16);
  tft.drawString("Initializing", tft.width()/2, tft.height()/2 + 36);

  tft.drawRect(6, 6, tft.width()-12, tft.height()-12, 0xC618 /*gray*/);
}

void setup() {
  Serial.begin(115200);
  delay(50);

  // Only do BL pin setup if the generator actually defined it
#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
#ifdef TFT_BACKLIGHT_ON
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
#else
  digitalWrite(TFT_BL, HIGH);
#endif
#endif

  tft.init();
  tft.setRotation(1);
  splash();

  Custom::init();
  showMainMenu();
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    Custom::handleCommand(line);
  }
  Custom::tick();
  delay(10);
}
