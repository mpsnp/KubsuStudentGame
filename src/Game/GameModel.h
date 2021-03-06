#ifndef _GAME_MODEL_H
#define _GAME_MODEL_H

#include "../KSUEngine.h"

using namespace KSU;

class CGameModel: public IGame
{
    IEngine     *_EngineCore;
	IInput		*_Input;
    IResourceManager *_ResourceManager;
    IRender     *_Render;
    
    IMesh       *_pMesh;
    ICamera     *_pCamera;
    int count;
    
public:
    CGameModel(void *pEngineCore);
    ~CGameModel();
    
    void Init();
    void Process();
    void Render();
    void Free();
};

#endif
