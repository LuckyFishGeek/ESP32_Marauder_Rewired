#include "MenuFromRegistry.h"

static std::vector<SimpleMenuItem> makeItems(const String& path){
  std::vector<SimpleMenuItem> v;
  for (auto &e : ToolRegistry::instance().getTools(path)){
    v.push_back(SimpleMenuItem{ e.name, e.onLaunch });
  }
  return v;
}

SimpleMenu buildMenuFromRegistry(const String& path){
  SimpleMenu m; m.path=path; m.items=makeItems(path); return m;
}

void runSerialMenu(const String& path){
  auto menu = buildMenuFromRegistry(path);
  int idx = 0;
  auto redraw = [&](){
    Serial.println(); Serial.print("[Menu] "); Serial.println(menu.path);
    for(size_t i=0;i<menu.items.size();++i){ Serial.print(i==idx?"> ":"  "); Serial.println(menu.items[i].label); }
    Serial.println("w=up s=down e=enter b=back");
  };
  redraw();
  while(true){
    if(Serial.available()){
      char c=Serial.read();
      if(c=='w' && idx>0){ idx--; redraw(); }
      else if(c=='s' && idx+1<(int)menu.items.size()){ idx++; redraw(); }
      else if(c=='e' && !menu.items.empty()){ auto fn = menu.items[idx].onSelect; if(fn) fn(); redraw(); }
      else if(c=='b'){ break; }
    }
    delay(10);
  }
}
