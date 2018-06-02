#pragma once

#include <windows.h>
#define GetHoldKeyState(nVirtKey) (GetKeyState(nVirtKey)>>1)
