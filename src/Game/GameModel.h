#ifndef _GAME_MODEL_H
#define _GAME_MODEL_H

#include "../KSUEngine.h"
#include "GameClasses.h"

using namespace KSU;

class CGameModel: public IGame
{
    IEngine     *_EngineCore;
	IInput		*_Input;
    IResourceManager *_ResourceManager;
    IRender     *_Render;
    
    CVehicle    *Vec;
    CVehicle    *Vec2;
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
