#include "Render2d.h"
#include "../glfw.h"

HRESULT CRender2d::DrawRectangle(TVector2d UpLeft, TVector2d DownRight, KSU::ITexture *pTexture)
{
    glBegin(GL_QUADS);
        glVertex2f(<#GLfloat x#>, <#GLfloat y#>)
    glEnd();
    return H_OK;
}