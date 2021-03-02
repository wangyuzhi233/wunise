#include <Windows.h>
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
// Main message handler for the sample.

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw;
    }
}

class DXAPP {
public:
    DXAPP() {}
    ~DXAPP() {}
    DXAPP(const DXAPP&) {}
    DXAPP(DXAPP&&) noexcept {}
    DXAPP& operator=(const DXAPP&) { return *this; }
    DXAPP& operator=(DXAPP&&) noexcept { return *this; }

    void InitDevice() {
        UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        D3D_FEATURE_LEVEL featureLevel;
        ID3D11Device* md3dDevice;
        ID3D11DeviceContext* md3dImmediateContext;

        D3D_FEATURE_LEVEL featurearray[] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1,
        };;

        ThrowIfFailed(D3D11CreateDevice(
            0, // default adapter
            D3D_DRIVER_TYPE_HARDWARE,
            0, // no software device
            createDeviceFlags,
            featurearray, 7, // default feature level array
            D3D11_SDK_VERSION,
            &md3dDevice,
            &featureLevel,
            &md3dImmediateContext));

    }
private:
    
};
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // Handle any messages the switch statement didn't.
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd) 
{
    // Initialize the window class.
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

    // Create the window and store a handle to it.
    HWND m_hwnd = CreateWindow(
        windowClass.lpszClassName,
        L"wunise",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window.
        nullptr,        // We aren't using menus.
        hInstance,
        nullptr);

    DXAPP app;
    app.InitDevice();

    ShowWindow(m_hwnd, nShowCmd);

    // Main sample loop.
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {

        }
    }
    return 0;
}
