#pragma once

#define KRDLL_EXPORTS
#include "KRDLL.h"

#define VK_COUNT 255

namespace kr
{
    enum class KeyMapType
    {
        QWERTY,
        DVORAK,
        COLEMAK
    };

    struct KeyMap
    {
    public:
        KRDLL_API KeyMap(KeyMapType type = KeyMapType::QWERTY);

        int vkReplace[VK_COUNT];

    protected:
        void KRDLL_API initQwerty();
        void KRDLL_API initDvorak();
        void KRDLL_API initColemak();
    };
}