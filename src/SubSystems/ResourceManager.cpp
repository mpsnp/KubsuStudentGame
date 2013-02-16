#include "ResourceManager.h"
#include "../Model3d.h"
#include "../Camera.h"

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
            break;
            
        case KSU::RT_SHAPE:
            break;
            
        case KSU::RT_SOUND_SAMPLE:
            break;
            
        case KSU::RT_TEXTURE:
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
    for (int i = 0; i<_pResources.size(); i++) {
        if (pResource == _pResources[i]) {
            _pResources.erase(_pResources.begin() + i);
            break;
        }
    }
    delete pResource;
    pResource = NULL;
	return H_OK;
}


HRESULT CResourceManager::GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem)
{
    EngineSubSystem = ES_RESOURSE_MANAGER;
    return H_OK;
}