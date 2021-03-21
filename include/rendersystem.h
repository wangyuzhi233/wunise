#pragma once
#ifndef __RENDERSYSTEM_H__
#define __RENDERSYSTEM_H__
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <wrl/wrappers/corewrappers.h>
namespace wunise {
	class RenderSystem {
	public:
		RenderSystem() :
			m_window(nullptr),
			m_outputWidth(800),
			m_outputHeight(600),
			m_backBufferIndex(0),
			m_rtvDescriptorSize(0),
			m_fenceValues{}
		{
		}
		~RenderSystem() {}

		RenderSystem(RenderSystem&& r) noexcept = default;
		RenderSystem& operator=(RenderSystem&& r) noexcept = default;

		RenderSystem(const RenderSystem& r) = delete;
		RenderSystem& operator=(const RenderSystem& r) = delete;
	private:

		void CreateDevice();
		void GetAdapter(IDXGIAdapter1** ppAdapter);
		// Application state
		HWND                                                m_window;
		int                                                 m_outputWidth;
		int                                                 m_outputHeight;

		UINT                                                m_backBufferIndex;
		UINT                                                m_rtvDescriptorSize;
		Microsoft::WRL::ComPtr<ID3D12Device>                m_d3dDevice;
		Microsoft::WRL::ComPtr<IDXGIFactory4>               m_dxgiFactory;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>          m_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        m_rtvDescriptorHeap;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        m_dsvDescriptorHeap;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>      m_commandAllocators[2];
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>   m_commandList;
		Microsoft::WRL::ComPtr<ID3D12Fence>                 m_fence;
		UINT64                                              m_fenceValues[2];
		Microsoft::WRL::Wrappers::Event                     m_fenceEvent;

		// Rendering resources
		Microsoft::WRL::ComPtr<IDXGISwapChain3>             m_swapChain;
		Microsoft::WRL::ComPtr<ID3D12Resource>              m_renderTargets[2];
		Microsoft::WRL::ComPtr<ID3D12Resource>              m_depthStencil;
	};
}
#endif // !__RENDERSYSTEM_H__
