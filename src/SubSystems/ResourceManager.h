#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "../CommonIncludes.h"
#include <vector>

class CResourceManager: public IResourceManager
{
    vector<IResource*> _pResources;
public:
    HRESULT GenerateResource(const E_RESOURCE_TYPE ResourceType, IResource *&pResource);
    HRESULT LoadResource(char *pFileName, IResource *pResource);
    HRESULT FreeResource(IResource *&pResource);
    HRESULT GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem);
};

#endif //_RESOURCE_MANAGER_H