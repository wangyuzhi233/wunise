#include "wunise.h"
#include <wrl\client.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <memory>
namespace wunise {
	class _rendersystem {
	public:
		_rendersystem() {}
		~_rendersystem() {}
		_rendersystem(_rendersystem&& r) noexcept = default;
		_rendersystem& operator=(_rendersystem&& r) noexcept = default;
		_rendersystem(const _rendersystem& r) = delete;
		_rendersystem& operator=(const _rendersystem& r) = delete;
		Microsoft::WRL::ComPtr<ID3D12Device8> m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_GcommandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CopycommandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_ComputecommandQueue;
		Microsoft::WRL::ComPtr<IDXGIFactory7> m_dxgiFactory;
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D12Fence1> m_Fence;
	};

	RenderSystem::RenderSystem() {
		_rs = new _rendersystem;
	}

	RenderSystem::~RenderSystem() {
		if (_rs) {
			delete _rs;
			_rs = nullptr;
		}
	}

	RenderSystem::RenderSystem(RenderSystem&& r) noexcept {
		_rs = r._rs;
		r._rs = nullptr;
	}
	RenderSystem& RenderSystem::operator=(RenderSystem&& r) noexcept {
		if (this != std::addressof(r)) {
			if (_rs) {
				delete _rs;
			}
			_rs = r._rs;
			r._rs = nullptr;
		}
		return *this;
	}

	void RenderSystem::CreateFactory()
	{
		CreateDXGIFactory2(0, IID_PPV_ARGS(_rs->m_dxgiFactory.ReleaseAndGetAddressOf()));
	}
	void RenderSystem::CreateDevice()
	{
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(_rs->m_d3dDevice.ReleaseAndGetAddressOf()));
	}
	void RenderSystem::CreateGraphicsCommandQueue()
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		_rs->m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(_rs->m_GcommandQueue.ReleaseAndGetAddressOf()));
	}
	void RenderSystem::CreateCopyCommandQueue()
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		_rs->m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(_rs->m_CopycommandQueue.ReleaseAndGetAddressOf()));
	}

	void RenderSystem::CreateComputeCommandQueue() {
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		_rs->m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(_rs->m_ComputecommandQueue.ReleaseAndGetAddressOf()));
	}

	void RenderSystem::CreateFence()
	{
		_rs->m_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_rs->m_Fence));
	}
}