#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "../CommonIncludes.h"

class CResourceManager: public IResourceManager
{
public:
    HRESULT GenerateResource(const E_RESOURCE_TYPE ResourceType, IResource *&pResource);
    HRESULT LoadResource(char *pFileName, IResource *pResource);
    HRESULT FreeResource(IResource *&pResource);
    HRESULT GenerateTexture(ITexture *&pTexture);	
};

#endif //_RESOURCE_MANAGER_H