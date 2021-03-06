#include "wunise/dxapp.h"
#include <d3dcompiler.h>
#include <utility>
namespace wunise {

    DXAPP::DXAPP(DXAPP&& r) noexcept
    {
        m_SwapChain = std::move(r.m_SwapChain);
        m_Device = std::move(r.m_Device);
        m_DeviceContext = std::move(r.m_DeviceContext);
        m_RenderTargetView = std::move(r.m_RenderTargetView);
    }


    DXAPP& DXAPP::operator=(DXAPP&& r) noexcept
    {
        m_SwapChain = std::move(r.m_SwapChain);
        m_Device = std::move(r.m_Device);
        m_DeviceContext = std::move(r.m_DeviceContext);
        m_RenderTargetView = std::move(r.m_RenderTargetView);
        return *this;
    }

    void DXAPP::CreateDeviceAndSwapChain(HWND hwnd,UINT w,UINT h) {
        UINT createDeviceFlags = 0;
        UINT dxgiFactoryFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1
        },featureLevel;

        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        sd.BufferCount = 1;
        sd.BufferDesc.Width = w;
        sd.BufferDesc.Height = h;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hwnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;
        Microsoft::WRL::ComPtr<ID3D11Device> Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;
        Microsoft::WRL::ComPtr<IDXGIFactory7> Factory;
        Microsoft::WRL::ComPtr<IDXGIAdapter4> Adapter;
        CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&Factory));
        Factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&Adapter));
        D3D11CreateDeviceAndSwapChain(
            Adapter.Get(),
            D3D_DRIVER_TYPE_UNKNOWN,
            nullptr,
            createDeviceFlags,
            featureLevels,
            1,
            D3D11_SDK_VERSION,
            &sd,
            &SwapChain,
            &Device,
            &featureLevel,
            &DeviceContext
        );
        SwapChain.As(&m_SwapChain);
        Device.As(&m_Device);
        DeviceContext.As(&m_DeviceContext);
    }

    void DXAPP::CreateRenderTargetView() {
        ID3D11Texture2D1* pBackBuffer = NULL;
        m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetView);
        pBackBuffer->Release();
    }

    void DXAPP::SetRenderTargets() {
        m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), NULL);
    }

    void DXAPP::SetViewports(float w, float h){
        D3D11_VIEWPORT vp;
        vp.Width = (FLOAT)w;
        vp.Height = (FLOAT)h;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        m_DeviceContext->RSSetViewports(1, &vp);
    }
    void DXAPP::ClearRenderTargetView(float r, float g, float b, float a){
        float ClearColor[] = { r, g, b, a }; //red,green,blue,alpha
        m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), ClearColor);
    }
    void DXAPP::Present(){
        m_SwapChain->Present(1, 0);
    }
    void DXAPP::CompileVertexShader(const wchar_t*Path,const char* Entrypoint)
    {
#if defined(_DEBUG)
        // Enable better shader debugging with the graphics debugging tools.
        UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
        UINT compileFlags = 0;
#endif
      
        D3DCompileFromFile(Path, nullptr, nullptr, Entrypoint, "vs_5_0", compileFlags, 0, &vertexShader, nullptr);

    }



}