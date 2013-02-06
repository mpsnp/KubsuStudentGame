#ifndef _KSU_ENGINE_H
#define _KSU_ENGINE_H

#include <stddef.h>

typedef long int HRESULT;

#define H_OK    0x00000000
#define H_FALSE 0x00000001
#define H_ERROR 0x80000001

//TODO: Документировать

typedef HRESULT (* KSUUserFunc)(void);

namespace KSU {
    
    /*
     * Common typedefs
     */
    
    //signed//
	typedef short int			int16;
	typedef long int			int32;
	typedef signed char			int8;
	typedef wchar_t				wchar;
    
	//unsigned//
	typedef unsigned int		uint;
	typedef unsigned short int	uint16;
	typedef unsigned long int	uint32;
	typedef unsigned char		uint8;
	typedef uint8				uchar;
    
    /*
     * Enums
     */
    
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
    
    enum E_KEYBOARD_KEY_CODES
	{
		KEY_ESCAPE			= 0x01,
		KEY_TAB				= 0x0F,
		KEY_GRAVE			= 0x29,
		KEY_CAPSLOCK		= 0x3A,
		KEY_BACKSPACE		= 0x0E,
		KEY_RETURN			= 0x1C,
		KEY_SPACE			= 0x39,
		KEY_SLASH			= 0x35,
		KEY_BACKSLASH		= 0x2B,
        
		KEY_SYSRQ			= 0xB7,
		KEY_SCROLL			= 0x46,
		KEY_PAUSE			= 0xC5,
        
		KEY_INSERT			= 0xD2,
		KEY_DELETE			= 0xD3,
		KEY_HOME			= 0xC7,
		KEY_END				= 0xCF,
		KEY_PGUP			= 0xC9,
		KEY_PGDN			= 0xD1,
        
		KEY_LSHIFT			= 0x2A,
		KEY_RSHIFT			= 0x36,
		KEY_LALT			= 0x38,
		KEY_RALT			= 0xB8,
		KEY_LWIN_OR_CMD		= 0xDB,
		KEY_RWIN_OR_CMD		= 0xDC,
		KEY_LCONTROL		= 0x1D,
		KEY_RCONTROL		= 0x9D,
        
		KEY_UP				= 0xC8,
		KEY_RIGHT			= 0xCD,
		KEY_LEFT			= 0xCB,
		KEY_DOWN			= 0xD0,
        
		KEY_1				= 0x02,
		KEY_2				= 0x03,
		KEY_3				= 0x04,
		KEY_4				= 0x05,
		KEY_5				= 0x06,
		KEY_6				= 0x07,
		KEY_7				= 0x08,
		KEY_8				= 0x09,
		KEY_9				= 0x0A,
		KEY_0				= 0x0B,
        
		KEY_F1				= 0x3B,
		KEY_F2				= 0x3C,
		KEY_F3				= 0x3D,
		KEY_F4				= 0x3E,
		KEY_F5				= 0x3F,
		KEY_F6				= 0x40,
		KEY_F7				= 0x41,
		KEY_F8				= 0x42,
		KEY_F9				= 0x43,
		KEY_F10				= 0x44,
		KEY_F11				= 0x57,
		KEY_F12				= 0x58,
        
		KEY_Q				= 0x10,
		KEY_W				= 0x11,
		KEY_E				= 0x12,
		KEY_R				= 0x13,
		KEY_T				= 0x14,
		KEY_Y				= 0x15,
		KEY_U				= 0x16,
		KEY_I				= 0x17,
		KEY_O				= 0x18,
		KEY_P				= 0x19,
		KEY_A				= 0x1E,
		KEY_S				= 0x1F,
		KEY_D				= 0x20,
		KEY_F				= 0x21,
		KEY_G				= 0x22,
		KEY_H				= 0x23,
		KEY_J				= 0x24,
		KEY_K				= 0x25,
		KEY_L				= 0x26,
		KEY_Z				= 0x2C,
		KEY_X				= 0x2D,
		KEY_C				= 0x2E,
		KEY_V				= 0x2F,
		KEY_B				= 0x30,
		KEY_N				= 0x31,
		KEY_M				= 0x32,
        
		KEY_MINUS			= 0x0C,
		KEY_PLUS			= 0x0D,
		KEY_LBRACKET		= 0x1A,
		KEY_RBRACKET		= 0x1B,
        
		KEY_SEMICOLON		= 0x27,
		KEY_APOSTROPHE		= 0x28,
        
		KEY_COMMA			= 0x33,
		KEY_PERIOD			= 0x34,
        
