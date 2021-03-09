#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <Windows.h>
#include <string>
namespace wunise {
	class Window {
	public:
		Window();
		~Window();
		Window(const Window&);
		Window(Window&&) noexcept;
		Window& operator=(const Window&);
		Window& operator=(Window&&) noexcept;

		void CreateGameWindow();
		HWND getHWND()const;
		int getWidth()const;
		int getHeight()const;
	private:
		std::wstring title;
		int width;
		int height;
		HWND window_hwnd;
	};
}
#endif // !__WINDOW_H__
