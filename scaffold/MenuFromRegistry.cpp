#include "MenuFromRegistry.h"
#include "ToolRegistry.h"
#include <Arduino.h>

// ---------- Simple hierarchical navigator over registry paths ----------
// Controls: w=up s=down e=enter b=back

struct SimpleMenuItem {
  String label;
  std::function<void(void)> onSelect;
};

static void drawList(const String& title, const std::vector<String>& items, int idx){
  Serial.println();
  Serial.print("["); Serial.print(title); Serial.println("]");
  for (int i=0;i<(int)items.size();++i){
    Serial.print((i==idx) ? "> " : "  ");
    Serial.println(items[i]);
  }
  Serial.println("w=up s=down e=enter b=back");
}

void runSerialNavigator(){
  auto& reg = ToolRegistry::instance();

  if (reg.getPaths().empty()){
    Serial.println("Registry is empty (no paths). Did you call init_tool_registry()?");
    return;
  }

  String prefix = "";
  while (true){
    auto children = reg.getChildPaths(prefix);
    auto tools    = reg.getTools(prefix);

    if (!children.empty()){
      int idx=0; drawList(prefix.length()?prefix:"<root>", children, idx);
      while (true){
        if (Serial.available()){
          char c=Serial.read();
          if (c=='w' && idx>0){ idx--; drawList(prefix.length()?prefix:"<root>", children, idx); }
          else if (c=='s' && idx+1<(int)children.size()){ idx++; drawList(prefix.length()?prefix:"<root>", children, idx); }
          else if (c=='e'){ prefix = children[idx]; break; }
          else if (c=='b'){
            if (prefix.length()==0) return;
            int slash = prefix.lastIndexOf('/');
            prefix = (slash>=0) ? prefix.substring(0, slash) : "";
            break;
          }
        }
        delay(10);
      }
    } else if (!tools.empty()){
      int idx=0;
      std::vector<SimpleMenuItem> items;
      items.reserve(tools.size());
      for (auto &t : tools) items.push_back(SimpleMenuItem{ t.name, t.onLaunch });

      while (true){
        Serial.println();
        Serial.print("["); Serial.print(prefix); Serial.println("]");
        for (int i=0;i<(int)items.size();++i){
          Serial.print((i==idx) ? "> " : "  ");
          Serial.println(items[i].label);
        }
        Serial.println("w=up s=down e=enter b=back");

        while (!Serial.available()) delay(10);
        char c=Serial.read();
        if (c=='w' && idx>0){ idx--; }
        else if (c=='s' && idx+1<(int)items.size()){ idx++; }
        else if (c=='e'){ auto fn = items[idx].onSelect; if(fn) fn(); }
        else if (c=='b'){ 
          int slash = prefix.lastIndexOf('/');
          prefix = (slash>=0) ? prefix.substring(0, slash) : "";
          break;
        }
      }
    } else {
      int slash = prefix.lastIndexOf('/');
      if (slash<0) return;
      prefix = (slash>=0) ? prefix.substring(0, slash) : "";
    }
  }
}
