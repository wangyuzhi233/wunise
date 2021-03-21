#include "game.h"
namespace wunise {



	LRESULT CALLBACK ___WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message)
		{
		//�˳���Ϸ
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		//��ֹalt��ݼ���������
		case WM_MENUCHAR:
			return MAKELRESULT(0, MNC_CLOSE);
		}
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	Game::Game() {
		Title = L"wunise";
		Width = 800;
		Height = 600;
		//IsFullScreen = false;
	}

	int Game::Run()
	{
		WNDCLASSEXW wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEXW);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = ___WndProc;
		wcex.hInstance = GetModuleHandleW(NULL);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(32512));
		wcex.lpszClassName = L"___wuniseClass";
		if (!RegisterClassExW(&wcex))
			return 1;

		RECT rc = { 0, 0, static_cast<LONG>(Width), static_cast<LONG>(Height) };

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, FALSE);

		HWND hwnd = CreateWindowExW(0, wcex.lpszClassName,Title.c_str(), WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, wcex.hInstance,
			nullptr);
		if (!hwnd)
			return 1;

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		CreateDevice();
		MSG msg = {};
		while (WM_QUIT != msg.message)
		{
			if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			else
			{
				
			}
		}
		return static_cast<int>(msg.wParam);
	}
	void Game::CreateDevice()
	{
		D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(m_d3dDevice.ReleaseAndGetAddressOf()));
	}

}