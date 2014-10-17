#pragma once

#include "KRDLL.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace kr
{
    LRESULT CALLBACK messageHandler(int code, WPARAM wParam, LPARAM lParam);
}