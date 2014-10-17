#define KRDLL_EXPORTS
#include "KRDLL.h"
#include "MessageHandler.h"
#include "KeyMap.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
    IN DWORD nReason,
    IN LPVOID Reserved)
{
    bool init;

    if (nReason == DLL_PROCESS_ATTACH)
    {
        // Store DLL handle
        kr::dllHandle = hDllHandle;

        // Create a named file mapping object (for shared memory)
        kr::mapHandle = CreateFileMapping(
            INVALID_HANDLE_VALUE,   // Use paging file
            NULL,                   // Default security attributes
            PAGE_READWRITE,         // Read/write access
            0,                      // Size: high 32 bits
            sizeof(kr::KeyMap),     // Size: low 32 bits
            TEXT("keymapvalues2"));   // Name of map object;

        // Check if failed and return FALSE for not success
        if (kr::mapHandle == NULL)
            return FALSE;

        // Check if this is the first process to load this so we can initialise it
        init = (GetLastError() != ERROR_ALREADY_EXISTS);

        // Get a pointer to the file-mapped memory
        kr::keyMap = (kr::KeyMap*)MapViewOfFile(
            kr::mapHandle,      // The object to map view of
            FILE_MAP_WRITE,     // Read/write access
            0,                  // High offset
            0,                  // Low offset
            0);                 // default: map enttire file

        // Check for success
        if (kr::keyMap == NULL)
            return FALSE;

        // Initialise memory if this is the first process
        if (init)
        {
            // Initialise with default constructor
            kr::KeyMap defaultKeyMap;
            memcpy(kr::keyMap, &defaultKeyMap, sizeof(kr::KeyMap));
        }
    }
    else if (nReason == DLL_PROCESS_DETACH)
    {
        // Unset DLL handle
        kr::dllHandle = NULL;

        // Unmap shared memory
        UnmapViewOfFile(kr::keyMap);
        kr::keyMap = NULL;

        // Close the process's handle to the shared memory
        CloseHandle(kr::mapHandle);
        kr::mapHandle = NULL;
    }

    // Report success
    return TRUE;
}

namespace kr
{
    HINSTANCE dllHandle = NULL;
    HHOOK getMessageWndHook = NULL;
    HHOOK callWndHook = NULL;

    KeyMap* keyMap = NULL;
    HANDLE mapHandle = NULL;

    /* Update character conversion keymap */
    void KRDLL_API updateKeymap(kr::KeyMap* keyMap)
    {
        // Copy keymap
        memcpy(kr::keyMap, keyMap, sizeof(kr::KeyMap));
    }

    /* Insert windows hook for character conversion */
    void KRDLL_API insertHook()
    {
        // Insert hooks
        getMessageWndHook = SetWindowsHookEx(WH_GETMESSAGE, messageHandler, dllHandle, NULL);
        callWndHook = SetWindowsHookEx(WH_CALLWNDPROC, messageHandler, dllHandle, NULL);
    }

    /* Remove windows hook */
    void KRDLL_API removeHook()
    {
        // Disable hooks
        UnhookWindowsHookEx(getMessageWndHook);
        UnhookWindowsHookEx(callWndHook);

        // Unset handles
        callWndHook = NULL;
        getMessageWndHook = NULL;
    }
}