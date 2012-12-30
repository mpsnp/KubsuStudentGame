#include "Engine.h"
#include "glfw.h"

void GLFWCALL WindowResize( int width, int height );

CEngine::CEngine(string Title)
	:_Width(800), _Height(600), _c_WindowTitle(Title.c_str())
{
    _WindowInit();
    glViewport( 0, 0, _Width, _Height );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 65.0f, (GLfloat)_Width/(GLfloat)_Height, 1.0f, 100.0f );
    glMatrixMode( GL_MODELVIEW );
	_Map = CModel3d();
	_Map.LoadFrom3ds("models/Flyer.3ds");
}

CEngine::~CEngine()
{

}

void CEngine::_Draw()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
	// =========== Тестовый костыль ==============
	glTranslatef(0,0,-3);
	glRotatef(_Frame,0,0,1);
	// =========== Тестовый костыль ==============
	_Map.Draw();
	glfwSwapBuffers();
}

void CEngine::_Process()
{
	_Frame+=0.2; // =========== Тестовый костыль ==============
	_Running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

void CEngine::MainLoop()
{
	_Frame = 0;// =========== Тестовый костыль ==============
	_Running = true;
	while (_Running){
		_Draw();
		_Process();
		glfwSleep(0.0001);
	}
	glfwTerminate();
}

void GLFWCALL WindowResize( int width, int height )
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f);
    glMatrixMode( GL_MODELVIEW );
}

void CEngine::_Collision()
{
	for (int i = 0; i < _Vehicles.size(); i++)
	{
		// Collision detection between vehicles
		for (int j = 0; j < _Vehicles.size(); j++)
		{
			TVector3d distance = _Vehicles[i].GetPosition() - _Vehicles[j].GetPosition();
			float min_distance = _Vehicles[i].GetRadius() + _Vehicles[j].GetRadius();
			if (distance.LengthSquared() <= min_distance * min_distance)
			{
				/* Collision detected!
				** TODO: reduce vehicles life
				** FIXED: compute new velocity vector
				*/
				// p = mv;  Ek = mv^2/2
				TVector3d v1 = _Vehicles[i].GetVelocity();
				int		  m1 = _Vehicles[i].GetWeight();
				TVector3d v2 = _Vehicles[j].GetVelocity();
				int		  m2 = _Vehicles[j].GetWeight();

				_Vehicles[i].SetVelocity((v1 * (m1 - m2) + v2 * m2 * 2) * (1/(m1 + m2)));
				_Vehicles[j].SetVelocity((v2 * (m2 - m1) + v1 * m1 * 2) * (1/(m1 + m2)));
			}
		}
		/*
		** TODO: Collision detection beween vehicle and other static objects e.g. walls
		** TODO: Make sure you use square instead of square root everywhere where it possible
		*/
	}
}

void CEngine::_WindowInit()
{
    glfwInit();
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	if( !glfwOpenWindow( _Width,_Height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
    }
    glfwSetWindowTitle(_c_WindowTitle);
	glfwSetWindowSizeCallback( WindowResize );
	glfwGetWindowSize( &_Width, &_Height);
    _Height = _Height > 0 ? _Height : 1;
}
