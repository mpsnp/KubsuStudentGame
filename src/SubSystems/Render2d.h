#ifndef _RENDER_2D_H
#define _RENDER_2D_H

#include "../CommonIncludes.h"

class CRender2d: public IRender2d
{
public:
    HRESULT DrawRectangle(TVector2d UpLeft, TVector2d DownRight, ITexture *pTexture);    
};

#endif //_RENDER_2D_H