#include "gamewindow.h"
#include <utility>
#include <memory>
namespace wunise {

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		switch (message) {

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	void _RegisterClass() {}
	void _UnRegisterClass() {}

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

	void GameWindow::CreateGameWindow() {}

	void GameWindow::DestroyGameWindow() {}
	bool GameWindow::GameLoop() {
		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			// Process any messages in the queue.
			if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			else {
				return true;
			}
		}
		return false;
	}
}