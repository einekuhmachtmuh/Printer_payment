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