MarauderMenu (local Arduino library)
------------------------------------
Drop the 'MarauderMenu' folder under scaffold/lib/ in your repo.

In your workflow, ensure you either:
  1) Unpack all folders under scaffold/lib into $HOME/Arduino/libraries, or
  2) Rsync this folder to $HOME/Arduino/libraries/MarauderMenu

Sketch include:
    #include <MarauderMenu.h>

This will compile all sources under src/menus/ and provide:
  - init_tool_registry()
  - showMainMenu()
