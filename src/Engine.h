#ifndef _ENGINE_H
#define _ENGINE_H

#include "CommonIncludes.h"
#include "FuncDelegate.h"

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

public:
	CEngine();
	~CEngine();
    
    HRESULT InitWindowAndSubsystems(const char* WindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags = EIF_DEFAULT);
    HRESULT SetProcessInterval(uint uiProcessPerSecond);
    HRESULT AddFunction(E_ENGINE_PROCEDURE_TYPE eProcType, void (*pProc)(void *pParametr), void *pParametr = NULL);
    HRESULT RemoveFunction(E_ENGINE_PROCEDURE_TYPE eProcType);
    HRESULT StopEngine();
    HRESULT AddToLog(const char *pcTxt, bool bError = false);
    
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
