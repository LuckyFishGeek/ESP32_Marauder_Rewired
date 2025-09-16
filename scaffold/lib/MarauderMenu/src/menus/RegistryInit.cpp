#include "RegistryInit.h"
#include "ToolRegistry.h"

void init_tool_registry() {
  // Example tools
  register_tool({"WiFi Scan", [](){ Serial.println("WiFi Scan triggered"); }});
  register_tool({"Bluetooth Scan", [](){ Serial.println("Bluetooth Scan triggered"); }});
}
