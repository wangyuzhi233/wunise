#include <Windows.h>
#include "game.h"
#include <utility>
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    wunise::Game gameother;
    return gameother.Run();
}