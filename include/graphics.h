#pragma once
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
#include <Windows.h>
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
namespace wunise {
	class GraphicsDevice {
	public:
		GraphicsDevice();
		~GraphicsDevice();
		GraphicsDevice(const GraphicsDevice&);
		GraphicsDevice(GraphicsDevice&&) noexcept;
		GraphicsDevice& operator=(const GraphicsDevice&);
		GraphicsDevice& operator=(GraphicsDevice&&) noexcept;

		void CreateDeivce();
		void CreateSwapChain(HWND hwnd,int width,int height);
		void Present();
	private:
		Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;
	};
}
#endif // !__GRAPHICS_H__
