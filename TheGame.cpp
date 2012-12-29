
//#include "stdafx.h"
#include "TheGame.h"


//HINSTANCE hInst;
#ifdef _WIN32
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
#elif __linux__
int main(int argc, char *argv[])
#endif
{
	//UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);

	//hInst = hInstance;

	CEngine Engine("The Game");
	Engine.MainLoop();
	Engine.~CEngine();

    return 0;
	//PostQuitMessage(0);
}
