\
#include "CustomFunctions.h"

namespace {

  void showBanner() {
  Serial.println(F("=== CustomFunctions Active ==="));
  }

  void printHeapInfo() {
  Serial.printf("[Heap] Free: %u bytes\n", ESP.getFreeHeap());
  }

  // Internal state
  Custom::LogFn g_logger = nullptr;
  // Simple feature map (very small, fixed for now)
  struct FeatureKV { const char* key; bool enabled; };
  FeatureKV g_features[] = {
    {"tft", false},
    {"serial_menu", true},
  };
  constexpr size_t NFEATURES = sizeof(g_features)/sizeof(g_features[0]);

  void logln(const char* s) {
    if (g_logger) { g_logger(s); }
    else { Serial.println(s); }
  }

  bool getFeature(const String& key) {
    for (size_t i=0;i<NFEATURES;i++) {
      if (key.equalsIgnoreCase(g_features[i].key)) return g_features[i].enabled;
    }
    return false;
  }

  void setFeatureKV(const String& key, bool on) {
    for (size_t i=0;i<NFEATURES;i++) {
      if (key.equalsIgnoreCase(g_features[i].key)) {
        g_features[i].enabled = on;
        return;
      }
    }
    // ignore unknown keys silently for now
  }
}

namespace Custom {

void init() {
  // Minimal bring-up; nothing heavy here (safe before peripherals exist).
  // You can seed features from compile-time defines if you want, e.g.:
  // setFeature("tft", #ifdef TFT_PRESENT true #else false #endif);
  logln(F("[CustomFunctions] init"));
}

void showMainMenu() {
  // For now just print to serial; this unblocks link errors
  // and gives a visible trace in CI.
  logln(F("=== Menu ==="));
  logln(F("1) sub"));
  logln(F("2) sub"));
  logln(F("3) sub"));
  logln(F("4) sub"));
  logln(F("--------------------------"));
  logln(F("Use Serial to type a command (e.g., '1')"));
}

void tick() {
  // Very simple serial command demo; safe no-op if nothing available.
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    handleCommand(cmd);
  }
}

void setLogger(LogFn fn) { g_logger = fn; }

void setFeature(const String& key, bool enabled) { setFeatureKV(key, enabled); }

void handleCommand(const String& cmd) {
  if (cmd.length() == 0) return;
  if (cmd == "1") {
    logln(F("[Custom]  selected"));
  } else if (cmd == "2") {
    logln(F("[Custom]  selected"));
  } else if (cmd == "3") {
    logln(F("[Custom]  selected"));
  } else if (cmd == "4") {
    logln(F("[Custom]  selected"));
  } else if (cmd.equalsIgnoreCase("menu")) {
    showMainMenu();
  } else {
    logln(F("[Custom] Unknown command. Type 'menu' to redraw."));
  }
}

} // namespace Custom
