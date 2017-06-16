/*Printer_payment, a simple printing paying management software base on
win32 API.
Copyright (C) 2017  Cheng Wei

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
