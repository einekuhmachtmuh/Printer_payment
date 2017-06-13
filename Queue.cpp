#pragma once
#include "Queue.h"

myJob* Jsearch(DWORD JobId, myJob* table[10]) {
	for (int i = 0; i < 10; i++) {
		if (table[i]->_JobId == JobId) {
			return table[i];
		}
	}
	return 0;
}

myJob* Jinsert(DWORD JobId, myJob* table[10]) {
	if (JobId) {
		myJob* null = Jsearch(0, table);
		if (null != 0) {
			null->_JobId = JobId;
		}
		return null;

	}
	else
	{
		return 0;
	}
}

void Jfree(myJob* Job) {
	Job->_hThread = 0;
	Job->_JobId = 0;
	Job->_signal = JOB_UNDEF;
	Job->_ThreadId = 0;
}