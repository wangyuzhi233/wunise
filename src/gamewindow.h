#pragma once
#ifndef __GAMEWINDOW_H__
#define __GAMEWINDOW_H__
#include <string>
namespace wunise {
	class GameWindow {
	public:
		GameWindow();
		~GameWindow() = default;
		
		GameWindow(GameWindow&&) noexcept = default;
		GameWindow& operator=(GameWindow&&) noexcept = default;

		GameWindow(const GameWindow&) = delete;
		GameWindow& operator=(const GameWindow&) = delete;

		void SetWidth(int width) {
			this->width = width;
		}
		void SetHeight(int height) {
			this->height = height;
		}

		int GetWidth() const {
			return width;
		}
		int GetHeight() const {
			return height;
		}
	private:
		std::wstring title;
		int width;
		int height;
	};
}
#endif // !__GAMEWINDOW_H__