#include "TheGame.h"

int main(int argc, char *argv[])
{
	CEngine Engine("The Game");
	Engine.MainLoop();
	Engine.~CEngine();

    return 0;
}
