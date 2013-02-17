#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "CommonIncludes.h"
#include "glfw.h"

class CTexture: public ITexture
{
    GLuint _Texture;
public:
    CTexture();
    ~CTexture();
    HRESULT GetType(E_RESOURCE_TYPE &Type);
    HRESULT LoadFromFile(char *FileName);
    HRESULT BindTexture();
    HRESULT LoadToGPU();
    HRESULT DeleteTexture();
};

#endif //_TEXTURE_H
