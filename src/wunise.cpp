#include <Windows.h>
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 200
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }


    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd) 
{
    WNDCLASSEX windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = L"wunise";
    RegisterClassEx(&windowClass);

    RECT windowRect = { 0, 0, static_cast<LONG>(WINDOW_WIDTH), static_cast<LONG>(WINDOW_HEIGHT) };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    HWND m_hwnd = CreateWindow(
        windowClass.lpszClassName,
        L"wunise",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        
        nullptr,        
        hInstance,
        nullptr);

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1
    }, featureLevel;
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.BufferCount = 1;
    sd.BufferDesc.Width = WINDOW_WIDTH;
    sd.BufferDesc.Height = WINDOW_HEIGHT;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;
    Microsoft::WRL::ComPtr<ID3D11Device> Device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;
    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
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

    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView;
    ID3D11Texture2D1* pBackBuffer = NULL;
    SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    Device->CreateRenderTargetView(pBackBuffer, NULL, &RenderTargetView);
    pBackBuffer->Release();
    //
    DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), NULL);

    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)WINDOW_WIDTH;
    vp.Height = (FLOAT)WINDOW_HEIGHT;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    DeviceContext->RSSetViewports(1, &vp);

    ShowWindow(m_hwnd, nShowCmd);

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            float ClearColor[] = { 1.F, 0, 0, 1 }; //red,green,blue,alpha
            DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), ClearColor);

            SwapChain->Present(1, 0);
        }
    }

    return 0;
}
