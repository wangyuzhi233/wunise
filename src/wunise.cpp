#include <Windows.h>
#include "wunise.h"

namespace wunise{

}
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	wunise::Game game;
	game.Run();
	return 0;
}


