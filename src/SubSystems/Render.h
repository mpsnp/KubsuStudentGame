#ifndef _RENDER_H
#define _RENDER_H

#include "../CommonIncludes.h"
#include "../GUI.h"
#include <vector>

class CRender: public IRender
{
private:
    IEngine *_pEngine;
    vector<CGraphicalUserInterface *> _GuiItems;
    CPanel *_pMainPanel;
public:
    CRender(IEngine *);
    
    HRESULT GetRender2d(IRender2d *Render2d);
    HRESULT GetRender3d(IRender3d *Render3d);
    HRESULT AllowAutomaticSwappingProjectionType(bool Allow = true);
    HRESULT SetProjectionType(E_PROJECTION_TYPE ProjectionType);
    HRESULT GetMainUIPanel(IPanel *&Panel);
    HRESULT GenerateNewGUIItem(E_GUI_TYPE Type, IGraphicalUserInterface *&Item);
    HRESULT DeleteGUIItem(IGraphicalUserInterface *Item);
    HRESULT GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem);
    
};

#endif //_RENDER_H