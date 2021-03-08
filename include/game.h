#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <Windows.h>
#include <string>
namespace wunise {
	class Game {
	public:
		Game();
		Game(const wchar_t* title, int width, int height);
		Game(const Game& r);
		Game(Game&&) noexcept;
		Game& operator=(const Game& r);
		Game& operator=(Game&& r) noexcept;
		~Game();

		int Run(HINSTANCE hInstance, int nCmdShow);
	public:
		std::wstring Title;
		int Width;
		int Height;
	};
}
#endif // !__GAME_H__
