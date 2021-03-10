#include "game.h"
#include "gamewindow.h"
namespace wunise {

	Game::Game() noexcept : window(new GameWindow){}
	Game::~Game() = default;

	void Game::Initialize(){
		window->Initialize();
	}
	int Game::Run()
	{
		Initialize();

        return 0;
	}

}