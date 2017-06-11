#pragma once
#include <stdlib.h> //malloc()
#include <windows.h>// it includes Winuser.h for MessageBox.

//Avoid collision beteen class MessageBox and int Messageox(the function we want!)
#ifdef UNICODE
#define MessageBoxQ  MessageBoxW
#else
#define MessageBoxQ  MessageBoxA
#endif

DWORD strlen(LPTSTR); // LPTSTR string length counting

LPTSTR strcat(LPTSTR, LPTSTR);//more "safty" LPTSTR string concatenation(by malloc)

LPTSTR strcpy(LPTSTR);

LPTSTR int2LPTSTR_10(int);//convert int digit to decimal LPTSTR string

void Error_Report(LPTSTR, LPTSTR);//Report error, including specific title, message and error code from GetLastError()

wchar_t * cstr2wstr(const char*, UINT);

char* wstr2cstr(LPTSTR, UINT);

