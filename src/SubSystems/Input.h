#ifndef _INPUT_H
#define _INPUT_H

#include "../CommonIncludes.h"

class CInput: public IInput
{
    bool        IsTextInputStarted;
    char        *pTextBuffer;
public:
    HRESULT KeyPressed(const E_KEYBOARD_KEY_CODES KeyKode)const;
    HRESULT GetMouseState(TMouseState &MouseState)const;
    HRESULT BeginTextInput(char *pBuffer, uint BufferSize);
    HRESULT EndTextInput();
    HRESULT GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem);
};

#endif //_INPUT_H
