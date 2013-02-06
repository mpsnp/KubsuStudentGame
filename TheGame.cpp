#include "src/KSUEngine.h"

using namespace KSU;

IEngine* Engine = NULL;
int counter = 0;

void Init(void* pParam)
{
    Engine->AddToLog("Init!");
}

void Process(void *pParam)
{
    if (counter % 10 == 0)
        Engine->AddToLog("a");
    counter++;
    if (counter == 100)
        Engine->StopEngine();
}

void Render(void *pParam)
{
    
}

void Free(void *pParam)
{
    Engine->AddToLog("Free!");
}

int main(int argc, char *argv[])
{
    if (GetEngine(Engine) == H_OK)
    {
        Engine->AddFunction(EPT_INIT, &Init);
        Engine->AddFunction(EPT_PROCESS, &Process);
        Engine->AddFunction(EPT_RENDER, &Render);
        Engine->AddFunction(EPT_FREE, &Free);
        
        Engine->InitWindowAndSubsystems("TheGame",EIF_DEFAULT/* | EIF_FULLSCREEN */);
        
        FreeEngine();
        return 0;
    }
    else
        return 1;
}
