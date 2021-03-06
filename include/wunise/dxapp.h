#pragma once
#ifndef __DXAPP_H__
#define __DXAPP_H__
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <vector>
namespace wunise {
    class DXAPP {
    public:
        DXAPP() {}
        ~DXAPP() {}
        DXAPP(const DXAPP& r) {
            m_SwapChain = r.m_SwapChain;
            m_Device = r.m_Device;
            m_DeviceContext = r.m_DeviceContext;
            m_RenderTargetView = r.m_RenderTargetView;
        }
        DXAPP(DXAPP&& r) noexcept;
        DXAPP& operator=(const DXAPP& r) {
            m_SwapChain = r.m_SwapChain;
            m_Device = r.m_Device;
            m_DeviceContext = r.m_DeviceContext;
            m_RenderTargetView = r.m_RenderTargetView;
            return *this;
        }
        DXAPP& operator=(DXAPP&& r) noexcept;

        void CreateDeviceAndSwapChain(HWND hwnd, UINT w, UINT h);
        void CreateRenderTargetView();
        void SetRenderTargets();
        void SetViewports(float w, float h);
        void ClearRenderTargetView(float r, float g, float b, float a);
        void Present();
        void CompileVertexShader(const wchar_t*path,const char * entrypoint);
    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain4> m_SwapChain;
        Microsoft::WRL::ComPtr<ID3D11Device5> m_Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext4> m_DeviceContext;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
        Microsoft::WRL::ComPtr<ID3DBlob> vertexShader;
        Microsoft::WRL::ComPtr<ID3DBlob> pixelShader;
    };
}
#endif // !__DXAPP_H__


