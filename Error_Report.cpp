#include "Error_Report.h"


DWORD strlen(LPTSTR s) {
	DWORD count = 0;
	while (*(s + count)) {
		count++;
	}
	return count;
}

LPTSTR strcat(LPTSTR _dest, LPTSTR src) {
	LPTSTR dest = _dest;
	LPTSTR ret = (LPTSTR)malloc(sizeof(TCHAR)*(strlen(dest) + strlen(src) + 1));
	LPTSTR needle = ret;
	for (;*dest;dest++, needle++) {
		*needle = *dest;
	}

	for (;*src;src++, needle++) {
		*needle = *src;
	}
	*needle = '\0';
	return ret;

}

LPTSTR int2LPTSTR_10(int number) {
	int top_number = 0;
	LPTSTR r_str;
	if (number == 0) {
		r_str = L"0";
	}
	else {
		int j = number;
		do {
			top_number++;
			j /= 10;
		} while (j);
		r_str = (LPTSTR)malloc(sizeof(TCHAR)*(top_number + 1));
		j = number;
		for (int k = 1; k <= top_number; k++) {
			r_str[top_number - k] = (j % 10) + 48;
			j /= 10;
		}
		r_str[top_number] = '\0';
	}
	return r_str;
}

void Error_Report(LPTSTR title, LPTSTR msg) {
	MessageBoxQ(NULL, strcat(strcat(msg, L"\nError code "), int2LPTSTR_10(GetLastError())), title, MB_OK | MB_ICONHAND | MB_DEFBUTTON1 | MB_APPLMODAL);
}