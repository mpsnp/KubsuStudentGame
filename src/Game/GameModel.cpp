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
	EngineCore->GetSubSystem(ES_INPUT, (IEngineSubsystem *&)Input);
    count = 0;
}

void CGameModel::Process()
{
    count++;
    if (count == 100)
        EngineCore->StopEngine();
	if (Input->KeyPressed(KEY_LCONTROL) == H_OK)
		EngineCore->AddToLog("KEY_LCONTROL pressed!");
}

void CGameModel::Render()
{
   
}

void CGameModel::Free()
{
    
    EngineCore->AddToLog("free");
}
