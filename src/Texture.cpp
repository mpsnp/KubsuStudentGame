#include "Texture.h"


CTexture::CTexture()
{
    _Texture = -1;
}

CTexture::~CTexture()
{
    DeleteTexture();
}

HRESULT CTexture::GetType(KSU::E_RESOURCE_TYPE &Type)
{
    Type = RT_TEXTURE;
    return H_OK;
}

HRESULT CTexture::LoadFromFile(char *FileName)
{
    glGenTextures(1,&_Texture);
	glBindTexture(GL_TEXTURE_2D,_Texture);
	if(!glfwLoadTexture2D(FileName, GLFW_BUILD_MIPMAPS_BIT))
		return H_FALSE;
    return H_OK;
}

HRESULT CTexture::BindTexture()
{
    if (!(_Texture == -1))
        glBindTexture(GL_TEXTURE_2D, _Texture);
    return H_OK;
}

HRESULT CTexture::LoadToGPU()
{
    //TODO: пока не нужна, но если будет поддержка нескольких форматов, кроме *.tif, то генерация текстуры в памяти GPU будет здесь.
    return H_OK;
}

HRESULT CTexture::DeleteTexture()
{
    if (!(_Texture == -1))
        glDeleteTextures(1, &_Texture);
    _Texture = -1;
    return H_OK;
}