#include "d11rendersystem.h"
namespace wunise {

    namespace DX
    {
        void ThrowIfFailed(HRESULT hr)
        {
            if (FAILED(hr))
            {
                // Set a breakpoint on this line to catch DirectX API errors
                throw;
            }
        }
    }

	D11RenderSystem::D11RenderSystem() noexcept {
		m_window = NULL;
		m_outputWidth = 1;
		m_outputHeight = 1;
	}
	void D11RenderSystem::Initialize(HWND hwnd, int w, int h)
	{
		RenderSystem::Initialize(hwnd, w, h);
        m_window = hwnd;
		m_outputWidth = w > 1 ? w : 1;
		m_outputHeight = h > 1 ? h : 1;

        UINT creationFlags = 0;

#ifdef _DEBUG
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        const D3D_FEATURE_LEVEL featureLevels[] =
        {
            // TODO: Modify for supported Direct3D feature levels
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1,
        };

        // Create the DX11 API device object, and get a corresponding context.
        Microsoft::WRL::ComPtr<ID3D11Device> device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
        DX::ThrowIfFailed(D3D11CreateDevice(
            nullptr,                            // specify nullptr to use the default adapter
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            featureLevels,
            7,
            D3D11_SDK_VERSION,
            device.ReleaseAndGetAddressOf(),    // returns the Direct3D device created
            nullptr,                    // returns feature level of device created
            context.ReleaseAndGetAddressOf()    // returns the device immediate context
        ));
        DX::ThrowIfFailed(device.As(&m_d3dDevice));
        DX::ThrowIfFailed(context.As(&m_d3dContext));

        CreateResources();

	}

    void D11RenderSystem::CreateResources() {
        ID3D11RenderTargetView* nullViews[] = { nullptr };
        m_d3dContext->OMSetRenderTargets(static_cast<UINT>(1), nullViews, nullptr);
        m_renderTargetView.Reset();
        m_depthStencilView.Reset();
        m_d3dContext->Flush();

        const UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
        const UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
        const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
        const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
        constexpr UINT backBufferCount = 2;
        // If the swap chain already exists, resize it, otherwise create one.
        if (m_swapChain)
        {
            HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);
            DX::ThrowIfFailed(hr);
        }
        else
        {
            // First, retrieve the underlying DXGI Device from the D3D Device.
            Microsoft::WRL::ComPtr<IDXGIDevice1> dxgiDevice;
            DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

            // Identify the physical adapter (GPU or card) this device is running on.
            Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
            DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

            // And obtain the factory object that created it.
            Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
            DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain.ReleaseAndGetAddressOf()
            ));

            // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
            DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
        }

        // Obtain the backbuffer for this window which will be the final 3D rendertarget.
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
        DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

        // Create a view interface on the rendertarget to use on bind.
        DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

        // Allocate a 2-D surface as the depth/stencil buffer and
        // create a DepthStencil view on this surface to use on bind.
        CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

        Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil;
        DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

        CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
        DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

        // TODO: Initialize windows-size dependent objects here.
    }
}