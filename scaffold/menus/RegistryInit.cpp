#include "RegistryInit.h"
#include "ToolRegistry.h"
#include <Arduino.h>

// Small helper to generate a stub action that logs the tool name.
static std::function<void(void)> make_stub_action(const char* name) {
  return [name]() {
    Serial.print("[Tool] ");
    Serial.print(name);
    Serial.println(" launched (stub)");
  };
}

void init_tool_registry() {
  // Clear before registering (idempotent)
  ToolRegistry::clearTools();

  // WiFi group
  ToolRegistry::registerTool({ "WiFi/Scanners - AP Scanner", make_stub_action("AP Scanner") });
  ToolRegistry::registerTool({ "WiFi/Scanners - Client Scanner", make_stub_action("Client Scanner") });
  ToolRegistry::registerTool({ "WiFi/Scanners - Channel Scanner", make_stub_action("Channel Scanner") });

  ToolRegistry::registerTool({ "WiFi/Sniffers - Beacon Sniffer", make_stub_action("Beacon Sniffer") });
  ToolRegistry::registerTool({ "WiFi/Sniffers - Probe Sniffer", make_stub_action("Probe Sniffer") });
  ToolRegistry::registerTool({ "WiFi/Sniffers - Deauth Sniffer", make_stub_action("Deauth Sniffer") });

  ToolRegistry::registerTool({ "WiFi/Wardriving - Start Wardrive", make_stub_action("Start Wardrive") });
  ToolRegistry::registerTool({ "WiFi/Wardriving - Export Wardrive", make_stub_action("Export Wardrive Log") });

  ToolRegistry::registerTool({ "WiFi/Attacks - Deauth Attack", make_stub_action("Deauth Attack") });
  ToolRegistry::registerTool({ "WiFi/Attacks - Beacon Flood", make_stub_action("Beacon Flood") });
  ToolRegistry::registerTool({ "WiFi/Attacks - Probe Flood", make_stub_action("Probe Flood") });

  // Bluetooth
  ToolRegistry::registerTool({ "Bluetooth/Sniffers - BLE Scanner", make_stub_action("BLE Scanner") });
  ToolRegistry::registerTool({ "Bluetooth/Sniffers - Classic Scan", make_stub_action("Classic Scan") });
  ToolRegistry::registerTool({ "Bluetooth/Sniffers - Adv Packet Sniffer", make_stub_action("Adv Packet Sniffer") });

  ToolRegistry::registerTool({ "Bluetooth/Attacks - Sour Apple", make_stub_action("Sour Apple") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - Swiftpair Spam", make_stub_action("Swiftpair Spam") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - Flipper BLE Spam", make_stub_action("Flipper BLE Spam") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - BLE Spam All", make_stub_action("BLE Spam All") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - Spoof Airtag", make_stub_action("Spoof Airtag") });

  // Device
  ToolRegistry::registerTool({ "Device - Update Firmware", make_stub_action("Update Firmware") });
  ToolRegistry::registerTool({ "Device - Save/Load Files", make_stub_action("Save/Load Files") });
  ToolRegistry::registerTool({ "Device - Format SD Files", make_stub_action("Format SD Files") });
  ToolRegistry::registerTool({ "Device - GPS Data", make_stub_action("GPS Data") });
  ToolRegistry::registerTool({ "Device - NMEA Stream", make_stub_action("NMEA Stream") });
  ToolRegistry::registerTool({ "Device - GPS Tracker", make_stub_action("GPS Tracker") });
  ToolRegistry::registerTool({ "Device - GPS POI", make_stub_action("GPS POI") });
}
