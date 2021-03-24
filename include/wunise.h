#pragma once
#ifndef __WUNISE_H__
#define __WUNISE_H__
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

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
	private:
		class _rendersystem* _rs;
	};
}


#endif // !__WUNISE_H__

