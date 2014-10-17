#pragma once

#ifdef KRDLL_EXPORTS
    #define KRDLL_API __declspec(dllexport)
#else
    #define KRDLL_API __declspec(dllimport)
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace kr
{
    struct KeyMap;

    // Only available in the dll since they're per process
#ifdef KRDLL_EXPORTS
    extern HINSTANCE dllHandle;

    extern KeyMap* keyMap;
    extern HANDLE mapHandle;
#endif

    /* Update character conversion keymap */
    void KRDLL_API updateKeymap(kr::KeyMap* keyMap);

    /* Insert windows hook for character conversion */
    void KRDLL_API insertHook();

    /* Remove windows hook for character conversion */
    void KRDLL_API removeHook();
}