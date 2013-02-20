#include "Render.h"
#include "../glfw.h"

CRender::CRender(IEngine *pEngine)
{
    _pEngine = pEngine;
    _pMainPanel = NULL;
    _pRender2d = NULL;
}

void CRender::DrawGUI()
{
    SetProjectionType(PT_2D);
    _pMainPanel->Draw();
    SetProjectionType(PT_3D);
}

CRender::~CRender()
{
    //TODO: Исправить
    //CGraphicalUserInterface *TempItem;
   /* while (_GuiItems.size() > 0) {
        //TempItem = _GuiItems[_GuiItems.size() - 1];
        //delete TempItem;
        _GuiItems.erase(_GuiItems.end());
    }*/
}

HRESULT CRender::GetRender2d(IRender2d *&Render2d)
{
    if (!_pRender2d)
        _pRender2d = new CRender2d();
    Render2d = _pRender2d;
    return H_OK;
}

HRESULT CRender::GetRender3d(IRender3d *&Render3d)
{
    return H_OK;
}

HRESULT CRender::AllowAutomaticSwappingProjectionType(bool Allow)
{
    return H_OK;
}

HRESULT CRender::SetProjectionType(E_PROJECTION_TYPE ProjectionType)
{
    glfwGetWindowSize(&_Width, &_Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch (ProjectionType) {
        case KSU::PT_2D:
            gluOrtho2D(0, _Width, _Height, 0);
            break;
        case KSU::PT_3D:
            gluPerspective(45, _Width / _Height, 0.0011, 500);
            break;
        default:
            break;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return H_OK;
}

HRESULT CRender::GetMainUIPanel(IPanel *&Panel)
{
    if (!_pMainPanel)
        GenerateNewGUIItem(GT_PANEL, (IGraphicalUserInterface *&)_pMainPanel);
    Panel = _pMainPanel;
    return H_OK;
}

HRESULT CRender::GenerateNewGUIItem(E_GUI_TYPE Type, IGraphicalUserInterface *&Item)
{
    CGraphicalUserInterface *NewItem;
    switch (Type) {
        case KSU::GT_BUTTON:
            NewItem = new CButton(this);
            break;
        case KSU::GT_CHECK_BOX:
            NewItem = new CCheckBox(this);
            break;
        case KSU::GT_COMBO_BOX:
            NewItem = new CComboBox(this);
            break;
        case KSU::GT_LABEL:
            NewItem = new CLabel(this);
            break;
        case KSU::GT_PANEL:
            NewItem = new CPanel(this);
            break;
        default:
            return H_FALSE;
            break;
    }
    _GuiItems.push_back(NewItem);
    Item = NewItem;
    return H_OK;
}

HRESULT CRender::DeleteGUIItem(IGraphicalUserInterface *Item)
{
    std::vector<CGraphicalUserInterface *>::iterator it;
    it = find(_GuiItems.begin(), _GuiItems.end(), Item);
    
    if (*it == Item)
    {
        delete *it;
        _GuiItems.erase(it);
        Item = NULL;
        return H_OK;
    }
    
    return H_FALSE;
}

HRESULT CRender::GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem)
{
    EngineSubSystem = ES_RENDER;
    return H_OK;
}