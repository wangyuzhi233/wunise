#include "game.h"
#include "gamewindow.h"
#include "rendersystem.h"
#include "d3d11rendersystem.h"
#include <Windows.h>
#include <utility>

namespace wunise {



	class _game_proc_context {
	public:
		_game_proc_context() :_window(nullptr), _render(nullptr) {}
		~_game_proc_context() {}
		_game_proc_context(_game_proc_context&&) noexcept = default;
		_game_proc_context& operator=(_game_proc_context&&) noexcept = default;
		_game_proc_context(const _game_proc_context&) = delete;
		_game_proc_context& operator=(const _game_proc_context&) = delete;
		GameWindow* _window;
		RenderSystem* _render;
	};

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		auto game_proc = reinterpret_cast<_game_proc_context*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
		switch (message)
		{
		case WM_PRINT:
			return 0;
		//退出游戏 一般是alt+f4 点击退出按钮等
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}

	Game::Game()
	{
		window = std::make_unique<GameWindow>();
		rendersystem = std::make_unique<D3D11RenderSystem>();
		_proc = std::make_unique<_game_proc_context>();
		_proc->_window = window.get();
		_proc->_render = rendersystem.get();
	}

	Game::~Game(){}

	Game::Game(Game&& r) noexcept
	{
		window = std::move(r.window);
		rendersystem = std::move(r.rendersystem);
		_proc = std::move(r._proc);
	}

	Game& Game::operator=(Game&& r) noexcept
	{
		if (this != std::addressof(r)) {
			window = std::move(r.window);
			rendersystem = std::move(r.rendersystem);
			_proc = std::move(r._proc);
		}
		return *this;
	}

	int Game::Run()
	{
		WNDCLASSEXW wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEXW);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.hInstance = GetModuleHandleW(NULL);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(32512));
		wcex.lpszClassName = L"___wuniseClass";
		if (!RegisterClassExW(&wcex))
			return 1;

		RECT rc = { 0, 0, static_cast<LONG>(window->GetWidth()), static_cast<LONG>(window->GetHeight()) };

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, FALSE);

		HWND hwnd = CreateWindowExW(0, wcex.lpszClassName,window->GetTitle().c_str(), WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, wcex.hInstance,
			nullptr);
		if (!hwnd)
			return 1;

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(_proc.get()));
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
}