#include "game.h"
namespace wunise {
	LRESULT CALLBACK ___WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message)
		{
		//ÍË³öÓÎÏ·
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_MENUCHAR:
			return MAKELRESULT(0, MNC_CLOSE);
		}
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}

	Game::Game() {
		Title = L"wunise";
		Width = 800;
		Height = 600;
		Isfullscreen = false;
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
		CreateFactory();
		CreateDevice();
		CreateCommandQueue();
		CreateSwapChain(hwnd);
		ShowWindow(hwnd, SW_SHOWDEFAULT);

		MSG msg = {};
		while (WM_QUIT != msg.message)
		{
			if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			else {}
		}
		return static_cast<int>(msg.wParam);
	}

	void Game::CreateFactory()
	{
		CreateDXGIFactory2(0, IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf()));
	}
	void Game::CreateDevice()
	{
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(m_d3dDevice.ReleaseAndGetAddressOf()));
	}
	void Game::CreateCommandQueue()
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_commandQueue.ReleaseAndGetAddressOf()));
	}
	void Game::CreateSwapChain(HWND hwnd)
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = Width;
		swapChainDesc.Height = Height;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.Stereo = FALSE;
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc = {};
		fullscreenDesc.RefreshRate.Numerator = 60;
		fullscreenDesc.RefreshRate.Denominator = 1;
		fullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		fullscreenDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
		fullscreenDesc.Windowed = !Isfullscreen;
		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
		m_dxgiFactory->CreateSwapChainForHwnd(
			m_commandQueue.Get(),
			hwnd,
			&swapChainDesc,
			&fullscreenDesc,
			nullptr,
			&swapChain
		);
		swapChain.As(&m_swapChain);
		m_dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
	}



}