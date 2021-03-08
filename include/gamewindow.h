#pragma once
#ifndef __GAMEWINDOW_H__
#define __GAMEWINDOW_H__
namespace wunise {
	class GameWindow {
	public:
		GameWindow() {}
		~GameWindow() {}
		GameWindow(const GameWindow&) {}
		GameWindow(GameWindow&&) noexcept {}
		GameWindow& operator=(const GameWindow&) { return *this; }
		GameWindow& operator=(GameWindow&&) noexcept { return *this; }
	private:
	};
}
#endif // !__GAMEWINDOW_H__
