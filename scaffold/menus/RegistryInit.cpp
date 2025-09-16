#include "RegistryInit.h"
#include "ToolRegistry.h"

static void demo_hello() {
  Serial.println(F("Hello from demo_hello()"));
}
static void demo_scan() {
  Serial.println(F("Pretend WiFi scan… (demo)"));
}

void init_tool_registry() {
  register_tool(SimpleMenuItem{ "Hello", demo_hello });
  register_tool(SimpleMenuItem{ "Scan",  demo_scan  });
}
