#include "GameModel.h"
#include "glfw.h"

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
    EngineCore->GetSubSystem(ES_RESOURSE_MANAGER, (IEngineSubsystem *&)ResourceManager);
    count = 0;
    EngineCore->GetSubSystem(ES_PHYSICS, (IEngineSubsystem*&)_Physics);
    ResourceManager->GenerateResource(RT_COLLIDABLE, (IResource *&)_Collidable);
    ResourceManager->GenerateResource(RT_CAMERA, (IResource *&)_Camera);
    _Camera->SetPosition({1,1,1});
    _Camera->SetTopVector({0,0,1});
    _Physics->AddObject(_Collidable);
    _Collidable->SetPosition({0,0,0});
}

void CGameModel::Process()
{
    count++;
    if (count == 100)
        EngineCore->StopEngine();
    EngineCore->AddToLog("process");
    _Camera->AutomaticProcessingInput();
}

void CGameModel::Render()
{
    EngineCore->AddToLog("render");
    TVector3d pos = _Collidable->GetPosition();
    
    _Camera->Draw();
    
    glTranslatef(0, 0, -6);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(1, 1, 0);
    glVertex3f(-1, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glEnd();
    
    glBegin(GL_POINT);
    glColor3f(1, 0, 0);
    glVertex3f(pos.x, pos.y, pos.z-1);
    glEnd();
}

void CGameModel::Free()
{
    EngineCore->AddToLog("free");
}
