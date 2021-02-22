#ifndef UNICODE
#define UNICODE
#endif
#include "wunise/wunise.h"


//// Main message handler for the sample.
//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    //DXSample* pSample = reinterpret_cast<DXSample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
//
//    switch (message)
//    {
//    case WM_CREATE:
//    {
//
//    }
//    return 0;
//
//    case WM_KEYDOWN:
//        //if (pSample)
//        //{
//        //    pSample->OnKeyDown(static_cast<UINT8>(wParam));
//        //}
//        return 0;
//
//    case WM_KEYUP:
//        //if (pSample)
//        //{
//        //    pSample->OnKeyUp(static_cast<UINT8>(wParam));
//        //}
//        return 0;
//
//    case WM_PAINT:
//        //if (pSample)
//        //{
//        //    pSample->OnUpdate();
//        //    pSample->OnRender();
//        //}
//        //draw
//        return 0;
//
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        return 0;
//    }
//
//    // Handle any messages the switch statement didn't.
//    return DefWindowProc(hWnd, message, wParam, lParam);
//}
//
//int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {
//
//    // Initialize the window class.
//    WNDCLASSEX windowClass = { 0 };
//    windowClass.cbSize = sizeof(WNDCLASSEX);
//    windowClass.style = CS_HREDRAW | CS_VREDRAW;
//    windowClass.lpfnWndProc = WindowProc;
//    windowClass.hInstance = hInstance;
//    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//    windowClass.lpszClassName = L"DXSampleClass";
//    RegisterClassEx(&windowClass);
//
//    RECT windowRect = { 0, 0, static_cast<LONG>(800), static_cast<LONG>(600) };
//    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
//
//    HWND m_hwnd = CreateWindow(
//        windowClass.lpszClassName,
//        L"SSS",
//        WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT,
//        CW_USEDEFAULT,
//        windowRect.right - windowRect.left,
//        windowRect.bottom - windowRect.top,
//        nullptr,        // We have no parent window.
//        nullptr,        // We aren't using menus.
//        hInstance,
//        nullptr);
//
//    // Initialize the sample. OnInit is defined in each child-implementation of DXSample.
//
//    ShowWindow(m_hwnd, nCmdShow);
//
//    // Main sample loop.
//    MSG msg = {};
//    while (msg.message != WM_QUIT)
//    {
//        // Process any messages in the queue.
//        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//    }
//    //destory
//
//	return 0;
//}