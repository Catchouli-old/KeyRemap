#include "KeyMap.h"

#include <stdio.h>

namespace kr
{
    KRDLL_API KeyMap::KeyMap(KeyMapType type)
    {
        switch (type)
        {
        case KeyMapType::QWERTY:
            initQwerty();
            break;
        case KeyMapType::DVORAK:
            initDvorak();
            break;
        case KeyMapType::COLEMAK:
            initColemak();
            break;
        default:
            fprintf(stderr, "Unknown key map type, defaulting to qwerty\n");
            initQwerty();
            break;
        }
    }

    void KRDLL_API KeyMap::initQwerty()
    {
        for (int i = 0; i < VK_COUNT; ++i)
        {
            vkReplace[i] = i;
        }
    }

    void KRDLL_API KeyMap::initDvorak()
    {
        // Init defaults
        initQwerty();

        // Custom
        // Letters
        vkReplace['A'] = 'A';
        vkReplace['N'] = 'B';
        vkReplace['I'] = 'C';
        vkReplace['H'] = 'D';
        vkReplace['D'] = 'E';
        vkReplace['Y'] = 'F';
        vkReplace['U'] = 'G';
        vkReplace['C'] = 'J';
        vkReplace['F'] = 'U';
        vkReplace['G'] = 'I';
        vkReplace['J'] = 'H';
        vkReplace['K'] = 'T';
        vkReplace['L'] = 'N';
        vkReplace['M'] = 'M';
        vkReplace['O'] = 'R';
        vkReplace['P'] = 'L';
        vkReplace['R'] = 'P';
        vkReplace['S'] = 'O';
        vkReplace['V'] = 'K';
        vkReplace['X'] = 'Q';
        vkReplace[VK_OEM_1 /* ;: */] = 'S';
        vkReplace[VK_OEM_PERIOD] = 'V';
        vkReplace[VK_OEM_COMMA] = 'W';
        vkReplace['B'] = 'X';
        vkReplace['T'] = 'Y';
        vkReplace[VK_OEM_2 /* /? */] = 'Z';

        // Puctuation
        vkReplace[VK_OEM_MINUS] = VK_OEM_4 /* [{ */;
        vkReplace[VK_OEM_PLUS] = VK_OEM_6 /* }] */;
        vkReplace[VK_OEM_4 /* [{ */] = VK_OEM_2 /* /? */;
        vkReplace[VK_OEM_6 /* }] */] = VK_OEM_PLUS;
        vkReplace['W'] = VK_OEM_COMMA;
        vkReplace['E'] = VK_OEM_PERIOD;
        vkReplace['Z'] = VK_OEM_1 /* :; */;
        vkReplace[VK_OEM_7 /* '" */] = VK_OEM_MINUS;
    }

    void KRDLL_API KeyMap::initColemak()
    {
        // Init defaults
        initQwerty();

        // Custom
        // Letters
        vkReplace['D'] = 'S';
        vkReplace['E'] = 'F';
        vkReplace['F'] = 'T';
        vkReplace['G'] = 'D';
        vkReplace['U'] = 'L';
        vkReplace['I'] = 'U';
        vkReplace['J'] = 'N';
        vkReplace['K'] = 'E';
        vkReplace['L'] = 'I';
        vkReplace['N'] = 'K';
        vkReplace['O'] = 'Y';
        vkReplace['P'] = VK_OEM_1 /* :; */;
        vkReplace['R'] = 'P';
        vkReplace['S'] = 'R';
        vkReplace['T'] = 'G';
        vkReplace['Y'] = 'J';
        vkReplace[VK_OEM_1 /* :; */] = 'O';
    }
}