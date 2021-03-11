#include "wunise.h"
namespace wunise {
	void ExitGame(int code) {
		ExitProcess(static_cast<UINT>(code));
	}
	HWND GetHWND() {
		return FindWindowW(L"wuniseCLASS", NULL);
	}
}


