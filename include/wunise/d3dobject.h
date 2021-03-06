#pragma once
#ifndef __D3D_OBJECT_H__
#define __D3D_OBJECT_H__
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace wunise {
    class D3DObject {
    public:
        D3DObject(HWND hwnd,UINT width, UINT height);

        void OnInit();
        void OnUpdate();
        void OnRender();
        void OnDestroy();

    private:
        void LoadPipeline();
        void LoadAssets();
        void PopulateCommandList();
        void WaitForPreviousFrame();

        // Pipeline objects.
        Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapChain;
        Microsoft::WRL::ComPtr<ID3D12Device8> m_device;
        Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[2];
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
        Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
        UINT m_rtvDescriptorSize;
        UINT m_width;
        UINT m_height;
        HWND m_hwnd;
        // Synchronization objects.
        UINT m_frameIndex;
        HANDLE m_fenceEvent;
        Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
        UINT64 m_fenceValue;

    };
}
#endif // !__D3D_OBJECT_H__


