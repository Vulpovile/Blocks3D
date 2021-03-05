#pragma once

#include <windows.h>
#define GetHoldKeyState(nVirtKey) (GetKeyState(nVirtKey)>>1)
#define GetKPBool(nVirtKey) (GetKeyState(nVirtKey) & 0x8000)
