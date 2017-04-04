#pragma once
#include <stdlib.h>
#include <windows.h>

#ifdef UNICODE
#define MessageBoxQ  MessageBoxW
#else
#define MessageBoxQ  MessageBoxA
#endif

DWORD strlen(LPTSTR);

LPTSTR strcat(LPTSTR, LPTSTR);

LPTSTR int2LPTSTR_10(int);

void Error_Report(LPTSTR, LPTSTR);

