#include <Windows.h>
#include "wunise/application.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {

    wunise::Application app;
    app.InitWindow(hInstance, 300, 300);

    while (!app.WindowShouldClose()) {

        app.SwapBuffer();
    }
    app.DestroyWindow();
    return 0;
}
