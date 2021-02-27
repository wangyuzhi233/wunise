#pragma once
#ifndef __APPLICATION__H__
#define __APPLICATION__H__
#include <Windows.h>
#include <gl/GL.h>
namespace wunise {
	
	class Application {
	public:
		Application() {
			dc = NULL;
			msg = {};
		}
		~Application() {}
		Application(const Application& r) { dc = r.dc; msg = r.msg; }
		Application(Application&&r) noexcept { dc = r.dc; msg = r.msg; }
		Application& operator=(const Application&r) { dc = r.dc; msg = r.msg; return *this; }
		Application& operator=(Application&&r) noexcept { dc = r.dc; msg = r.msg; return *this; }

		void InitWindow(HINSTANCE hInstance, int w, int h);
		bool WindowShouldClose();
		void SwapBuffer();
		void DestroyWindow();
	private:
		HDC dc;
		MSG msg;
	};
}

#endif // !__APPLICATION__H__
