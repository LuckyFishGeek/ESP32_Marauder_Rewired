#pragma once
#include ".autogen/config.h"
#include <functional>
#include <WString.h>

struct SimpleMenuItem {
  String label;
  std::function<void(void)> onSelect;
};
