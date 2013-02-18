#include "Input.h"
#include "../glfw.h"

HRESULT CInput::KeyPressed(const E_KEYBOARD_KEY_CODES KeyKode)const
{
	if (KeyKode >= KEY_0 && KeyKode <= KEY_9)
	{
		return (glfwGetKey('0' + KeyKode - KEY_0) == GLFW_PRESS)? H_OK : H_FALSE;
	}
    
	if (KeyKode >= KEY_A && KeyKode <= KEY_Z)
	{
		return (glfwGetKey('A' + KeyKode - KEY_A) == GLFW_PRESS)? H_OK : H_FALSE;
	}
       
	if (KeyKode >= KEY_F1 && KeyKode <= KEY_F12)
	{
		return (glfwGetKey(GLFW_KEY_F1 + KeyKode - KEY_F1) == GLFW_PRESS)? H_OK : H_FALSE;
	}

	switch (KeyKode)
	{
		case KEY_LSHIFT:    return (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS)? H_OK : H_FALSE; break;
		case KEY_LCONTROL:  return (glfwGetKey(GLFW_KEY_LCTRL) == GLFW_PRESS)? H_OK : H_FALSE; break;
		case KEY_RSHIFT:	return (glfwGetKey(GLFW_KEY_RSHIFT) == GLFW_PRESS)? H_OK : H_FALSE; break;
		case KEY_LALT:		return (glfwGetKey(GLFW_KEY_LALT) == GLFW_PRESS)? H_OK : H_FALSE; break;
		case KEY_LWIN_OR_CMD:	return (glfwGetKey(GLFW_KEY_LSUPER) == GLFW_PRESS)? H_OK : H_FALSE; break;
		case KEY_RWIN_OR_CMD:	return (glfwGetKey(GLFW_KEY_RSUPER) == GLFW_PRESS)? H_OK : H_FALSE; break;
		case KEY_RCONTROL:	return (glfwGetKey(GLFW_KEY_RCTRL) == GLFW_PRESS)? H_OK : H_FALSE; break;

		case KEY_ESCAPE:    return (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)? H_OK : H_FALSE; break;
		case KEY_TAB:		return (glfwGetKey(GLFW_KEY_TAB) == GLFW_PRESS)? H_OK : H_FALSE; break;		
		case KEY_GRAVE:		return H_FALSE; break; //TODO:не нашли в glwf необработываеться
		case KEY_CAPSLOCK:	return (glfwGetKey(GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)? H_OK : H_FALSE; break;	
		case KEY_BACKSPACE:	return (glfwGetKey(GLFW_KEY_BACKSPACE) == GLFW_PRESS)? H_OK : H_FALSE; break;		
		case KEY_RETURN:	return (glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)? H_OK : H_FALSE; break;	
		case KEY_SPACE:		return (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS)? H_OK : H_FALSE; break;			
		case KEY_SLASH:		return (glfwGetKey(GLFW_KEY_KP_DIVIDE) == GLFW_PRESS)? H_OK : H_FALSE; break;		
		case KEY_BACKSLASH:	return H_FALSE; break; //TODO:не нашли в glwf необработываеться

		case KEY_SYSRQ:		return H_FALSE; break; //TODO:не нашли в glwf необработываеться				
		case KEY_SCROLL:	return (glfwGetKey(GLFW_KEY_SCROLL_LOCK) == GLFW_PRESS)? H_OK : H_FALSE; break;			
		case KEY_PAUSE:		return (glfwGetKey(GLFW_KEY_PAUSE) == GLFW_PRESS)? H_OK : H_FALSE; break;	
		case KEY_INSERT:	return (glfwGetKey(GLFW_KEY_INSERT) == GLFW_PRESS)? H_OK : H_FALSE; break;			
		case KEY_DELETE:	return (glfwGetKey(GLFW_KEY_DEL) == GLFW_PRESS)? H_OK : H_FALSE; break;		
		case KEY_HOME:		return (glfwGetKey(GLFW_KEY_HOME) == GLFW_PRESS)? H_OK : H_FALSE; break;		
		case KEY_END:		return (glfwGetKey(GLFW_KEY_END) == GLFW_PRESS)? H_OK : H_FALSE; break;			
		case KEY_PGUP:		return (glfwGetKey(GLFW_KEY_PAGEUP) == GLFW_PRESS)? H_OK : H_FALSE; break;		
		case KEY_PGDN:		return (glfwGetKey(GLFW_KEY_PAGEDOWN) == GLFW_PRESS)? H_OK : H_FALSE; break;		

		case KEY_UP:		return (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)? H_OK : H_FALSE; break;		
		case KEY_RIGHT:		return (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)? H_OK : H_FALSE; break;	
		case KEY_LEFT:		return (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)? H_OK : H_FALSE; break;	
		case KEY_DOWN:		return (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)? H_OK : H_FALSE; break;	

		case KEY_MINUS:		return (glfwGetKey(GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)? H_OK : H_FALSE; break;	
		case KEY_PLUS:		return (glfwGetKey(GLFW_KEY_KP_ADD) == GLFW_PRESS)? H_OK : H_FALSE; break;	
		case KEY_LBRACKET:	return H_FALSE; break;	
		case KEY_RBRACKET:	return H_FALSE; break;		
		case KEY_SEMICOLON:	return H_FALSE; break;		
		case KEY_APOSTROPHE:return H_FALSE; break;			
		case KEY_COMMA:		return H_FALSE; break;		
		case KEY_PERIOD:	return H_FALSE; break;			
            
		//TODO:необработываем мелкую клаву

	default:
		break;
	}
    return H_FALSE;
}

HRESULT CInput::GetMouseState(TMouseState &MouseState)const
{
	if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
		MouseState.LeftButtonPressed=true;
	else
		MouseState.LeftButtonPressed=false;

	if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS)
		MouseState.RightButtonPressed=true;
	else
		MouseState.RightButtonPressed=false;

	if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE)==GLFW_PRESS)
		MouseState.MiddleButtonPressed=true;
	else
		MouseState.MiddleButtonPressed=false;

	glfwGetMousePos(&MouseState.x,&MouseState.y);
	MouseState.dWheeel=glfwGetMouseWheel();

	GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)MouseState.x;
   // winY = (float)viewport[3] - (float)y;
	winY = (float)MouseState.y;
    glReadPixels( MouseState.x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &MouseState.WorldX, &MouseState.WorldY, &MouseState.WorldZ);
	//TODO:проверить правильность работы worldx and etc
	 
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