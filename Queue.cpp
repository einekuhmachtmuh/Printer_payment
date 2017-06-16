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