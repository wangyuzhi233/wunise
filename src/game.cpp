#include "game.h"
#include "gamewindow.h"
#include "renderer.h"
#include <Windows.h>
#include <utility>

namespace wunise {



	class _game_proc_context {
	public:
		_game_proc_context() :_window(nullptr), _renderer(nullptr) {}
		~_game_proc_context() {}
		_game_proc_context(_game_proc_context&&) noexcept = default;
		_game_proc_context& operator=(_game_proc_context&&) noexcept = default;
		_game_proc_context(const _game_proc_context&) = delete;
		_game_proc_context& operator=(const _game_proc_context&) = delete;
		GameWindow* _window;
		Renderer* _renderer;
	};

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		auto game_proc = reinterpret_cast<_game_proc_context*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
		switch (message)
		{
		//�˳���Ϸ һ����alt+f4 ����˳���ť��
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}

	Game::Game()
	{
		window = std::make_unique<GameWindow>();
		renderer = std::make_unique<Renderer>();
		_proc = std::make_unique<_game_proc_context>();
		_proc->_window = window.get();
		_proc->_renderer = renderer.get();
	}

	Game::~Game(){}

	Game::Game(Game&& r) noexcept
	{
		window = std::move(r.window);
		renderer = std::move(r.renderer);
		_proc = std::move(r._proc);
	}

	Game& Game::operator=(Game&& r) noexcept
	{
		if (this != std::addressof(r)) {
			window = std::move(r.window);
			renderer = std::move(r.renderer);
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
		wcex.hIcon = LoadIconW(wcex.hInstance, L"IDI_ICON");
		wcex.hCursor = LoadCursorW(NULL, MAKEINTRESOURCEW(32512));
		wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wcex.lpszClassName = L"__WUNISE_CLASS";
		wcex.hIconSm = LoadIconW(wcex.hInstance, L"IDI_ICON");
		if (!RegisterClassExW(&wcex))
			return 1;

		RECT rc = { 0, 0, static_cast<LONG>(800), static_cast<LONG>(600) };

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		HWND hwnd = CreateWindowExW(0, wcex.lpszClassName, L"wunise", WS_OVERLAPPEDWINDOW,
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

		DestroyWindow(hwnd);
		UnregisterClassW(wcex.lpszClassName, wcex.hInstance);
		return static_cast<int>(msg.wParam);
	}
}