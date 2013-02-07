#ifndef _ENGINE_H
#define _ENGINE_H

#include "CommonIncludes.h"
#include "FuncDelegate.h"

class CInput;
class CPhysics;
class CRender;
class CResourceManager;
class CSound;

/*
 * Класс движка. 
 */
class CEngine: public KSU::IEngine
{
private:
	int _Width, _Height;
	bool _Running;
	double _ProcessInterval;
    
    TUserFunction   _UserProcess;
    TUserFunction   _UserRender;
    TUserFunction   _UserInit;
    TUserFunction   _UserFree;
    
	fstream         _LogFile;
    
    CInput          *pInput;
    CPhysics        *pPhysics;
    CRender         *pRender;
    CResourceManager*pResorceManager;
    CSound          *pSound;

public:
	CEngine();
	~CEngine();
    
    HRESULT InitWindowAndSubsystems(const char* pWindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags = EIF_DEFAULT);
    HRESULT SetProcessInterval(uint ProcessPerSecond);
    HRESULT AddFunction(const E_ENGINE_PROCEDURE_TYPE ProcType, void (*pProc)(void *pParametr), void *pParametr = NULL);
    HRESULT RemoveFunction(const E_ENGINE_PROCEDURE_TYPE ProcType);
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
