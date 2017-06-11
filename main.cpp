#pragma once
#include "main.h"
#include "Queue.h"
#include "Error_Report.h"
#include "PayForm.h"

using namespace 印表機付費管理;

//*****************************************//Allowed Change Notification Type//*****************************************

WORD pnf[9] = {
	PRINTER_NOTIFY_FIELD_DEVMODE,
	PRINTER_NOTIFY_FIELD_PRINTER_NAME,
	PRINTER_NOTIFY_FIELD_COMMENT,
	PRINTER_NOTIFY_FIELD_LOCATION,
	PRINTER_NOTIFY_FIELD_SEPFILE,
	PRINTER_NOTIFY_FIELD_STATUS,
	PRINTER_NOTIFY_FIELD_PRINT_PROCESSOR,
	PRINTER_NOTIFY_FIELD_PARAMETERS,
	PRINTER_NOTIFY_FIELD_CJOBS };

WORD jnf[8] = {
	JOB_NOTIFY_FIELD_PRINTER_NAME,
	JOB_NOTIFY_FIELD_PARAMETERS,
	JOB_NOTIFY_FIELD_STATUS,
	JOB_NOTIFY_FIELD_DOCUMENT,
	JOB_NOTIFY_FIELD_PRIORITY,
	JOB_NOTIFY_FIELD_POSITION,
	JOB_NOTIFY_FIELD_TOTAL_PAGES,
	JOB_NOTIFY_FIELD_SUBMITTED };

//*****************************************//Paying Thread Function//*****************************************

DWORD WINAPI Pay_start(PVOID _p) {
	PayForm^ p = gcnew PayForm((payarg*)_p);
	Application::Run(p);
	ExitThread(0);
}

//*****************************************//Printer_Screener Thread Function//*****************************************

