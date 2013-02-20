#include "Render2d.h"
#include "../glfw.h"

HRESULT CRender2d::DrawRectangle(TVector2d UpLeft, TVector2d DownRight, KSU::ITexture *pTexture)
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    //pTexture->BindTexture();
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(UpLeft.x, UpLeft.y);
    glTexCoord2f(1, 0);
    glVertex2f(UpLeft.x, DownRight.y);
    glTexCoord2f(1, 1);
    glVertex2f(DownRight.x, DownRight.y);
    glTexCoord2f(0, 1);
    glVertex2f(DownRight.x, UpLeft.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    return H_OK;
}