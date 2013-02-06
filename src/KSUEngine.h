#ifndef _KSU_ENGINE_H
#define _KSU_ENGINE_H

#include <stddef.h>

typedef long int HRESULT;

#define H_OK    0x00000000
#define H_FALSE 0x00000001
#define H_ERROR 0x80000001

#define KSUCALL

//TODO: Документировать

typedef HRESULT (KSUCALL * KSUUserFunc)(void);

namespace KSU {
    
    enum E_ENGINE_INITIALISATION_FLAGS
    {
        EIF_DEFAULT     = 0x00000000,
        EIF_FULLSCREEN  = 0x00000001,
        EIF_NO_LOGGING  = 0x00000002
    };
    
    enum E_ENGINE_PROCEDURE_TYPE
	{
		EPT_PROCESS = 0,
		EPT_RENDER,
		EPT_INIT,
		EPT_FREE
	};
    
    class IEngine
    {
    public:
        virtual HRESULT KSUCALL InitWindowAndSubsystems(const char* WindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags = EIF_DEFAULT) = 0;
        virtual HRESULT KSUCALL SetProcessInterval(unsigned int uiProcessPerSecond) = 0;
        virtual HRESULT KSUCALL AddFunction(E_ENGINE_PROCEDURE_TYPE eProcType, void (KSUCALL *pProc)(void *pParametr), void *pParametr = NULL) = 0;
		virtual HRESULT KSUCALL RemoveFunction(E_ENGINE_PROCEDURE_TYPE eProcType) = 0;
		virtual HRESULT KSUCALL StopEngine() = 0;
		virtual	HRESULT KSUCALL AddToLog(const char *pcTxt, bool bError = false) = 0;
    };

    extern HRESULT GetEngine(IEngine *&EngineInterface);
    extern HRESULT FreeEngine();
}
#endif //_KSU_ENGINE_H