#pragma once
#ifndef __WEXCEPTION_H__
#define __WEXCEPTION_H__
#include <Windows.h>
namespace wunise {
	void ThrowIfFailed(HRESULT hr);
}
#endif // !__WEXCEPTION_H__
