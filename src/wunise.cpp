#include "wunise.h"
#include <Windows.h>
namespace wunise {
	void ExitGame(int code) {
		ExitProcess(static_cast<UINT>(code));
	}
}


