#include "config.h"
#include <Arduino.h>
#include "RegistryInit.h"
#include "ToolRegistry.h"

static void demo_wifi()   { Serial.println("WiFi tools selected"); }
static void demo_bt()     { Serial.println("Bluetooth tools selected"); }
static void demo_storage(){ Serial.println("Storage selected"); }
static void demo_settings(){ Serial.println("Settings selected"); }

void init_tool_registry() {
  auto& reg = tool_registry();
  reg.clear();
  register_tool("1) WiFi tools",    demo_wifi);
  register_tool("2) Bluetooth",     demo_bt);
  register_tool("3) Storage",       demo_storage);
  register_tool("4) Settings",      demo_settings);
}
