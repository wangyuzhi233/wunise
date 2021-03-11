#include "gamewindow.h"
#include <Windows.h>

namespace wunise {
	LRESULT CALLBACK _windowProc(HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam) {
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
	void _RegisterWindowClassWin32() {
		WNDCLASSEXW wc = {};
		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = _windowProc;
		wc.hInstance = GetModuleHandleW(NULL);
		wc.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(32512));
		wc.lpszClassName = L"wuniseCLASS";
		wc.hIcon = (HICON)LoadImageW(NULL,
			MAKEINTRESOURCEW(32512), IMAGE_ICON,
			0, 0, LR_DEFAULTSIZE | LR_SHARED);
		RegisterClassExW(&wc);
	}
	
	void _UnregisterWindowClassWin32()
	{
		UnregisterClassW(L"wuniseCLASS", GetModuleHandleW(NULL));
	}

	void _CreateWindow(int w, int h, const std::wstring& title) {
		RECT rc = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		HWND hwnd = CreateWindowExW(
			0, 
			L"wuniseCLASS", 
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			rc.right - rc.left,
			rc.bottom - rc.top, 
			nullptr, 
			nullptr, 
			GetModuleHandleW(NULL),
			nullptr);

		ShowWindow(hwnd, SW_SHOWDEFAULT);
	}

	void _DestroyWindow(const std::wstring &title) {
		HWND hwnd = FindWindowW(L"wuniseCLASS", title.c_str());
		DestroyWindow(hwnd);
	}




	void GameWindow::CreateGameWindow() {
		_RegisterWindowClassWin32();
		_CreateWindow(width, height, title);
	}

	void GameWindow::DestroyGameWindow() {
		_DestroyWindow(title);
		_UnregisterWindowClassWin32();
	}
	bool GameWindow::GameLoop() {
		MSG msg = {};
		while (WM_QUIT != msg.message)
		{
			if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			else
			{
				return true;
			}
		}
		return false;
	}
}