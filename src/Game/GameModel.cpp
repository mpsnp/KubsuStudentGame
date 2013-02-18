#include "GameModel.h"
#include <cstring>
#include "stdlib.h"

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
	TMouseState t;
	if (Input->KeyPressed(KEY_ESCAPE) == H_OK)
		EngineCore->StopEngine();

	Input->GetMouseState(t);

	if (t.LeftButtonPressed)
		EngineCore->AddToLog("LeftButtonPressed pressed!");
	if (t.RightButtonPressed)
		EngineCore->AddToLog("RightButtonPressed pressed!");
	if (t.MiddleButtonPressed)
		EngineCore->AddToLog("MiddleButtonPressed pressed!");
	
	char xc[100];
	char yc[100];
	itoa(t.x,xc,10);
	itoa(t.y,yc,10);

	EngineCore->AddToLog(strcat(xc,"-x"));
	EngineCore->AddToLog(strcat(yc,"-y"));

}

void CGameModel::Render()
{
   
}

void CGameModel::Free()
{
    
    EngineCore->AddToLog("free");
}
