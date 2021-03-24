#pragma once
#ifndef __WUNISE_H__
#define __WUNISE_H__
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <dxgi1_6.h>
namespace wunise {

	class RenderSystem {
	public:
		RenderSystem();
		~RenderSystem();
		RenderSystem(RenderSystem&& r) noexcept;
		RenderSystem& operator=(RenderSystem&& r) noexcept;
		RenderSystem(const RenderSystem& r) = delete;
		RenderSystem& operator=(const RenderSystem& r) = delete;

		void CreateFactory();
		void CreateDevice();
		void CreateGraphicsCommandQueue();
		void CreateCopyCommandQueue();
		void CreateComputeCommandQueue();
		void CreateFence();
		void CreateSwapChain(HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc);
	private:
		class _rendersystem* _rs;
	};
}


#endif // !__WUNISE_H__

