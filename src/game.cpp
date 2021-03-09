#include "game.h"
#include <utility>
namespace wunise {
	Game::Game()
	{
	}
	Game::~Game()
	{
	}
	Game::Game(const Game& r)
	{
		window = r.window;
		device = r.device;
	}
	Game::Game(Game&& r) noexcept
	{
		window = std::move(r.window);
		device = std::move(r.device);
	}
	Game& Game::operator=(const Game& r)
	{
		window = r.window;
		device = r.device;
		return *this;
	}
	Game& Game::operator=(Game&& r) noexcept
	{
		window = std::move(r.window);
		device = std::move(r.device);
		return *this;
	}

	void Game::Run()
	{
		window.CreateGameWindow();
		device.CreateDeivce();
;		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
			}
		}
	
	}
	void Game::Exit() {
		PostQuitMessage(0);
	}
}