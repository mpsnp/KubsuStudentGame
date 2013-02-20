#include "GUI.h"

CGraphicalUserInterface::CGraphicalUserInterface(IRender *pRender)
{
    _pRender = pRender;
    _pRender->GetRender2d(_pRender2d);
}

CGraphicalUserInterface::~CGraphicalUserInterface()
{
}

HRESULT CGraphicalUserInterface::SetPosition(TVector2d Position)
{
    _Position = Position;
    return H_OK;
}

HRESULT CGraphicalUserInterface::GetPosition(TVector2d &Position)
{
    Position = _Position;
    return H_OK;
}

HRESULT CGraphicalUserInterface::SetSize(TVector2d Size)
{
    _Size = Size;
    return H_OK;
}

HRESULT CGraphicalUserInterface::GetSize(TVector2d &Size)
{
    Size = _Size;
    return H_OK;
}

HRESULT CGraphicalUserInterface::SetColor(TColor Color)
{
    _Color = Color;
    return H_OK;
}

HRESULT CGraphicalUserInterface::GetColor(TColor &Color)
{
    Color = _Color;
    return H_OK;
}

HRESULT CGraphicalUserInterface::SetTexture(ITexture *pTexture)
{
    _pTexture = pTexture;
    return H_OK;
}

CPanel::CPanel(IRender *pRender)
    :CGraphicalUserInterface(pRender)
{
    
}

CPanel::~CPanel()
{
}

HRESULT CPanel::AddItem(IGraphicalUserInterface *pItem)
{
    _pChildren.push_back((CGraphicalUserInterface *)(void*)pItem);
    return H_OK;
}

HRESULT CPanel::RemoveItem(IGraphicalUserInterface *pItem)
{
    std::vector<CGraphicalUserInterface *>::iterator it;
    it = find(_pChildren.begin(), _pChildren.end(), pItem);
    
    
    if (*it == pItem)
        _pChildren.erase(it);
    else
        return H_FALSE;
    
    return H_OK;
}

void CPanel::Draw()
{
    _pRender2d->DrawRectangle(_Position, _Position + _Size, _pTexture);
    for (int i = 0; i < _pChildren.size(); i++) {
        _pChildren.at(i)->Draw();
    }
}

//============LABEL=====================

CLabel::CLabel(IRender *pRender)
:CGraphicalUserInterface(pRender)
{
    
}

HRESULT CLabel::SetCaption(char *Caption)
{
    _Caption = Caption;
    return H_OK;
}

HRESULT CLabel::GetCaption(char *&Caption)const
{
    Caption = Caption;
    return H_OK;
}

void CLabel::Draw()
{
    //TODO: Доделать
}

//============BUTTON=====================

CButton::CButton(IRender *pRender)
:CGraphicalUserInterface(pRender)
{
    
}

HRESULT CButton::InitWithCaptionAndAction(char *Caption, GUIAction pAction)
{
    _Caption = Caption;
    _pAction = pAction;
    return H_OK;
}

HRESULT CButton::SetAction(GUIAction pAction)
{
    _pAction = pAction;
    return H_OK;
}

HRESULT CButton::SetCaption(char *Caption)
{
    _Caption = Caption;
    return H_OK;
}

HRESULT CButton::GetCaption(char *&Caption)const
{
    Caption = _Caption;
    return H_OK;
}

void CButton::InvokeAction()
{
    _pAction((IGraphicalUserInterface *)(IButton *)this);
}

void CButton::Draw()
{
    //TODO: Доделать    
}

//===============CHECK==BOX================

CCheckBox::CCheckBox(IRender *pRender)
:CGraphicalUserInterface(pRender)
{
    
}

HRESULT CCheckBox::SetCaption(char *Caption)
{
    _Caption = Caption;
    return H_OK;
}

HRESULT CCheckBox::GetCaption(char *&Caption)const
{
    Caption = _Caption;
    return H_OK;
}

HRESULT CCheckBox::GetCheckState(bool &isChecked)const
{
    isChecked = _Checked;
    return H_OK;
}

void CCheckBox::Check(bool isChecked)
{
    _Checked = isChecked;
}

void CCheckBox::Draw()
{
    //TODO: Доделать    
}

//=============COMBO==BOX================

CComboBox::CComboBox(IRender *pRender)
:CGraphicalUserInterface(pRender)
{
    
}

HRESULT CComboBox::AddItem(char *Caption)
{
    _Items.push_back(Caption);
    return H_OK;
}

HRESULT CComboBox::SetCaptionAtIndex(char *Caption, uint Index)
{
    if (Index < _Items.size())
        _Items[Index] = Caption;
    else
        return H_FALSE;
    return H_OK;
}

HRESULT CComboBox::RemoveItem(char *Caption)
{
    std::vector<char *>::iterator it;
    it = find(_Items.begin(), _Items.end(), Caption);
    
    _Items.erase(it);
    
    return H_OK;
}

HRESULT CComboBox::GetIndexOfSelectedItem(uint &Index)const
{
    Index = _SelectedItem;
    return H_OK;
}

HRESULT CComboBox::SelectItemAtIndex(uint Index)
{
    _SelectedItem = Index;
    return H_OK;
}

HRESULT CComboBox::SelectItemWithCaption(char *Caption)
{
    for (int i = 0; i<_Items.size(); i++)
        if (strcmp(_Items[i], Caption) == 0)
        {
            _SelectedItem = i;
            return H_OK;
        }
        
    return H_FALSE;
}

void CComboBox::Draw()
{
     //TODO: Доделать    
}
