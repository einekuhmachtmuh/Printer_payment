#include "main.h"
#include "Error_Report.h"
#include "PayForm.h"

using namespace 印表機付費管理;

//*****************************************//Allowed Notification Type//*****************************************

WORD pnf[100] = {
	PRINTER_NOTIFY_FIELD_SERVER_NAME,
	PRINTER_NOTIFY_FIELD_PRINTER_NAME,
	PRINTER_NOTIFY_FIELD_SHARE_NAME,
	PRINTER_NOTIFY_FIELD_PORT_NAME,
	PRINTER_NOTIFY_FIELD_DRIVER_NAME,
	PRINTER_NOTIFY_FIELD_COMMENT,
	PRINTER_NOTIFY_FIELD_LOCATION,
	PRINTER_NOTIFY_FIELD_SEPFILE,
	PRINTER_NOTIFY_FIELD_PRINT_PROCESSOR,
	PRINTER_NOTIFY_FIELD_PARAMETERS,
	PRINTER_NOTIFY_FIELD_DATATYPE,
	PRINTER_NOTIFY_FIELD_ATTRIBUTES,
	PRINTER_NOTIFY_FIELD_PRIORITY,
	PRINTER_NOTIFY_FIELD_DEFAULT_PRIORITY,
	PRINTER_NOTIFY_FIELD_START_TIME,
	PRINTER_NOTIFY_FIELD_UNTIL_TIME,
	PRINTER_NOTIFY_FIELD_STATUS_STRING,
	PRINTER_NOTIFY_FIELD_CJOBS,
	PRINTER_NOTIFY_FIELD_AVERAGE_PPM,
	PRINTER_NOTIFY_FIELD_TOTAL_PAGES,
	PRINTER_NOTIFY_FIELD_PAGES_PRINTED,
	PRINTER_NOTIFY_FIELD_TOTAL_BYTES,
	PRINTER_NOTIFY_FIELD_BYTES_PRINTED };

WORD jnf[100] = {
	JOB_NOTIFY_FIELD_PRINTER_NAME,
	JOB_NOTIFY_FIELD_MACHINE_NAME,
	JOB_NOTIFY_FIELD_PORT_NAME,
	JOB_NOTIFY_FIELD_USER_NAME,
	JOB_NOTIFY_FIELD_NOTIFY_NAME,
	JOB_NOTIFY_FIELD_DATATYPE,
	JOB_NOTIFY_FIELD_PRINT_PROCESSOR,
	JOB_NOTIFY_FIELD_PARAMETERS,
	JOB_NOTIFY_FIELD_DRIVER_NAME,
	JOB_NOTIFY_FIELD_STATUS_STRING,
	JOB_NOTIFY_FIELD_DOCUMENT,
	JOB_NOTIFY_FIELD_PRIORITY,
	JOB_NOTIFY_FIELD_POSITION,
	JOB_NOTIFY_FIELD_START_TIME,
	JOB_NOTIFY_FIELD_UNTIL_TIME,
	JOB_NOTIFY_FIELD_TIME,
	JOB_NOTIFY_FIELD_TOTAL_PAGES,
	JOB_NOTIFY_FIELD_PAGES_PRINTED,
	JOB_NOTIFY_FIELD_TOTAL_BYTES,
	JOB_NOTIFY_FIELD_BYTES_PRINTED };

//*****************************************//Prequeries for PayForm//*****************************************

DWORD WINAPI Pay_start(PVOID _p) {
		ExitThread(0);
}

//*****************************************//Printer_Screener//*****************************************

DWORD WINAPI Printer_Screener(PVOID _PrinterName) {
	LPTSTR PrinterName = (LPTSTR)_PrinterName;
	HANDLE hPrinter = INVALID_HANDLE_VALUE;
	HANDLE hNotify;
	PRINTER_NOTIFY_INFO* pPNI;
	PRINTER_NOTIFY_OPTIONS PNO;
	PRINTER_NOTIFY_OPTIONS_TYPE PNOT[2];
	PNO.Version = 2;
	PNO.Count = 2;
	PNO.pTypes = PNOT;

	PNOT[0].Type = PRINTER_NOTIFY_TYPE;
	PNOT[0].Count = 23;
	PNOT[0].pFields = pnf;

	PNOT[1].Type = JOB_NOTIFY_TYPE;
	PNOT[1].Count = 20;
	PNOT[1].pFields = jnf;

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
	DWORD JobId;
	JOB_INFO_2* pJob;
	DWORD ChangeReason;
	HANDLE hpayform;
	LPDWORD ppayID;
	HANDLE PayThread[2];
	for (;;)
	{
		WaitForSingleObject(hNotify, INFINITE);
		PNO.Flags = PRINTER_NOTIFY_OPTIONS_REFRESH;

		LPVOID p;
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

		if (ChangeReason & PRINTER_CHANGE_ADD_JOB) {
			DWORD l_JobId;
			for (int j;j < pPNI->Count;j++) {
				if (pPNI->aData[j].Type == JOB_NOTIFY_TYPE) {
					l_JobId = pPNI->aData[j].Id;
					break;
				}
			}
			DWORD Command = (JobId == NULL) ? (JOB_CONTROL_PAUSE) : (JOB_CONTROL_DELETE);
			if (!SetJob(
				hPrinter,
				l_JobId,
				0,
				NULL,//iflevel = 0, pJob should be NULL
				Command
			)) {
				Error_Report(L"Error", L"Can't set last added job");
				ClosePrinter(hPrinter);
				ExitThread(0);
			}
			if (JobId == NULL) {
				JobId = l_JobId;
			}
		}
		if (ChangeReason & PRINTER_CHANGE_SET_JOB) {
			if (pJob != nullptr) {
				if (pJob->Status & JOB_STATUS_PAUSED && !(pJob->Status &  JOB_STATUS_DELETING) && !(pJob->Status & JOB_STATUS_DELETED)) {
					if (!(pJob->Status & JOB_STATUS_SPOOLING)) {
						payarg *p = new payarg(JobId, hPrinter, (LPTSTR)PrinterName);
						hpayform = CreateThread(
							NULL,
							0,
							Pay_start, // LPTHREAD_START_ROUTINE, pointer to thread funtion
							p, // LPVOID, poniter of Parameter
							0, //DWORD,flags that control the creation of the thread.(0, immedinately runs thread after creation)
							ppayID //LPDWORD, pointer to thread ID
						);
						if (hpayform != nullptr) {
							JobId = NULL;
							free(pJob);
						}
					}
				}
			}
		}
		if (!FreePrinterNotifyInfo(pPNI) && GetLastError() != ERROR_INVALID_PARAMETER && GetLastError() != 0) {
			Error_Report(L"Error", L"Can't free job notification INFO!");
			ExitThread(0);
		}
	}

	return 0;
}

//*****************************************//emtry poin//*****************************************

int main()
{
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
	WaitForSingleObject(hScreener[0], INFINITE);
	//WaitForMultipleObjects(
	//	2,//number of objects
	//	hScreener,//Handle array of objects
	//	true, //Wait all or not
	//	INFINITE //wait time, in milliseconds
	//);
	return 0;
}