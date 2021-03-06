#include "ResourceManager.h"
#include "../Model3d.h"
#include "../Camera.h"
#include "../Texture.h"
#include "Collidable.h"
#include "Shape.h"

CResourceManager::CResourceManager(CEngine *pEngine)
{
    _EngineCore = pEngine;
}

CResourceManager::~CResourceManager()
{
    IResource *pTempResource;
    while (_pResources.size() > 0) {
        pTempResource = _pResources.front();
        FreeResource(pTempResource);
    }
}

HRESULT CResourceManager::GenerateResource(const E_RESOURCE_TYPE ResourceType, IResource *&pResource)
{
    IResource *NewResource;
    //TODO: дописать.
    switch (ResourceType) {
        case KSU::RT_MESH:
            NewResource = new CMesh();
            break;
            
        case KSU::RT_CAMERA:
            NewResource = new CCamera();
            break;
            
        case KSU::RT_COLLIDABLE:
            NewResource = new CCollidable(this->_EngineCore);
            break;
            
        case KSU::RT_SHAPE:
            NewResource = new CShape();
            break;
            
        case KSU::RT_SOUND_SAMPLE:
            break;
            
        case KSU::RT_TEXTURE:
            NewResource = new CTexture();
            break;
    }    
    _pResources.push_back(NewResource);
    pResource = NewResource;
	return H_OK;
}

HRESULT CResourceManager::LoadResource(char *pFileName,  IResource *pResource)
{
    pResource->LoadFromFile(pFileName);
	return H_OK;
}

HRESULT CResourceManager::FreeResource(IResource *&pResource)
{
    std::vector<IResource*>::iterator it;
    it = find(_pResources.begin(), _pResources.end(), pResource);
    
    if (*it == pResource)
        _pResources.erase(it);

    delete pResource;
    pResource = NULL;
	return H_OK;
}


HRESULT CResourceManager::GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem)
{
    EngineSubSystem = ES_RESOURSE_MANAGER;
    return H_OK;
}