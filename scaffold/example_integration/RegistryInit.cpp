#include "RegistryInit.h"
#include "../registry/ToolRegistry.h"

// Helper: generate a no-op tool callable that prints a label once
static std::function<void(void)> stubLaunch(const char* name){
  return [name](){
    Serial.print("[Tool] "); Serial.print(name); Serial.println(" launched (stub)");
  };
}

void init_tool_registry(){
  auto& reg = ToolRegistry::instance();

  // WiFi / Sniffers
  const char* wifiSniffers[] = {
    "Probe Request Sniff","Beacon Sniff","Deauth Sniff","Packet Count","EAPOL/PMKID Scan",
    "Packet Monitor","Channel Analyzer","Raw Capture","Detect Pwnagotchi","Detect Pineapple","Detect MultiSSID"
  };
  for(auto n: wifiSniffers) reg.registerTool("WiFi/Sniffers", ToolEntry{ n, stubLaunch(n) });

  // WiFi / Scanners
  const char* wifiScanners[] = { "Ping Scan","ARP Scan","Port Scan All","SSH Scan","Telnet Scan" };
  for(auto n: wifiScanners) reg.registerTool("WiFi/Scanners", ToolEntry{ n, stubLaunch(n) });

  // WiFi / Wardriving
  const char* wifiWard[] = { "Wardrive","Station Wardrive" };
  for(auto n: wifiWard) reg.registerTool("WiFi/Wardriving", ToolEntry{ n, stubLaunch(n) });

  // WiFi / Attacks (registered names only; stubs do nothing)
  const char* wifiAtk[] = {
    "Beacon Spam List","Beacon Spam Random","Rick Roll Beacon","Probe Req Flood","Evil Portal","Deauth Flood",
    "AP Clone Spam","Deauth Targeted","Karma","Bad Msg","Bad Msg Targeted","Assoc Sleep","Assoc Sleep Targ"
  };
  for(auto n: wifiAtk) reg.registerTool("WiFi/Attacks", ToolEntry{ n, stubLaunch(n) });

  // WiFi / General
  const char* wifiGen[] = {
    "Generate SSIDs","Select probe SSIDs","Add SSIDs","Clear SSIDs","Clear APs","Clear Stations",
    "Select APs","Select Stations","Select EP HTML File","View AP Info","Join WiFi","Join Saved WiFi","Set MACs","Shutdown WiFi"
  };
  for(auto n: wifiGen) reg.registerTool("WiFi/General", ToolEntry{ n, stubLaunch(n) });

  // Bluetooth / Sniffers
  const char* btSniff[] = { "Bluetooth Sniffer","Flipper Sniff","Airtag Sniff","BT Wardrive","BT Wardrive Continuous","Detect Card Skimmers","Bluetooth Analyzer" };
  for(auto n: btSniff) reg.registerTool("Bluetooth/Sniffers", ToolEntry{ n, stubLaunch(n) });

  // Bluetooth / Attacks
  const char* btAtk[] = { "Sour Apple","Swiftpair Spam","Samsung BLE Spam","Google BLE Spam","Flipper BLE Spam","BLE Spam All","Spoof Airtag","Spoof Airtag" };
  for(auto n: btAtk) reg.registerTool("Bluetooth/Bluetooth Attacks", ToolEntry{ n, stubLaunch(n) });

  // Device
  const char* deviceItems[] = { "Update Firmware","Save/Load Files","Language","Device Info","Settings","Delete SD Files","GPS Data","NMEA Stream","GPS Tracker","GPS POI" };
  for(auto n: deviceItems) reg.registerTool("Device", ToolEntry{ n, stubLaunch(n) });
}