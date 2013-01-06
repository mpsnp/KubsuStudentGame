#include "Engine.h"
#include "glfw.h"

void GLFWCALL WindowResize( int width, int height );

CEngine::CEngine(string Title)
	:_Width(800), _Height(600), _c_WindowTitle(Title.c_str())
{
    _WindowInit();
	_OpenGLInit();
	SetProcessPerSecond(75);
	_Map = CModel3d();
	_Map.LoadFrom3ds("models/Flyer.3ds");
}

CEngine::~CEngine()
{

}

void CEngine::_OpenGLInit()
{
	glViewport( 0, 0, _Width, _Height );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    gluPerspective( 65.0f, (GLfloat)_Width/(GLfloat)_Height, 1.0f, 100.0f );
    glMatrixMode( GL_MODELVIEW );

	GLfloat AmbientLight[4] = {0.5, 0.5, 0.5, 1.0};
	GLfloat DiffuseLight[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat SpecularLight[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat LightPosition[4] = {0.0, 1.0 ,0.0 ,2.0};
	GLfloat SpecularReflection[4] = {0.4, 0.4, 0.4, 1.0};

	glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_AMBIENT, (const GLfloat*)&AmbientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, (const GLfloat*)&DiffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR, (const GLfloat*)&SpecularLight);

	glLightfv(GL_LIGHT0,GL_POSITION,(const GLfloat*)&LightPosition);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, (const GLfloat*)&SpecularReflection);
	glMateriali(GL_FRONT,GL_SHININESS,100);
}

void CEngine::_Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	// =========== Only for testing ==============
	glTranslatef(0,0,-3);
	glRotatef(_Frame,0,1,1);
	// =========== Only for testing ==============
	_Map.Draw();
	for(int i = 0;i < _Vehicles.size();i++) _Vehicles[i].Draw();
	glfwSwapBuffers();
}

void CEngine::_Process()
{
	_Frame+=0.2; // =========== Only for testing ==============
	_Running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

void CEngine::SetProcessPerSecond(int Times)
{
	_ProcessPerSecond = 1.0/Times;
}

void CEngine::MainLoop()
{
	_Frame = 0;// =========== Only for testing ==============
	_Running = true;
	double dTime = glfwGetTime();
	while (_Running){
		_Draw();
		if (glfwGetTime() - dTime >= _ProcessPerSecond){
			_Process();
			dTime = glfwGetTime();
		}
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
