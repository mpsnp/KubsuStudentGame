#include "src/KSUEngine.h"
#include "src/Game/GameModel.h"

using namespace KSU;

int main(int argc, char *argv[])
{
    IEngine* Engine = NULL;
    CGameModel* Game;
    
    if (GetEngine(Engine) == H_OK)
    {           
        Game = new CGameModel(Engine);
        
        Engine->SetGame((IGame *)Game);
        
        Engine->InitWindowAndSubsystems("TheGame",EIF_DEFAULT /*| EIF_FULLSCREEN*/);
        
        FreeEngine();
        
        delete Game;
        return 0;
    }
    else
        return 1;
}
