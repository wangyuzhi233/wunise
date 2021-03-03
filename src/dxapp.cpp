#include "wunise/dxapp.h"
#include <utility>
namespace wunise {

    DXAPP::DXAPP(DXAPP&& r) noexcept
    {
        m_Device = std::move(r.m_Device);
        m_DeviceContext = std::move(r.m_DeviceContext);
        m_SwapChain = std::move(r.m_SwapChain);
        m_Factory = std::move(r.m_Factory);
    }


    DXAPP& DXAPP::operator=(DXAPP&& r) noexcept
    {
        m_Device = std::move(r.m_Device);
        m_DeviceContext = std::move(r.m_DeviceContext);
        m_SwapChain = std::move(r.m_SwapChain);
        m_Factory = std::move(r.m_Factory);
        return *this;
    }

	void DXAPP::InitDevice() {
        UINT createDeviceFlags = 0;
        UINT dxgiFactoryFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
        };
        D3D_FEATURE_LEVEL myFeature;
        Microsoft::WRL::ComPtr<ID3D11Device>  __Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>__DeviceContext;
        Microsoft::WRL::ComPtr<IDXGIAdapter4> __Adapter;
        CreateDXGIFactory2(dxgiFactoryFlags,IID_PPV_ARGS(&m_Factory));
        m_Factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS (&__Adapter));
        D3D11CreateDevice(
            __Adapter.Get(),
            D3D_DRIVER_TYPE_UNKNOWN,
            nullptr, 
            createDeviceFlags, 
            featureLevels, 
            2, 
            D3D11_SDK_VERSION, 
            __Device.ReleaseAndGetAddressOf(), 
            &myFeature, 
            __DeviceContext.ReleaseAndGetAddressOf());
        __Device.As(&m_Device);
        __DeviceContext.As(&m_DeviceContext);
        
    }

    void DXAPP::InitSwapChain(HWND hwnd,UINT w,UINT h) {
        //m_Factory->CreateSwapChainForHwnd
        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.Width = w;
        sd.Height = h;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        // 是否开启4倍多重采样？

        
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        sd.Flags = 0;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd = {};
        fd.RefreshRate.Numerator = 60;
        fd.RefreshRate.Denominator = 1;
        fd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        fd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        fd.Windowed = TRUE;
        Microsoft::WRL::ComPtr<IDXGISwapChain1>__SwapChain;
        m_Factory->CreateSwapChainForHwnd(m_Device.Get(), hwnd, &sd, &fd, nullptr, __SwapChain.ReleaseAndGetAddressOf());
        __SwapChain.As(&m_SwapChain);
        m_Factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
    }

    void DXAPP::SwapChain() {
        m_SwapChain->Present(1, 0);
    }
}