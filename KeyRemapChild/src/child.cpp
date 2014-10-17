#include <Windows.h>
#include <cstdio>
#include <dos.h>

#include "Hooks.h"
#include "KeyMap.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance,
    _In_  HINSTANCE hPrevInstance,
    _In_  LPSTR lpCmdLine,
    _In_  int nCmdShow)
{
    kr::KeyMap keyMap(kr::KeyMapType::COLEMAK);
    
    // Init keyremap dll
    kr::updateKeymap(&keyMap);
    kr::insertHook();
    
    MSG msg;
    while (GetMessage(&msg, NULL, WM_HOTKEY, WM_HOTKEY))
    {
        // Break when we receive a WM_QUIT message from our parent
        if (msg.message == WM_QUIT)
        {
            break;
        }
    }

    // Deinit keyremap dll
    kr::removeHook();
}