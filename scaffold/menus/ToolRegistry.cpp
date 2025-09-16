#include "ToolRegistry.h"
#include "RegistryInit.h"

void registerTools() {
    auto& reg = getRegistry();

    reg.push_back({"WiFi Scanner", [](){ /* start WiFi scan */ }});
    reg.push_back({"Bluetooth Scan", [](){ /* start BT scan */ }});
    reg.push_back({"Packet Sniffer", [](){ /* start sniffer */ }});
}
