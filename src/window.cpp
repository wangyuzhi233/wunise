#include "window.h"

namespace wunise {
	namespace _internal {
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

			switch (message)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	Window::Window()
	{
		title = L"wunise";
		width = 800;
		height = 600;
		window_hwnd = NULL;
	}
	Window::~Window()
	{
	}
	Window::Window(const Window& r)
	{
		title = r.title;
		width = r.width;
		height = r.height;
		window_hwnd = r.window_hwnd;
	}
	Window::Window(Window&& r) noexcept
	{
		title = r.title; 
		r.title.clear();
		width = r.width;
		height = r.height;
		window_hwnd = r.window_hwnd;
	}
	Window& Window::operator=(const Window& r)
	{
		title = r.title;
		width = r.width;
		height = r.height;
		window_hwnd = r.window_hwnd;
		return *this;
	}

	Window& Window::operator=(Window&& r) noexcept
	{
		title = r.title; 
		r.title.clear();
		width = r.width;
		height = r.height;
		window_hwnd = r.window_hwnd;
		return *this;
	}
	void Window::CreateGameWindow() {
		// Initialize the window class.
		WNDCLASSEX windowClass = { 0 };
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = _internal::WndProc;
		windowClass.hInstance = GetModuleHandle(0);
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.lpszClassName = L"wunise";
		RegisterClassEx(&windowClass);

		RECT windowRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		window_hwnd = CreateWindow(
			windowClass.lpszClassName,
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			nullptr,
			nullptr,
			windowClass.hInstance,
			nullptr);
		ShowWindow(window_hwnd, SW_SHOWDEFAULT);
	}

	HWND Window::getHWND() const
	{
		return window_hwnd;
	}
	int Window::getWidth() const
	{
		return width;
	}

	int Window::getHeight() const
	{
		return height;
	}

}