#include "RegistryInit.h"

static std::vector<SimpleMenuItem> registry;

std::vector<SimpleMenuItem>& getRegistry() {
    return registry;
}
