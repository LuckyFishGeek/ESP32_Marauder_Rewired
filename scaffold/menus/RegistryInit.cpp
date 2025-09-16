#include "RegistryInit.h"
#include "ToolRegistry.h"
#include <Arduino.h>

static std::function<void(void)> stub(const char* name){
  return [name](){ Serial.print(F("[Tool] ")); Serial.print(name); Serial.println(F(" launched (stub)")); };
}

void init_tool_registry() {
  ToolRegistry::clearTools();

  // WiFi
  ToolRegistry::registerTool({ "WiFi/Scanners - AP Scanner", stub("AP Scanner") });
  ToolRegistry::registerTool({ "WiFi/Scanners - Client Scanner", stub("Client Scanner") });
  ToolRegistry::registerTool({ "WiFi/Scanners - Channel Scanner", stub("Channel Scanner") });
  ToolRegistry::registerTool({ "WiFi/Sniffers - Beacon Sniffer", stub("Beacon Sniffer") });
  ToolRegistry::registerTool({ "WiFi/Sniffers - Probe Sniffer", stub("Probe Sniffer") });
  ToolRegistry::registerTool({ "WiFi/Sniffers - Deauth Sniffer", stub("Deauth Sniffer") });
  ToolRegistry::registerTool({ "WiFi/Wardriving - Start Wardrive", stub("Start Wardrive") });
  ToolRegistry::registerTool({ "WiFi/Wardriving - Export Wardrive", stub("Export Wardrive Log") });
  ToolRegistry::registerTool({ "WiFi/Attacks - Deauth Attack", stub("Deauth Attack") });
  ToolRegistry::registerTool({ "WiFi/Attacks - Beacon Flood", stub("Beacon Flood") });
  ToolRegistry::registerTool({ "WiFi/Attacks - Probe Flood", stub("Probe Flood") });

  // Bluetooth
  ToolRegistry::registerTool({ "Bluetooth/Sniffers - BLE Scanner", stub("BLE Scanner") });
  ToolRegistry::registerTool({ "Bluetooth/Sniffers - Classic Scan", stub("Classic Scan") });
  ToolRegistry::registerTool({ "Bluetooth/Sniffers - Adv Packet Sniffer", stub("Adv Packet Sniffer") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - Sour Apple", stub("Sour Apple") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - Swiftpair Spam", stub("Swiftpair Spam") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - Flipper BLE Spam", stub("Flipper BLE Spam") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - BLE Spam All", stub("BLE Spam All") });
  ToolRegistry::registerTool({ "Bluetooth/Attacks - Spoof Airtag", stub("Spoof Airtag") });

  // Device
  ToolRegistry::registerTool({ "Device - Update Firmware", stub("Update Firmware") });
  ToolRegistry::registerTool({ "Device - Save/Load Files", stub("Save/Load Files") });
  ToolRegistry::registerTool({ "Device - Format SD Files", stub("Format SD Files") });
  ToolRegistry::registerTool({ "Device - GPS Data", stub("GPS Data") });
  ToolRegistry::registerTool({ "Device - NMEA Stream", stub("NMEA Stream") });
  ToolRegistry::registerTool({ "Device - GPS Tracker", stub("GPS Tracker") });
  ToolRegistry::registerTool({ "Device - GPS POI", stub("GPS POI") });
}
