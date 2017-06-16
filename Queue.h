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
#include <windows.h>
#include <stdlib.h>

#define JOB_UNDEF 0
#define JOB_UNEXDEL 1
#define JOB_SPOOLING 2
#define JOB_PAYING 3
#define JOB_PRINTING 4

typedef struct _myJob {
	DWORD _JobId;
	HANDLE _hThread;
	DWORD _ThreadId;
	DWORD _signal;
	_myJob() {
		this->_JobId = 0;
		_ThreadId = 0;
		this->_hThread = 0;
		this->_signal = JOB_UNDEF;
	}
}myJob;


myJob* Jsearch(DWORD, myJob*[10]);


myJob* Jinsert(DWORD, myJob*[10]);

void Jfree(myJob*);