		KEY_NUMPAD0			= 0x52,
		KEY_NUMPAD1			= 0x4F,
		KEY_NUMPAD2			= 0x50,
		KEY_NUMPAD3			= 0x51,
		KEY_NUMPAD4			= 0x4B,
		KEY_NUMPAD5			= 0x4C,
		KEY_NUMPAD6			= 0x4D,
		KEY_NUMPAD7			= 0x47,
		KEY_NUMPAD8			= 0x48,
		KEY_NUMPAD9			= 0x49,
		KEY_NUMPADPERIOD	= 0x53,
		KEY_NUMPADENTER		= 0x9C,
		KEY_NUMPADSTAR		= 0x37,
		KEY_NUMPADPLUS		= 0x4E,
		KEY_NUMPADMINUS		= 0x4A,
		KEY_NUMPADSLASH		= 0xB5,
		KEY_NUMLOCK			= 0x45,
    };
    
    enum E_ENGINE_SUBSYSTEM
    {
        ES_INPUT = 0,
        ES_PHYSICS,
        ES_RENDER,
        ES_RESOURSE_MANAGER,
        ES_SOUND
    };
    
    /*
     * Structs
     */
    
    struct TMouseState
    {
        int x,y;
        int dx,dy;
        int dWheeel;
        bool LeftButtonPressed;
        bool MiddleButtonPressed;
        bool RightButtonPressed;
    };
    
    /*
     * Main engine systems
     */
    
    class IEngineBase
    {
    public:
    };
    
    class IEngineSubsystem: public IEngineBase
    {
    public:
        virtual HRESULT GetType(E_ENGINE_SUBSYSTEM &EngineSubSystem);
    };
    
    class IEngine: public IEngineBase
    {
    public:
        virtual HRESULT InitWindowAndSubsystems(const char* pWindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags = EIF_DEFAULT) = 0;
        virtual HRESULT SetProcessInterval(uint ProcessPerSecond) = 0;
        virtual HRESULT AddFunction(E_ENGINE_PROCEDURE_TYPE ProcType, void (*pProc)(void *pParametr), void *pParametr = NULL) = 0;
		virtual HRESULT RemoveFunction(E_ENGINE_PROCEDURE_TYPE ProcType) = 0;
		virtual HRESULT StopEngine() = 0;
		virtual	HRESULT AddToLog(const char *pText, bool Error = false) = 0;
    };
    
    class IInput: public IEngineSubsystem
    {
    public:
        virtual HRESULT KeyPressed(E_KEYBOARD_KEY_CODES KeyKode)const = 0;
        virtual HRESULT GetMouseState(TMouseState &MouseState)const = 0;
        virtual HRESULT BeginTextInput(char *pBuffer, uint BufferSize) = 0;
        virtual HRESULT EndTextInput() = 0;
    };
    
    class IRender: public IEngineSubsystem
    {
    public:
    };
    
    class IRender2d: public IRender
    {
    public:
    };
    
    class IRender3d: public IRender
    {
    public:
    };
    
    class IResourceManager: public IEngineSubsystem
    {
    public:
        virtual HRESULT LoadResource(char *pFileName) = 0;
    };
    
    class IPhysics: public IEngineSubsystem
    {
    public:
    };
    
    class ISound: public IEngineSubsystem
    {
    public:
    };
    
    /*
     * Интерфейсы ресурсов
     */
    
    class IResource: public IEngineBase
    {
    public:
    };
    
    class IModel: public IResource
    {
    public:
    };
    
    class ICamera: public IResource
    {
    public:
    };
    
    class ITexture: public IResource
    {
    public:
    };
    
    class ISoundSample: public IResource
    {
    public:
    };
    
    class IPhysicsObject: public IResource
    {
    public:
    };
    
    class ICollidable: public IPhysicsObject
    {
    public:
        
    };
    
    class IShape: public IPhysicsObject
    {
    public:
    };
    
    /*
     * Интерфейсы графического интерфейса))
     */
    
    class IGraphicalUserInterface: public IEngineBase
    {
    public:
    };
    
    class IPanel: public IGraphicalUserInterface
    {
    public:
    };
    
    class IButton: public IGraphicalUserInterface
    {
    public:
    };
    
    class ILabel: public IGraphicalUserInterface
    {
    public:
    };
    
    class ICheckBox: public IGraphicalUserInterface
    {
    public:
    };
    
    class IComboBox: public IGraphicalUserInterface
    {
    public:
    };

    extern HRESULT GetEngine(IEngine *&EngineInterface);
    extern HRESULT FreeEngine();
}
#endif //_KSU_ENGINE_H