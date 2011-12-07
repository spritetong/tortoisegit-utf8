#pragma once

// Change these values to use different versions
#define WINVER		0x0400
#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#include <Windows.h>
#include <tchar.h>
#include <oleauto.h>

#include <vector>
#include <map>
#include <string>

#include "../Utils/tgit_xutf8.h" /* For UTF-8. Added by Sprite Tong, 12/1/2011. */

using namespace std;

#define CRASHRPTAPI extern "C" __declspec(dllexport)
//////////////////////////////////////////////////////////////////////
// how shall addresses be formatted?
//////////////////////////////////////////////////////////////////////

extern const LPCTSTR addressFormat;
extern const LPCTSTR offsetFormat;
extern const LPCTSTR sizeFormat;
