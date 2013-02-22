#include "GameModel.h"
#include <cstring>
#include "stdlib.h"
#include "glfw.h"

CGameModel::CGameModel(void *pEngineCore)
{
    _EngineCore = (IEngine *)pEngineCore;
}

CGameModel::~CGameModel()
{
    
}

void CGameModel::Init()
{
    _EngineCore->GetSubSystem(ES_INPUT, (IEngineSubsystem *&)_Input);
    _EngineCore->GetSubSystem(ES_RESOURSE_MANAGER, (IEngineSubsystem *&)_ResourceManager);
    _EngineCore->GetSubSystem(ES_RENDER, (IEngineSubsystem *&)_Render);
    
    ITexture *tempTexture;
    _ResourceManager->GenerateResource(RT_TEXTURE, (IResource *&)tempTexture);
    tempTexture->LoadFromFile("data/textures/Flyer.tga");
    
    IMesh *pMesh;
    _ResourceManager->GenerateResource(RT_MESH, (IResource *&)pMesh);
    pMesh->LoadFromFile("data/models/Flyer.3ds");
    pMesh->SetTexture(tempTexture);
    
    Vec = new CVehicle(_ResourceManager, pMesh);
    Vec->SetPosition(TVector3d(0,0,0));
    Vec->SetAngle(0);
    
    Vec2 = new CVehicle(_ResourceManager, pMesh);
    Vec2->SetPosition(TVector3d(7,0,0));
    Vec2->SetAngle(0);
    
    Wall = new CWall(_ResourceManager);
    Wall->SetPoints(TVector3d(10,10,0), TVector3d(10,-10,0));
    
    _ResourceManager->GenerateResource(RT_CAMERA, (IResource *&)_pCamera);
    _pCamera->SetPosition({2,0,0});
    
    IPanel *pMainPanel;
    _Render->GetMainUIPanel(pMainPanel);
    
    pMainPanel->SetPosition({0,0});
    pMainPanel->SetSize({100,100});
    pMainPanel->SetTexture(tempTexture);
    _EngineCore->AddToLog("Game succsessfully initialized!");
}

void CGameModel::Process()
{
	if (_Input->KeyPressed(KEY_ESCAPE) == H_OK)
		_EngineCore->StopEngine();
    
    if (_Input->KeyPressed(KEY_A) == H_OK)
        Vec->Rotate(0.1);
    if (_Input->KeyPressed(KEY_D) == H_OK)
        Vec->Rotate(-0.1);
    if (_Input->KeyPressed(KEY_W) == H_OK)
        Vec->Force(-5);
    if (_Input->KeyPressed(KEY_S) == H_OK)
        Vec->Force(5);
    
    _pCamera->SetPosition(Vec->GetPosition() + Vec->GetVelocity() * -4. + TVector3d(cos(Vec->GetAngle()), sin(Vec->GetAngle()), 0) * 3 + TVector3d(0,0,4));
    _pCamera->SetHorizontalAngle(PI + Vec->GetAngle());
    _pCamera->AutomaticProcessingInput();
    
    _EngineCore->AddToLog("process");
}

void CGameModel::Render()
{
    _pCamera->Draw();
    
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(10, 10, 0);
    glVertex3f(-10, 10, 0);
    glVertex3f(-10, -10, 0);
    glVertex3f(10, -10, 0);
    glEnd();
    
    Vec->Draw();
    Vec2->Draw();
    Wall->Draw();
    
    _EngineCore->AddToLog("render");
}

void CGameModel::Free()
{
    _EngineCore->AddToLog("free");
}
