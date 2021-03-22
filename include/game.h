#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <string>
#include "gamepad.h"
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
		void CreateFactory();
		void CreateDevice();
		void CreateCommandQueue();
		void CreateSwapChain(HWND hwnd);
		
		//window message
		std::wstring Title;
		int Width;
		int Height;
		bool Isfullscreen;
		//render message
		Microsoft::WRL::ComPtr<ID3D12Device8> m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
		Microsoft::WRL::ComPtr<IDXGIFactory7> m_dxgiFactory;
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;
		//
		GamePad Gamepad;

		
	};
}
#endif // !__GAME_H__
