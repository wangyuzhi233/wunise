#include <Windows.h>
#include "gamewindow.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{

    wunise::GameWindow game;
    game.CreateGameWindow();
    while (game.GameLoop()) {

    }
    game.DestroyGameWindow();

    return 0;
}