#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "../CommonIncludes.h"
#include <vector>
#include "../Engine.h"

class CResourceManager: public IResourceManager
{
    CEngine *_EngineCore;
    vector<IResource*> _pResources;
public:
    CResourceManager(CEngine *pEngine);
    ~CResourceManager();
    HRESULT GenerateResource(const E_RESOURCE_TYPE ResourceType, IResource *&pResource);
    HRESULT LoadResource(char *pFileName, IResource *pResource);
    HRESULT FreeResource(IResource *&pResource);
    HRESULT GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem);
};

#endif //_RESOURCE_MANAGER_H