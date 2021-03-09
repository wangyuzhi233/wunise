#include "game.h"
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

    namespace window {
        LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            static bool s_in_sizemove = false;
            static bool s_in_suspend = false;
            static bool s_minimized = false;
            static bool s_fullscreen = false;
            // TODO: Set s_fullscreen to true if defaulting to fullscreen.

            auto game = reinterpret_cast<wunise::Game*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

            switch (message)
            {
            case WM_PAINT:
                if (s_in_sizemove && game)
                {
                    game->Tick();

                }
                else
                {
                    PAINTSTRUCT ps;
                    (void)BeginPaint(hWnd, &ps);
                    EndPaint(hWnd, &ps);
                }
                break;

            case WM_SIZE:
                if (wParam == SIZE_MINIMIZED)
                {
                    if (!s_minimized)
                    {
                        s_minimized = true;
                        if (!s_in_suspend && game)
                            game->OnSuspending();
                        s_in_suspend = true;
                    }
                }
                else if (s_minimized)
                {
                    s_minimized = false;
                    if (s_in_suspend && game)
                        game->OnResuming();
                    s_in_suspend = false;
                }
                else if (!s_in_sizemove && game)
                {
                    game->OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
                }
                break;

            case WM_ENTERSIZEMOVE:
                s_in_sizemove = true;
                break;

            case WM_EXITSIZEMOVE:
                s_in_sizemove = false;
                if (game)
                {
                    RECT rc;
                    GetClientRect(hWnd, &rc);

                    game->OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
                }
                break;

            case WM_GETMINMAXINFO:
                if (lParam)
                {
                    auto info = reinterpret_cast<MINMAXINFO*>(lParam);
                    info->ptMinTrackSize.x = 320;
                    info->ptMinTrackSize.y = 200;
                }
                break;

            case WM_ACTIVATEAPP:
                if (game)
                {
                    if (wParam)
                    {
                        game->OnActivated();
                    }
                    else
                    {
                        game->OnDeactivated();
                    }
                }
                break;

            case WM_POWERBROADCAST:
                switch (wParam)
                {
                case PBT_APMQUERYSUSPEND:
                    if (!s_in_suspend && game)
                        game->OnSuspending();
                    s_in_suspend = true;
                    return TRUE;

                case PBT_APMRESUMESUSPEND:
                    if (!s_minimized)
                    {
                        if (s_in_suspend && game)
                            game->OnResuming();
                        s_in_suspend = false;
                    }
                    return TRUE;
                }
                break;

            case WM_DESTROY:
                PostQuitMessage(0);
                break;

            case WM_SYSKEYDOWN:
                if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
                {
                    // Implements the classic ALT+ENTER fullscreen toggle
                    if (s_fullscreen)
                    {
                        SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
                        SetWindowLongPtr(hWnd, GWL_EXSTYLE, 0);

                        int width = 800;
                        int height = 600;
                        if (game)
                            game->GetDefaultSize(width, height);

                        ShowWindow(hWnd, SW_SHOWNORMAL);

                        SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
                    }
                    else
                    {
                        SetWindowLongPtr(hWnd, GWL_STYLE, 0);
                        SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);

                        SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                        ShowWindow(hWnd, SW_SHOWMAXIMIZED);
                    }

                    s_fullscreen = !s_fullscreen;
                }
                break;

            case WM_MENUCHAR:
                // A menu is active and the user presses a key that does not correspond
                // to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
                return MAKELRESULT(0, MNC_CLOSE);
            }

            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }

    Game::Game() noexcept :
        m_window(nullptr),
        m_outputWidth(800),
        m_outputHeight(600),
        m_featureLevel(D3D_FEATURE_LEVEL_9_1)
    {
    }

    void Game::Initialize(HWND window)
    {
        m_window = window;
        CreateDevice();
        CreateResources();
        // TODO: Change the timer settings if you want something other than the default variable timestep mode.
        // e.g. for 60 FPS fixed timestep update logic, call:
        /*
        m_timer.SetFixedTimeStep(true);
        m_timer.SetTargetElapsedSeconds(1.0 / 60);
        */
    }

    void Game::Tick()
    {
        float ss[] = { 0,0,0,1.f };
        // Clear the views.
        m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), ss);
        m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

        // Set the viewport.
        CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
        m_d3dContext->RSSetViewports(1, &viewport);



        m_swapChain->Present(1, 0);
    }

    // Message handlers
    void Game::OnActivated()
    {
        // TODO: Game is becoming active window.
    }

    void Game::OnDeactivated()
    {
        // TODO: Game is becoming background window.
    }

    void Game::OnSuspending()
    {
        // TODO: Game is being power-suspended (or minimized).
    }

    void Game::OnResuming()
    {


        // TODO: Game is being power-resumed (or returning from minimize).
    }

    void Game::OnWindowSizeChanged(int width, int height)
    {
        m_outputWidth = width > 1 ? width : 1;
        m_outputHeight = height > 1 ? height : 1;

        CreateResources();

        // TODO: Game window is being resized.
    }

    // Properties
    void Game::GetDefaultSize(int& width, int& height) const noexcept
    {
        // TODO: Change to desired default window size (note minimum size is 320x200).
        width = 800;
        height = 600;
    }

    // These are the resources that depend on the device.
    void Game::CreateDevice()
    {
        UINT creationFlags = 0;

#ifdef _DEBUG
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        static const D3D_FEATURE_LEVEL featureLevels[] =
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
            &m_featureLevel,                    // returns feature level of device created
            context.ReleaseAndGetAddressOf()    // returns the device immediate context
        ));
        DX::ThrowIfFailed(device.As(&m_d3dDevice));
        DX::ThrowIfFailed(context.As(&m_d3dContext));

        // TODO: Initialize device dependent objects here (independent of window size).
    }

    // Allocate all memory resources that change on a window SizeChanged event.
    void Game::CreateResources()
    {
        // Clear the previous window size specific context.
        ID3D11RenderTargetView* nullViews[] = { nullptr };
        m_d3dContext->OMSetRenderTargets(1, nullViews, nullptr);
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