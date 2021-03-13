#include "gamewindow.h"
#include <utility>
#include <memory>
namespace wunise {
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		static bool s_in_sizemove = false;
		static bool s_in_suspend = false;
		static bool s_minimized = false;
		static bool s_fullscreen = false;
		switch (message) {

		//ÍË³öÓÎÏ·
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	GameWindow::GameWindow() noexcept
	{
		hwnd = NULL;
		title = L"wunise";
		width = 800;
		height = 600;
	}
	GameWindow::~GameWindow() {}
	GameWindow::GameWindow(GameWindow&& r) noexcept {
		hwnd = r.hwnd;
		r.hwnd = NULL;
		title = std::move(r.title);
		width = r.width;
		height = r.height;
	}
	GameWindow& GameWindow::operator=(GameWindow&& r) noexcept {
		if (this != std::addressof(r)) {
			hwnd = r.hwnd;
			r.hwnd = NULL;
			title = std::move(r.title);
			width = r.width;
			height = r.height;
		}
		return *this;
	}


}