#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <string>
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
namespace wunise {
	class Game {
	public:
		Game();
		~Game() {}

		Game(Game&& r) noexcept = default;
		Game& operator=(Game&& r) noexcept = default;

		Game(const Game& r) = delete;
		Game& operator=(const Game& r) = delete;

		int Run();
	private:
		void CreateDevice();

		std::wstring Title;
		int Width;
		int Height;
		//bool IsFullScreen;
	};
}
#endif // !__GAME_H__
