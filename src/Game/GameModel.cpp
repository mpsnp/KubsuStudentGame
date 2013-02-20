#include "GameModel.h"

CGameModel::CGameModel(void *pEngineCore)
{
    _EngineCore = (IEngine *)pEngineCore;
}

CGameModel::~CGameModel()
{
    
}

void CGameModel::Init()
{
    _EngineCore->AddToLog("init");
    _EngineCore->GetSubSystem(ES_RESOURSE_MANAGER, (IEngineSubsystem *&)_ResourceManager);
    _EngineCore->GetSubSystem(ES_RENDER, (IEngineSubsystem *&)_Render);
    
    ITexture *tempTexture;
    _ResourceManager->GenerateResource(RT_TEXTURE, (IResource *&)tempTexture);
    tempTexture->LoadFromFile("data/textures/Flyer.tga");
            
    _ResourceManager->GenerateResource(RT_MESH, (IResource *&)_pMesh);
    _pMesh->LoadFromFile("data/models/Flyer.3ds");
    _pMesh->SetTexture(tempTexture);
    
    _ResourceManager->GenerateResource(RT_CAMERA, (IResource *&)_pCamera);
    _pCamera->SetPosition({2,0,0});
    
    IPanel *pMainPanel;
    _Render->GetMainUIPanel(pMainPanel);
    
    pMainPanel->SetPosition({0,0});
    pMainPanel->SetSize({100,100});
    pMainPanel->SetTexture(tempTexture);
    count = 0;
}

void CGameModel::Process()
{
    count++;
    if (count == 200)
        _EngineCore->StopEngine();
    
    _pCamera->AutomaticProcessingInput();
    
    _EngineCore->AddToLog("process");
}

void CGameModel::Render()
{
    _pCamera->Draw();
    
    _pMesh->Draw();
    _pMesh->Draw({10,10,0});
    _pMesh->Draw({-10,10,0});
    _pMesh->Draw({-10,-10,0});
    _pMesh->Draw({10,-10,0});
    
    _EngineCore->AddToLog("render");
}

void CGameModel::Free()
{
    _EngineCore->AddToLog("free");
}
