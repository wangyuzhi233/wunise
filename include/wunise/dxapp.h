#pragma once
#ifndef __DXAPP_H__
#define __DXAPP_H__
#include <d3d11_4.h>
#include <wrl/client.h>
namespace wunise {
    class DXAPP {
    public:
        DXAPP() {}
        ~DXAPP() {}
        DXAPP(const DXAPP& r) { m_Device = r.m_Device; m_DeviceContext = r.m_DeviceContext; }
        DXAPP(DXAPP&& r) noexcept;
        DXAPP& operator=(const DXAPP&r) { m_Device = r.m_Device; m_DeviceContext = r.m_DeviceContext; return *this; }
        DXAPP& operator=(DXAPP&& r) noexcept;

        void InitDevice();
    private:
        Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
    };
}
#endif // !__DXAPP_H__


