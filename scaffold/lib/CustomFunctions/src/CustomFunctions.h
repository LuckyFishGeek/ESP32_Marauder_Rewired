#pragma once
#include <Arduino.h>

// All project-specific functions live in this library.
// Keep the public surface small and stable; add new APIs here as needed.
namespace Custom {

  // Example: startup banner
  void showBanner();

  // Example: free heap report
  void printHeapInfo();

  // Initialize any project‑level state (e.g., registry, IO, display hookup).
  void init();

  // Draw/print the main menu (safe even when no display is present).
  void showMainMenu();

  // Optional periodic tick to handle UI polling, timers, etc.
  void tick();

  // ----- Extension points you can wire up later -----
  // Example: attach a printf-like sink for UI logging
  typedef void (*LogFn)(const char*);
  void setLogger(LogFn fn);

  // Example: feature toggles you may want to drive from JSON/env
  void setFeature(const String& key, bool enabled);

  // Example: expose a simple command hook (for button/serial actions)
  void handleCommand(const String& cmd);
}
