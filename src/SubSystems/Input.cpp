#include "Input.h"

HRESULT CInput::KeyPressed(const E_KEYBOARD_KEY_CODES KeyKode)const
{
    return H_OK;
}

HRESULT CInput::GetMouseState(TMouseState &MouseState)const
{
    return H_OK;
}

HRESULT CInput::BeginTextInput(char *pBuffer, uint BufferSize)
{
    IsTextInputStarted = true;
    return H_OK;
}

HRESULT CInput::EndTextInput()
{
    IsTextInputStarted = false;
    return H_OK;
}

HRESULT CInput::GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem)
{
    EngineSubSystem = ES_INPUT;
    return H_OK;
}