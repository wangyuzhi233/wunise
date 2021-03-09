#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <Windows.h>
#include "window.h"
#include "graphics.h"
namespace wunise {
	class Game {
	public:
		Game();
		~Game();
		Game(const Game&);
		Game(Game&&) noexcept;
		Game& operator=(const Game&);
		Game& operator=(Game&&) noexcept;

		void Run();
		void Exit();
	protected:
		Window window;
		GraphicsDevice device;
	};
}
#endif // !__GAME_H__
