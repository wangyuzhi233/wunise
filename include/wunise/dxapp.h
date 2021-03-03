#pragma once
#ifndef __DXAPP_H__
#define __DXAPP_H__
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
namespace wunise {
    class DXAPP {
    public:
        DXAPP() {}
        ~DXAPP() {}
        DXAPP(const DXAPP& r) {
            m_Device = r.m_Device;
            m_DeviceContext = r.m_DeviceContext;
            m_SwapChain = r.m_SwapChain;
            m_Factory = r.m_Factory;
        }
        DXAPP(DXAPP&& r) noexcept;
        DXAPP& operator=(const DXAPP& r) {
            m_Device = r.m_Device;
            m_DeviceContext = r.m_DeviceContext;
            m_SwapChain = r.m_SwapChain;
            m_Factory = r.m_Factory;
            return *this;
        }
        DXAPP& operator=(DXAPP&& r) noexcept;

        void InitDevice();
        void InitSwapChain(HWND hwnd,UINT w, UINT h);
        void SwapChain();
    private:
        Microsoft::WRL::ComPtr<ID3D11Device5> m_Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext4> m_DeviceContext;
        Microsoft::WRL::ComPtr<IDXGISwapChain4>m_SwapChain;
        Microsoft::WRL::ComPtr<IDXGIFactory7> m_Factory;
    };
}
#endif // !__DXAPP_H__


