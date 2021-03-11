#pragma once
#ifndef __D11RENDERSYSTEM_H__
#define __D11RENDERSYSTEM_H__
#include "rendersystem.h"
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
namespace wunise {
	class D11RenderSystem:public RenderSystem {
	public:
		D11RenderSystem() noexcept;
		virtual ~D11RenderSystem() = default;

		D11RenderSystem(D11RenderSystem&&) noexcept = default;
		D11RenderSystem& operator=(D11RenderSystem&&) noexcept = default;

		D11RenderSystem(const D11RenderSystem&) = delete;
		D11RenderSystem& operator=(const D11RenderSystem&) = delete;
		
		virtual void Initialize(HWND hwnd, int w, int h);
	private:

		void CreateResources();
		// Device resources.
		HWND                                            m_window;
		int                                             m_outputWidth;
		int                                             m_outputHeight;

		Microsoft::WRL::ComPtr<ID3D11Device5>           m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext4>    m_d3dContext;

		Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

	};
}
#endif // !__D11RENDERSYSTEM_H__
