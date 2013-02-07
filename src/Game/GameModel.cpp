#include "GameModel.h"

CGameModel::CGameModel(void *pEngineCore)
{
    EngineCore = (IEngine *)pEngineCore;
}

CGameModel::~CGameModel()
{
    
}

void CGameModel::Init()
{
    EngineCore->AddToLog("init");
    count = 0;
}

void CGameModel::Process()
{
    count++;
    if (count == 100)
        EngineCore->StopEngine();
    EngineCore->AddToLog("process");
}

void CGameModel::Render()
{
    
    EngineCore->AddToLog("render");
}

void CGameModel::Free()
{
    
    EngineCore->AddToLog("free");
}
