#pragma once
#ifndef __GAMEWINDOW_H__
#define __GAMEWINDOW_H__
#include <Windows.h>
#include <string>
namespace wunise {
	class GameWindow {
	public:
		GameWindow() noexcept;
		~GameWindow();
		
		GameWindow(GameWindow&&) noexcept;
		GameWindow& operator=(GameWindow&&) noexcept;

		GameWindow(const GameWindow&) = delete;
		GameWindow& operator=(const GameWindow&) = delete;

	private:
		HWND hwnd;
		std::wstring title;
		int width;
		int height;
	};
}
#endif // !__GAMEWINDOW_H__
