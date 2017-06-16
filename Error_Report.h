/*Printer_payment, a simple printing paying management software base on
win32 API.
Copyright (C) 2017  Wei Cheng, 	Zhi Hao Shih, Chang Fu Wang

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
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

