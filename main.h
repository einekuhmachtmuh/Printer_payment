#pragma once
#include <windows.h>// Winuser.h for MessageBox, Winspool.h for spooler API
#include <Processthreadsapi.h> //Thread management API

#ifdef UNICODE
#define MessageBoxQ  MessageBoxW
#else
#define MessageBoxQ  MessageBoxA
#endif

//Avoid collision beteen class MessageBox and int Messageox(the function we want!)

struct payarg {
	DWORD JobId;
	HANDLE hPrinter;
	LPTSTR PrinterName;
	payarg(DWORD _JobId, HANDLE _hPrinter, LPTSTR _PrinterName) {
		this->JobId = _JobId;
		this->hPrinter = _hPrinter;
		this->PrinterName = _PrinterName;
	}
};