#ifndef _GUI_H
#define _GUI_H

#include "CommonIncludes.h"
#include <vector>

class CGraphicalUserInterface:public virtual IGraphicalUserInterface
{
protected:
    IRender *_pRender;
    IRender2d *_pRender2d;
    TVector2d _Position;
    TVector2d _Size;
    TColor _Color;
    ITexture *_pTexture;
public:
    CGraphicalUserInterface(IRender *pRender);
    virtual ~CGraphicalUserInterface();
    HRESULT SetPosition(TVector2d Position);
    HRESULT GetPosition(TVector2d &Position);
    HRESULT SetSize(TVector2d Size);
    HRESULT GetSize(TVector2d &Size);
    HRESULT SetColor(TColor Color);
    HRESULT GetColor(TColor &Color);
    HRESULT SetTexture(ITexture *pTexture);
    
    virtual void Draw() = 0;
};

class CPanel:public IPanel, public CGraphicalUserInterface
{
    vector<CGraphicalUserInterface *> _pChildren;
public:
    CPanel(IRender *pRender);
    ~CPanel();
    HRESULT AddItem(IGraphicalUserInterface *pItem);
    HRESULT RemoveItem(IGraphicalUserInterface *pItem);
    
    void Draw();
};

class CLabel: public ILabel, public CGraphicalUserInterface
{
    char *_Caption;
public:
    CLabel(IRender *pRender);
    HRESULT SetCaption(char *Caption);
    HRESULT GetCaption(char *&Caption)const;
    
    void Draw();
};

class CButton: public IButton,public CGraphicalUserInterface
{
    GUIAction _pAction;
    char *_Caption;
public:
    CButton(IRender *pRender);
    
    HRESULT InitWithCaptionAndAction(char *Caption, GUIAction pAction);
    HRESULT SetAction(GUIAction pAction);
    HRESULT SetCaption(char *Caption);
    HRESULT GetCaption(char *&Caption)const;
    
    void InvokeAction();
    
    void Draw();
};

class CCheckBox: public ICheckBox, public CGraphicalUserInterface
{
    char *_Caption;
    bool _Checked;
public:
    CCheckBox(IRender *pRender);
    
    HRESULT SetCaption(char *Caption);
    HRESULT GetCaption(char *&Caption)const;
    HRESULT GetCheckState(bool &isChecked)const;
    
    void Check(bool isChecked);
    
    void Draw();
};

class CComboBox: public IComboBox, public CGraphicalUserInterface
{
    vector<char *> _Items;
    int _SelectedItem;
public:
    CComboBox(IRender *pRender);
    
    HRESULT AddItem(char *Caption);
    HRESULT SetCaptionAtIndex(char *Caption, uint Index);
    HRESULT RemoveItem(char *Caption);
    HRESULT GetIndexOfSelectedItem(uint &Index)const;
    HRESULT SelectItemAtIndex(uint Index);
    HRESULT SelectItemWithCaption(char *Caption);
    
    void Draw();
};

#endif
