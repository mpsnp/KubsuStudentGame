#include "Input.h"
#include "../glfw.h"

HRESULT CInput::KeyPressed(const E_KEYBOARD_KEY_CODES KeyKode)const
{
	if (KeyKode >= KEY_0 && KeyKode <= KEY_9)
	{
		return (glfwGetKey('0' + KeyKode - KEY_0) == GLFW_PRESS)? H_OK : H_FALSE;
	}
	if(KeyKode >= KEY_A && KeyKode <= KEY_Z)
	{
		return (glfwGetKey('A' + KeyKode - KEY_A) == GLFW_PRESS)? H_OK : H_FALSE;
	}
	if(KeyKode >= KEY_F1 && KeyKode <= KEY_F12)
	{
		return (glfwGetKey(GLFW_KEY_F1 + KeyKode - KEY_F1) == GLFW_PRESS)? H_OK : H_FALSE;
	}

	if (KeyKode==KEY_LCONTROL)
		return (glfwGetKey(GLFW_KEY_LCTRL) == GLFW_PRESS)? H_OK : H_FALSE; 

	/*switch (KeyKode)
	{
	case KEY_LSHIFT: return (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS)? H_OK : H_FALSE; 
	default:
		break;
	}*/
    return H_FALSE;
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