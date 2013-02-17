#ifndef _ENGINE_H
#define _ENGINE_H

#include "CommonIncludes.h"

class CInput;
class CPhysics;
class CRender;
class CResourceManager;
class CSound;

/*
 * Класс движка. 
 */
class CEngine: public IEngine
{
private:
	int _Width, _Height;
	bool _Running;
	double _ProcessInterval;
    
	fstream         _LogFile;
    
    CInput          *pInput;
    CPhysics        *pPhysics;
    CRender         *pRender;
    CResourceManager*pResorceManager;
    CSound          *pSound;
    
    IGame           *pGameInterface;

public:
	CEngine();
	~CEngine();
    
    HRESULT InitWindowAndSubsystems(const char* pWindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags = EIF_DEFAULT);
    HRESULT SetProcessInterval(uint ProcessPerSecond);
    double GetProcessInterval();
    HRESULT SetGame(IGame *pGame);
    HRESULT StopEngine();
    HRESULT AddToLog(const char *pText, bool Error = false);
    HRESULT GetSubSystem(const E_ENGINE_SUBSYSTEM_TYPE SubSystemType, IEngineSubsystem *&SubSystem);
    
private:
    
    /*
     * Основной цикл программы. Запускает
     * _Process() & _Draw();
     */
	void _MainLoop();
        
    /*
     * Реализует логику игры. (Как-то передвижение объектов, камеры и т.п.)
     */
	void _Process();
    
    /*
     * Реализует рендер.
     */
	void _Draw();
    
    /*
     * Реализует весь код инициализации окна.
     * Вызывается 1 раз в конструкторе движка.
     */
	void _WindowInit(char *WindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags);
    
    /*
     * Реализует весь код инициализации OpenGL.
     * Вызывается 1 раз в конструкторе движка.
     */
	void _OpenGLInit();
};

#endif //_ENGINE_H
