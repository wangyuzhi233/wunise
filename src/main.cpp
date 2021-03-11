#include <Windows.h>
#include "wunise.h"
#include "gamewindow.h"
#include "d11rendersystem.h"
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    wunise::GameWindow game;
    game.CreateGameWindow();
    wunise::D11RenderSystem rs;
    rs.Initialize(wunise::GetHWND(), 800, 600);
    while (game.GameLoop()) {

    }
    game.DestroyGameWindow();
    return 0;
}