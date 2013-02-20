#include "Render.h"

CRender::CRender(IEngine *pEngine)
{
    _pEngine = pEngine;
    GenerateNewGUIItem(GT_PANEL, (IGraphicalUserInterface *&)_pMainPanel);
}

HRESULT CRender::GetRender2d(IRender2d *Render2d)
{
    return H_OK;
}

HRESULT CRender::GetRender3d(IRender3d *Render3d)
{
    return H_OK;
}

HRESULT CRender::AllowAutomaticSwappingProjectionType(bool Allow)
{
    return H_OK;
}

HRESULT CRender::SetProjectionType(E_PROJECTION_TYPE ProjectionType)
{
    return H_OK;
}

HRESULT CRender::GetMainUIPanel(IPanel *&Panel)
{
    Panel = _pMainPanel;
    return H_OK;
}

HRESULT CRender::GenerateNewGUIItem(E_GUI_TYPE Type, IGraphicalUserInterface *&Item)
{
    CGraphicalUserInterface *NewItem;
    switch (Type) {
        case KSU::GT_BUTTON:
            NewItem = new CButton();
            break;
        case KSU::GT_CHECK_BOX:
            NewItem = new CCheckBox();
            break;
        case KSU::GT_COMBO_BOX:
            NewItem = new CComboBox();
            break;
        case KSU::GT_LABEL:
            NewItem = new CLabel();
            break;
        case KSU::GT_PANEL:
            NewItem = new CPanel();
            break;
        default:
            return H_FALSE;
            break;
    }
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