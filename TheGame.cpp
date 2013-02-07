#include "KSUEngine.h"
#include "GameModel.h"

using namespace KSU;

IEngine* Engine = NULL;
CGameModel* Game;
int counter = 0;

void Init(void* pParam)
{
    Game->Init();
}

void Process(void *pParam)
{
    Game->Process();
}

void Render(void *pParam)
{
    Game->Render();
}

void Free(void *pParam)
{
    Game->Free();
}

int main(int argc, char *argv[])
{
    if (GetEngine(Engine) == H_OK)
    {
        Game = new CGameModel(Engine);
        
        Engine->AddFunction(EPT_INIT, &Init);
        Engine->AddFunction(EPT_PROCESS, &Process);
        Engine->AddFunction(EPT_RENDER, &Render);
        Engine->AddFunction(EPT_FREE, &Free);
        
        Engine->InitWindowAndSubsystems("TheGame",EIF_DEFAULT/* | EIF_FULLSCREEN */);
        
        FreeEngine();
        
        delete Game;
        return 0;
    }
    else
        return 1;
}
