#pragma once
#include <Arduino.h>
#include <vector>
#include "MenuTypes.h"

// Lightweight global registry for tools/pages.
// This is intentionally simple to avoid conflicts with other libs.

void registry_clear();
void registry_add(const ToolEntry& tool);
bool registry_has(const String& id);
const ToolEntry* registry_get(const String& id);
const std::vector<ToolEntry>& registry_all();
