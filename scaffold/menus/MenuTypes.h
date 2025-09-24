#pragma once
#include <Arduino.h>
#include <functional>
#include <vector>
#include <String.h>

// Basic menu/registry types used by our simple registry wiring.
// Keep this header small and dependency-free for easy inclusion.

enum class ToolKind : uint8_t {
  Action = 0,
  Page   = 1,
};

using ToolHandler = std::function<void(void)>;

struct ToolEntry {
  String     id;       // stable id, e.g. "wifi_scan"
  String     label;    // human label, e.g. "WiFi Scanner"
  ToolKind   kind;     // Action / Page
  ToolHandler run;     // callback
  ToolEntry() : kind(ToolKind::Action) {}
  ToolEntry(const String& i, const String& l, ToolKind k, ToolHandler f)
  : id(i), label(l), kind(k), run(f) {}
};

struct MenuItem {
  String  label;
  String  ref_id;   // maps to ToolEntry.id
  MenuItem() {}
  MenuItem(const String& l, const String& r) : label(l), ref_id(r) {}
};
