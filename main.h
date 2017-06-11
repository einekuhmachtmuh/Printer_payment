#pragma once
#include <windows.h>// it includes many headers, Winuser.h for MessageBox, Winspool.h for spooler API
#include <Processthreadsapi.h> //Thread management API

#include "Queue.h"

//argument for Paying Thread
typedef struct _payarg {
	HANDLE hPrinter;
	myJob* Jstat;
	_payarg(HANDLE _hPrinter,myJob* _Jstat) {
		this->hPrinter = _hPrinter;
		this->Jstat = _Jstat;
	}
}payarg;
