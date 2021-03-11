#pragma once
#ifndef __GAMEWINDOW_H__
#define __GAMEWINDOW_H__
#include <string>
namespace wunise {
	class GameWindow {
	public:
		GameWindow() noexcept {
			title = L"wunise";
			width = 800;
			height = 600;
		}
		~GameWindow() = default;
		
		GameWindow(GameWindow&&) noexcept = default;
		GameWindow& operator=(GameWindow&&) noexcept = default;

		GameWindow(const GameWindow&) = delete;
		GameWindow& operator=(const GameWindow&) = delete;

		void CreateGameWindow();
		void DestroyGameWindow();
		bool GameLoop();

	private:
		std::wstring title;
		int width;
		int height;
	};
}
#endif // !__GAMEWINDOW_H__