DWORD WINAPI Printer_Screener(PVOID _PrinterName) {
	LPTSTR PrinterName = (LPTSTR)_PrinterName;
	HANDLE hPrinter = INVALID_HANDLE_VALUE;
	HANDLE hNotify;
	PRINTER_NOTIFY_INFO* pPNI;

	//*****************************************//Initialization of PNO//*****************************************
	PRINTER_NOTIFY_OPTIONS PNO;
	PRINTER_NOTIFY_OPTIONS_TYPE PNOT[2];
	PNO.Version = 2;
	PNO.Count = 2;
	PNO.pTypes = PNOT;

	PNOT[0].Type = PRINTER_NOTIFY_TYPE;
	PNOT[0].Count = 9;
	PNOT[0].pFields = pnf;

	PNOT[1].Type = JOB_NOTIFY_TYPE;
	PNOT[1].Count = 8;
	PNOT[1].pFields = jnf;


	//*****************************************//Initialization of change signal//*****************************************

	if (!OpenPrinter(
		(LPTSTR)PrinterName,//LPTSTR
		&hPrinter,			//HANDLE
		NULL)				//LPPRINTER_DEFAULTS
		) {
		Error_Report((LPTSTR)PrinterName, L"Can't open Printer");
		ExitThread(0);
	}

	hNotify = FindFirstPrinterChangeNotification(
		hPrinter,
		PRINTER_CHANGE_JOB,
		0,
		&PNO);

	if (hNotify == INVALID_HANDLE_VALUE) {
		Error_Report(L"Error", L"Can't find first ptinter job change");
		ClosePrinter(hPrinter);
		ExitThread(0);
	}

	//*****************************************//Screener loop//*****************************************

	DWORD JobId = 0;
	DWORD JobStat = 0;
	DWORD ChangeReason;

	myJob* queue[10];
	for (int i = 0; i < 10; i++) {
		queue[i] = new myJob();
	}

	for (;;)
	{
		WaitForSingleObject(hNotify, INFINITE);
		PNO.Flags = 0;//PRINTER_NOTIFY_OPTIONS_REFRESH

		LPVOID p = nullptr;
		if (!FindNextPrinterChangeNotification(
			hNotify,
			&ChangeReason,
			&PNO,
			&p))
		{
			Error_Report(L"Error", L"Can't find next ptinter job change");
			ClosePrinter(hPrinter);
			ExitThread(0);
		}
		else {
			pPNI = (PRINTER_NOTIFY_INFO*)p;
		}

		//Collect info from Notification
		if (p != nullptr) {
			for (int i = 0; i < pPNI->Count; i++) {
				if (pPNI->aData[i].Type == JOB_NOTIFY_TYPE) {
					JobId = pPNI->aData[i].Id;
					if (pPNI->aData[i].Field == JOB_NOTIFY_FIELD_STATUS) {
						JobStat = pPNI->aData[i].NotifyData.adwData[0];
					}
				}
			}
		}

		//Degbug:whether JobId is set. 
		//if (JobId == 0 || (ChangeReason & PRINTER_CHANGE_ADD_JOB)||(ChangeReason & PRINTER_CHANGE_SET_JOB)||(ChangeReason & PRINTER_CHANGE_DELETE_JOB)) {
			//Error_Report(L"Warning", L"Change Notification wuthout JobId!");
		//}
		//Change Handling
		
		if (ChangeReason & PRINTER_CHANGE_ADD_JOB) {
			if (JobId != 0) {
				Jinsert(JobId, queue)->_signal = JOB_SPOOLING;
				if (!SetJob(
					hPrinter,
					JobId,
					0,
					NULL,//iflevel = 0, pJob should be NULL
					JOB_CONTROL_PAUSE
				)) {
					Error_Report(L"Error", L"Fail to pause last added job!");
					ClosePrinter(hPrinter);
					ExitThread(0);
				}
			}
			else {
				Error_Report(L"Error", L"Last Added job without ID!");
				ClosePrinter(hPrinter);
				ExitThread(0);
			}		
		}

		if (ChangeReason & PRINTER_CHANGE_SET_JOB) {
			myJob* temp = Jsearch(JobId, queue);
			if (temp) 
			{
				if (JobStat == JOB_STATUS_PAUSED) {
					if (temp->_signal == JOB_SPOOLING) { //避免重新啟動工作導致重複的paying thread
						temp->_signal = JOB_PAYING;
						LPVOID arg = new payarg(hPrinter, temp);
						temp->_hThread = CreateThread(
							NULL,//LPSECURITY_ATTRIBUTES, handle can't be inherited by child processes if NULL!
							0,  //SIZE_T, The initial size of the stack, in bytes.(0 = default size for the executable)
							Pay_start, // LPTHREAD_START_ROUTINE, pointer to thread funtion
							arg, // LPVOID, poniter of Parameter
							0, //DWORD,flags that control the creation of the thread.(0, immedinately runs thread after creation)
							&temp->_ThreadId //LPDWORD, pointer to thread ID
						);
					}
				}
				if (JobStat & JOB_STATUS_PRINTING) {
					if (temp->_signal == JOB_PAYING) {
						if (!SetJob(
							hPrinter,
							JobId,
							0,
							NULL,//iflevel = 0, pJob should be NULL
							JOB_CONTROL_PAUSE
						)) {
							Error_Report(L"Error", L"Fail to paused paying job!");
							ClosePrinter(hPrinter);
							ExitThread(0);
						}
					}
				}
			}
			else if(JobId)
			{
				Error_Report(L"Error", L"There's job not in queue!");
				if (!SetJob(
					hPrinter,
					JobId,
					0,
					NULL,//iflevel = 0, pJob should be NULL
					JOB_CONTROL_DELETE
				)) {
					Error_Report(L"Error", L"Fail to delete uncontol job!");
					ClosePrinter(hPrinter);
					ExitThread(0);
				}
			}
		}

		if (ChangeReason & PRINTER_CHANGE_DELETE_JOB) {
			myJob* temp = Jsearch(JobId, queue);
			if (temp) {
				if (temp->_signal == JOB_PAYING) {
					temp->_signal = JOB_UNEXDEL;
				}
				else {
					Jfree(temp);
				}
			}
		}

		//Free pPNI
		JobId = 0;
	}
	return 0;
}

//*****************************************//entry point//*****************************************

int main()
{
	FreeConsole();//主控台隱藏
	HANDLE hScreener[2];
	LPDWORD Screener_ID[2];
	hScreener[0] = CreateThread(
		NULL,//LPSECURITY_ATTRIBUTES, handle can't be inherited by child processes if NULL!
		0,  //SIZE_T, The initial size of the stack, in bytes.(0 = default size for the executable)
		Printer_Screener, // LPTHREAD_START_ROUTINE, pointer to thread funtion
		L"我是彩雷", // LPVOID, poniter of Parameter
		0, //DWORD,flags that control the creation of the thread.(0, immedinately runs thread after creation)
		Screener_ID[0] //LPDWORD, pointer to thread ID
	);
	hScreener[1] = CreateThread(
		NULL,//LPSECURITY_ATTRIBUTES, handle can't be inherited by child processes if NULL!
		0,  //SIZE_T, The initial size of the stack, in bytes.(0 = default size for the executable)
		Printer_Screener, // LPTHREAD_START_ROUTINE, pointer to thread funtion
		L"我是黑白", // LPVOID, poniter of Parameter
		0, //DWORD,flags that control the creation of the thread.(0, immedinately runs thread after creation)
		Screener_ID[1] //LPDWORD, pointer to thread ID
	);
	//WaitForSingleObject(hScreener[0], INFINITE);
	WaitForMultipleObjects(
		2,//number of objects
		hScreener,//Handle array of objects
		true, //Wait all or not
		INFINITE //wait time, in milliseconds
	);
	return 0;
}