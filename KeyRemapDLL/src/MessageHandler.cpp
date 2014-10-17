#define KRDLL_EXPORTS
#include "MessageHandler.h"
#include "KeyMap.h"

#include <stdio.h>
#include <string>

namespace kr
{
    LRESULT CALLBACK messageHandler(int code, WPARAM wParam, LPARAM lParam)
    {
        MSG* msg = (MSG*)lParam;

        if (msg->message == WM_KEYDOWN || msg->message == WM_KEYUP ||
            msg->message == WM_SYSKEYDOWN || msg->message == WM_SYSKEYUP)
        {
            // Replace character with value from kr::keyMapsk
            msg->wParam = kr::keyMap->vkReplace[msg->wParam];
        }

        // Forward message to next hook
        return CallNextHookEx(NULL, code, wParam, lParam);
    }
}