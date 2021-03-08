#include "game.h"
#include <utility>

namespace wunise {
	namespace _internal {
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			Game* game = reinterpret_cast<Game*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

			switch (message)
			{
			case WM_CREATE:
			{
				// Save the DXSample* passed in to CreateWindow.
				LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
				SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
			}
			return 0;

			case WM_KEYDOWN:
				if (game)
				{
					//pSample->OnKeyDown(static_cast<UINT8>(wParam));
				
				}
				return 0;

			case WM_KEYUP:
				if (game)
				{
					//pSample->OnKeyUp(static_cast<UINT8>(wParam));
				}
				return 0;

			case WM_PAINT:
				if (game)
				{
					//pSample->OnUpdate();
					//pSample->OnRender();
				}
				return 0;

			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			}

			// Handle any messages the switch statement didn't.
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	Game::Game(){
		Title = L"wunise";
		Width = 800;
		Height = 600;
	}

	Game::Game(const wchar_t* title, int width, int height) {
		Title = title;
		Width = width;
		Height = height;
	}
	Game::Game(const Game& r) {

		Title = r.Title;
		Width = r.Width;
		Height = r.Height;
	}

	Game::Game(Game&& r) noexcept {

		Title = std::move(r.Title);
		Width = r.Width;
		Height = r.Height;
	}
	Game& Game::operator=(const Game& r) {

		Title = r.Title;
		Width = r.Width;
		Height = r.Height;
		return *this;
	}

	Game& Game::operator=(Game&& r) noexcept {
		Title = std::move(r.Title);
		Width = r.Width;
		Height = r.Height;
		return *this;
	}
	Game::~Game() {}

	int Game::Run(HINSTANCE hInstance, int nCmdShow) {
		// Initialize the window class.
		WNDCLASSEX windowClass = { 0 };
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = _internal::WndProc;
		windowClass.hInstance = hInstance;
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.lpszClassName = L"DXSampleClass";
		RegisterClassEx(&windowClass);

		RECT windowRect = { 0, 0, static_cast<LONG>(Width), static_cast<LONG>(Height) };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		// Create the window and store a handle to it.
		HWND m_hwnd = CreateWindow(
			windowClass.lpszClassName,
			Title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			nullptr,        // We have no parent window.
			nullptr,        // We aren't using menus.
			hInstance,
			this);
		ShowWindow(m_hwnd, nCmdShow);

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
			else {

			}
		}

		return static_cast<int>(msg.wParam);
	}


}
