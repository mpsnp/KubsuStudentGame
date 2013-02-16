#include "Engine.h"
#include "glfw.h"
#include <cmath>

CEngine *TheEngine = NULL;

HRESULT KSU::GetEngine(IEngine *&EngineInterface)
{
    if (!TheEngine) TheEngine = new CEngine();
    EngineInterface = (IEngine *&)TheEngine;
    return H_OK;
}

HRESULT KSU::FreeEngine()
{
    delete TheEngine;
    return H_OK;
}

void GLFWCALL WindowResize( int width, int height );

HRESULT CEngine::InitWindowAndSubsystems(const char* WindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags)
{
    if (!(InitFlags & EIF_NO_LOGGING))
	{
		_LogFile.open("EngineLog.txt", ios::out | ios::trunc);
		_LogFile << "KSU Engine Log File" << endl;
	}
    
    _WindowInit((char *)WindowTitle, InitFlags);
    _OpenGLInit();
    AddToLog("Engine initialized!");
    _MainLoop();
    
    if (_LogFile.is_open())
        _LogFile.close();
    
    return H_OK;
}

HRESULT CEngine::GetSubSystem(const E_ENGINE_SUBSYSTEM_TYPE SubSystemType, IEngineSubsystem *&SubSystem)
{
    switch (SubSystemType) {
        case KSU::ES_INPUT:
            SubSystem = (IEngineSubsystem *&)pInput;
            break;
        case KSU::ES_PHYSICS:
            SubSystem = (IEngineSubsystem *&)pPhysics;
            break;
        case KSU::ES_RENDER:
            SubSystem = (IEngineSubsystem *&)pRender;
            break;
        case KSU::ES_RESOURSE_MANAGER:
            SubSystem = (IEngineSubsystem *&)pResorceManager;
            break;
        case KSU::ES_SOUND:
            SubSystem = (IEngineSubsystem *&)pSound;
            break;
        default:
            AddToLog("No such subsystem!",true);
            break;
    }
    return H_OK;
}

HRESULT CEngine::SetProcessInterval(uint uiProcessPerSecond)
{
    _ProcessInterval = 1.0 / uiProcessPerSecond;
    return H_OK;
}

HRESULT CEngine::StopEngine()
{
    _Running = false;
    return H_OK;
}

HRESULT CEngine::AddToLog(const char *pcTxt, bool bError)
{
    if (_LogFile.is_open())
    {
        double Time = glfwGetTime();
        
        _LogFile << "Time passed:" << Time << " : ";
        if (bError)
            _LogFile << "ERROR : ";
        _LogFile << pcTxt << endl;
    
        if (bError)
            StopEngine();
    }
    return H_OK;
}

HRESULT CEngine::SetGame(IGame *pGame)
{
    pGameInterface = pGame;
    return H_OK;
}

CEngine::CEngine()
{
    _ProcessInterval = 0;
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
    pGameInterface->Render();
	glfwSwapBuffers();
}

void CEngine::_Process()
{
    pGameInterface->Process();
}

void CEngine::_MainLoop()
{    
	_Running = true;
        
    pGameInterface->Init();
    
    if (_ProcessInterval == 0) {
        SetProcessInterval(30);
    }
    
    double dTime = glfwGetTime();
    
	while (_Running)
    {
        if ((glfwGetTime() - dTime) > _ProcessInterval)
        {
            _Process();
            dTime = glfwGetTime();
        }
		_Draw();
	}
    pGameInterface->Free();
    
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

/*
for Collision look at CPhysics class
*/

void CEngine::_WindowInit(char *WindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags)
{
    glfwInit();
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    GLFWvidmode DesktopMode;
    glfwGetDesktopMode(&DesktopMode);
    _Width = DesktopMode.Width;
    _Height = DesktopMode.Height;
	if(!glfwOpenWindow(_Width, _Height,
                       DesktopMode.RedBits,
                       DesktopMode.GreenBits,
                       DesktopMode.BlueBits,
                       8, 8, 0, (InitFlags & EIF_FULLSCREEN)? GLFW_FULLSCREEN : GLFW_WINDOW))
    {
        glfwTerminate();
    }
    glfwSetWindowTitle(WindowTitle);
	glfwSetWindowSizeCallback( WindowResize );
	glfwGetWindowSize( &_Width, &_Height);
    glfwSwapInterval(1);
    _Height = _Height > 0 ? _Height : 1;
}
