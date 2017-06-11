#include "Error_Report.h"


DWORD strlen(LPTSTR s) {
	DWORD count = 0;
	while (*(s + count)) {
		count++;
	}
	return count;
}

LPTSTR strcpy(LPTSTR source) {

	LPTSTR ret = (LPTSTR)malloc(sizeof(TCHAR) * strlen(source) + 1);
		for (;*source;source++, ret++) {
			*ret = *source;
		}
		*ret = 0;
		return ret;
}

LPTSTR strcat(LPTSTR _str1, LPTSTR str2) {
	LPTSTR str1 = _str1;
	LPTSTR ret = (LPTSTR)malloc(sizeof(TCHAR)*(strlen(str1) + strlen(str2) + 1));
	LPTSTR needle = ret;
	for (;*str1;str1++, needle++) {
		*needle = *str1;
	}

	for (;*str2;str2++, needle++) {
		*needle = *str2;
	}
	*needle = 0;
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

wchar_t * cstr2wstr(const char* cstr, UINT CodePage) {
	int wsize = MultiByteToWideChar(CodePage, 0, cstr, -1, NULL, 0);
	wchar_t* ret = new wchar_t[wsize + 1];
	MultiByteToWideChar(CodePage, 0, cstr, -1, ret, wsize);
	return ret;
}

char* wstr2cstr(LPTSTR wstr, UINT CodePage) {
	int Size = WideCharToMultiByte(CodePage, 0, wstr, -1, NULL, 0, NULL, false);
	//使用剛剛求出的size建立字串
	char* ret = new char[Size + 1];
	//將寬字元字串寫入字串
	WideCharToMultiByte(CodePage, 0, wstr, -1, ret, Size, NULL, false);

	return ret;
}