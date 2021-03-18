#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <memory>
namespace wunise {
	class Game {
	public:
		Game();
		virtual ~Game();

		Game(Game&& r) noexcept;
		Game& operator=(Game&& r) noexcept;

		Game(const Game& r) = delete;
		Game& operator=(const Game& r) = delete;

		int Run();
	protected:
		std::unique_ptr<class GameWindow> window;
		std::unique_ptr<class RenderSystem> rendersystem;
		std::unique_ptr<class _game_proc_context> _proc;
	};
}
#endif // !__GAME_H__
