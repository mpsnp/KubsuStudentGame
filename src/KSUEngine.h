#ifndef _KSU_ENGINE_H
#define _KSU_ENGINE_H

#include <stddef.h>
#include "CommonStructs.h"

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
    
    enum E_RESOURCE_TYPE
    {
        RT_CAMERA = 0,
        RT_MODEL,
        RT_COLLIDABLE,
        RT_SHAPE,
        RT_SOUND_SAMPLE,
        RT_TEXTURE
    };
    
    enum E_SHAPE_TYPE
    {
		ST_CIRCLE = 0,
		ST_LINE
	};
	
	enum E_PHYSICS_OBJECT_TYPE
	{
		POT_COLLIDABLE = 0,
		POT_SHAPE
	};
    
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
		KEY_TAB				= 0x02,
		KEY_GRAVE			= 0x03,
		KEY_CAPSLOCK		= 0x04,
		KEY_BACKSPACE		= 0x05,
		KEY_RETURN			= 0x06,
		KEY_SPACE			= 0x07,
		KEY_SLASH			= 0x08,
		KEY_BACKSLASH		= 0x09,
        
		KEY_SYSRQ			= 0x0A,
		KEY_SCROLL			= 0x0B,
		KEY_PAUSE			= 0x0C,
        
		KEY_INSERT			= 0x0D,
		KEY_DELETE			= 0x0E,
		KEY_HOME			= 0x0F,
		KEY_END				= 0x10,
		KEY_PGUP			= 0x11,
		KEY_PGDN			= 0x12,
        
		KEY_LSHIFT			= 0x13,
		KEY_RSHIFT			= 0x14,
		KEY_LALT			= 0x15,
		KEY_RALT			= 0x16,
		KEY_LWIN_OR_CMD		= 0x17,
		KEY_RWIN_OR_CMD		= 0x18,
		KEY_LCONTROL		= 0x19,
		KEY_RCONTROL		= 0x1A,
        
		KEY_UP				= 0x1B,
		KEY_RIGHT			= 0x1C,
		KEY_LEFT			= 0x1D,
		KEY_DOWN			= 0x1E,
        
		KEY_0				= 0x1F,
		KEY_1				= 0x20,
		KEY_2				= 0x21,
		KEY_3				= 0x22,
		KEY_4				= 0x23,
		KEY_5				= 0x24,
		KEY_6				= 0x25,
		KEY_7				= 0x26,
		KEY_8				= 0x27,
		KEY_9				= 0x28,
        
		KEY_F1				= 0x29,
		KEY_F2				= 0x2A,
		KEY_F3				= 0x2B,
		KEY_F4				= 0x2C,
		KEY_F5				= 0x2D,
		KEY_F6				= 0x2E,
		KEY_F7				= 0x2F,
		KEY_F8				= 0x30,
		KEY_F9				= 0x31,
		KEY_F10				= 0x32,
		KEY_F11				= 0x33,
		KEY_F12				= 0x34,
        
		KEY_A				= 0x35,
		KEY_B				= 0x36,
		KEY_C				= 0x37,
		KEY_D				= 0x38,
		KEY_E				= 0x39,
		KEY_F				= 0x3A,
		KEY_G				= 0x3B,
		KEY_H				= 0x3C,
		KEY_I				= 0x3D,
		KEY_J				= 0x3E,
		KEY_K				= 0x3F,
		KEY_L				= 0x40,
		KEY_M				= 0x41,
		KEY_N				= 0x42,
		KEY_O				= 0x43,
		KEY_P				= 0x44,
		KEY_Q				= 0x45,
		KEY_R				= 0x46,
		KEY_S				= 0x47,
		KEY_T				= 0x48,
		KEY_U				= 0x49,
		KEY_V				= 0x4A,
		KEY_W				= 0x4B,
		KEY_X				= 0x4C,
		KEY_Y				= 0x4D,
		KEY_Z				= 0x4E,
        
		KEY_MINUS			= 0x4F,
		KEY_PLUS			= 0x50,
		KEY_LBRACKET		= 0x51,
		KEY_RBRACKET		= 0x52,
        
		KEY_SEMICOLON		= 0x53,
		KEY_APOSTROPHE		= 0x54,
        
		KEY_COMMA			= 0x55,
		KEY_PERIOD			= 0x56,
        
		KEY_NUMPAD0			= 0x57,
		KEY_NUMPAD1			= 0x58,
		KEY_NUMPAD2			= 0x59,
		KEY_NUMPAD3			= 0x5A,
		KEY_NUMPAD4			= 0x5B,
		KEY_NUMPAD5			= 0x5C,
		KEY_NUMPAD6			= 0x5D,
		KEY_NUMPAD7			= 0x5E,
		KEY_NUMPAD8			= 0x5F,
		KEY_NUMPAD9			= 0x60,
		KEY_NUMPADPERIOD	= 0x61,
		KEY_NUMPADENTER		= 0x62,
		KEY_NUMPADSTAR		= 0x63,
		KEY_NUMPADPLUS		= 0x64,
		KEY_NUMPADMINUS		= 0x65,
		KEY_NUMPADSLASH		= 0x66,
		KEY_NUMLOCK			= 0x67
    };
    
    enum E_ENGINE_SUBSYSTEM_TYPE
    {
        ES_INPUT = 0,
        ES_PHYSICS,
        ES_RENDER,
        ES_RESOURSE_MANAGER,
        ES_SOUND
    };
    
    enum E_PROJECTION_TYPE
    {
        PT_2D = 0,
        PT_3D
    };
    
    /*
     * Structs
     */
    
    struct TMouseState
    {
        int x,y;//сейчас
        int dx,dy;//отношение между прошлый и следующим
		double WorldX,WorldY,WorldZ;//мировые значения
        int dWheeel;//колесо
        bool LeftButtonPressed;
        bool MiddleButtonPressed;
        bool RightButtonPressed;
    };
    
    class IGame
    {
    public:
        virtual void Init() = 0;
        virtual void Process() = 0;
        virtual void Render() = 0;
        virtual void Free() = 0;
    };
    
    class IEngineBase
    {
    public:
    };
    
    /*
     * Интерфейсы ресурсов
     */
    
    class IResource: public IEngineBase
    {
    public:
        virtual HRESULT GetData(char *&pData)const = 0;
        virtual HRESULT SetData(const char *pData) = 0;
        virtual HRESULT GetType(E_RESOURCE_TYPE &Type) = 0;
    };
    
    class IMesh: public IResource
    {
    public:
        virtual HRESULT Draw() = 0;
        virtual HRESULT Draw(TVector3d Position) = 0;
        virtual HRESULT Draw(TVector3d Position, float ZAngle) = 0;
        virtual HRESULT LoadFromFile(char *FileName) = 0;
    };
    
    class ICamera: public IResource
    {
    public:
		/*
		 * Устанавливает позицию камеры
		 * param[in] Позиция камеры
		 */
		virtual void SetPosition(const TVector3d) = 0;
		
		/*
		 * Устанавливает точку взгляда.
		 * param[in] Точка взгляда.
		 */
		virtual void SetTrackingPoint(const TVector3d) = 0;
		
		/*
		 * Устанавливает вектор верха камеры.
		 * param[in] Вектор верха.
		 */
		virtual void SetTopVector(const TVector3d) = 0;
		
		/*
		 * Поворачивает камеру в плоскости oXY
		 * param[in] Угол поворота.
		 */
		virtual void RotateHorizontal(const float) = 0;
		
		/*
		 * Поворачивает камеру вверх и вниз
		 * param[in] Угол поворота
		 */
		virtual void RotateVertical(const float) = 0;
		
		/*
		 * Передвигает вперед
		 * param[in] Величина сдвига
		 */
		virtual void MoveForwardBack(const float) = 0;
			
		/*
		 * Передвигает влево
		 * param[in] Величина сдвига
		 */
		virtual void MoveLeftRight(const float) = 0;

		/*
		 * Выводит камеру
		 */
		virtual void Draw() const = 0;
		
		/*
		 * Обрабатывает клавиатуру и мышь. Автоматически поворачивает и перемещает камеру. Свободный полет.
		 */
		virtual void AutomaticProcessingInput() = 0;
		
		/*
		 * Обновляет размеры окна для корректной работы AutomaticProcessingInput().
		 */
		virtual void UpdateWindowWidthAndHeight() = 0;
		
		/*
		 * Чувствительность мыши
		 */
		virtual void SetMouseSensivity(const float) = 0;
		virtual float GetMouseSensivity() const = 0;
		
		/*
		 * Смещение вперед
		 */
		virtual void SetMovingForwardOffset(const float) = 0;
		virtual float GetMovingForwardOffset() const = 0;
		
		/*
		 * Смещение назад
		 */
		virtual void SetMovingBackOffset(const float) = 0;
		virtual float GetMovingBackOffset() const = 0;
		
		/*
		 * Смещение в стороны
		 */
		virtual void SetMovingLeftRightOffset(const float) = 0;
		virtual float GetMovingLeftRightOffset() const = 0;
		
		/*
		 * Устанавливает управление свободной камерой
		 * param[in] Код клавиши, перемещающей камеру вперед
		 * param[in] Код клавиши, перемещающей камеру назад
		 * param[in] Код клавиши, перемещающей камеру влево
		 * param[in] Код клавиши, перемещающей камеру вправо
		 */
		virtual void SetControlKeys(const int, const int, const int, const int) = 0;
    };
    
    class ITexture: public IResource
    {
    public:
        virtual HRESULT BindTexture() = 0;
        virtual HRESULT LoadFromFile(char *FileName) = 0;
        virtual HRESULT LoadToGPU() = 0;
    };
    
    class ISoundSample: public IResource
    {
    public:
    };
    
    class IPhysicsObject: public IResource
    {
    public:
		virtual HRESULT GetPhysicsObjectType(E_PHYSICS_OBJECT_TYPE &PhysicsObjectType);
    };
    
    class ICollidable: public IPhysicsObject
    {
    public:
        
    };
    
    class IShape: public IPhysicsObject
    {
    public:
		virtual HRESULT GetShape(TVector3d *&pShape) = 0;
		virtual HRESULT SetShape(TVector3d *pShape) = 0;
		virtual HRESULT SetShapeType(E_SHAPE_TYPE ShapeType) = 0;
		virtual HRESULT GetShapeType(E_SHAPE_TYPE &ShapeType) = 0;
    };
    
    /*
     * Main engine systems
     */
    
    class IEngineSubsystem: public IEngineBase
    {
    public:
        virtual HRESULT GetType(E_ENGINE_SUBSYSTEM_TYPE &EngineSubSystem) = 0;
    };
    
    class IEngine: public IEngineBase
    {
    public:
        virtual HRESULT InitWindowAndSubsystems(const char* pWindowTitle, E_ENGINE_INITIALISATION_FLAGS InitFlags = EIF_DEFAULT) = 0;
        virtual HRESULT SetProcessInterval(uint ProcessPerSecond) = 0;
        virtual HRESULT SetGame(IGame *pGame) = 0;
		virtual HRESULT StopEngine() = 0;
		virtual	HRESULT AddToLog(const char *pText, bool Error = false) = 0;
        virtual HRESULT GetSubSystem(const E_ENGINE_SUBSYSTEM_TYPE SubSystemType, IEngineSubsystem *&SubSystem) = 0;
    };
    
    class IInput: public IEngineSubsystem
    {
    public:
        virtual HRESULT KeyPressed(const E_KEYBOARD_KEY_CODES KeyKode)const = 0;
        virtual HRESULT GetMouseState(TMouseState &MouseState)const = 0;
        virtual HRESULT BeginTextInput(char *pBuffer, uint BufferSize) = 0;
        virtual HRESULT EndTextInput() = 0;
    };
    
    class IRender2d: public IEngineBase
    {
    public:
        virtual HRESULT DrawRectangle() = 0;
    };
    
    class IRender3d: public IEngineBase
    {
    public:
    };
    
    class IRender: public IEngineSubsystem
    {
    public:
        virtual HRESULT GetRender2d(IRender2d *Render2d) = 0;
        virtual HRESULT GetRender3d(IRender3d *Render3d) = 0;
        virtual HRESULT AllowAutomaticSwappingProjectionType(bool Allow = true) = 0;
        virtual HRESULT SetProjectionType(E_PROJECTION_TYPE ProjectionType) = 0;
        
    };
    
    class IResourceManager: public IEngineSubsystem
    {
    public:
        virtual HRESULT GenerateResource(const E_RESOURCE_TYPE ResourceType, IResource *&pResource) = 0;
        virtual HRESULT LoadResource(char *pFileName, IResource *pResource) = 0;
        virtual HRESULT FreeResource(IResource *&pResource) = 0;
        virtual HRESULT GenerateTexture(ITexture *&pTexture) = 0;
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
     * Интерфейсы графического интерфейса))
     */
    
    class IGraphicalUserInterface: public IEngineBase
    {
    public:
        virtual HRESULT SetCoordinates(TVector2d Coordinates) = 0;
        virtual HRESULT GetCoordinates(TVector2d &Coordinates) = 0;
        virtual HRESULT SetSize(TVector2d Size) = 0;
        virtual HRESULT GetSize(TVector2d &Size) = 0;
        virtual HRESULT SetColor(TColor Color) = 0;
        virtual HRESULT GetColor(TColor &Color) = 0;
        virtual HRESULT SetTexture(ITexture *pTexture) = 0;
    };
    
    class IPanel: public IGraphicalUserInterface
    {
    public:
        virtual HRESULT AddItem(IGraphicalUserInterface *pItem) = 0;
        virtual HRESULT RemoveItem(IGraphicalUserInterface *pItem) = 0;
    };
    
    class IButton: public IGraphicalUserInterface
    {
    public:
        // TODO: Разобраться с типом Action!!!
        virtual HRESULT InitWithCaptionAndAction(char *Caption, void *pAction) = 0;
        virtual HRESULT SetAction(void *pAction) = 0;
        virtual HRESULT SetCaption(char *Caption) = 0;
        virtual HRESULT GetCaption(char *&Caption)const = 0;
    };
    
    class ILabel: public IGraphicalUserInterface
    {
    public:
        virtual HRESULT SetCaption(char *Caption) = 0;
        virtual HRESULT GetCaption(char *&Caption)const = 0;
    };
    
    class ICheckBox: public IGraphicalUserInterface
    {
    public:
        virtual HRESULT SetCaption(char *Caption) = 0;
        virtual HRESULT GetCaption(char *&Caption)const = 0;
        virtual HRESULT GetCheckState(bool isChecked)const = 0;
        
    };
    
    class IComboBox: public IGraphicalUserInterface
    {
    public:
        virtual HRESULT AddItem(char *Caption) = 0;
        virtual HRESULT SetCaptionAtIndex(char *Caption, uint Index) = 0;
        virtual HRESULT RemoveItem(char *Caption) = 0;
        virtual HRESULT GetIndexOfSelectedItem(uint &Index)const = 0;
        virtual HRESULT SelectItemAtIndex(uint Index) = 0;
        virtual HRESULT SelectItemWithCaption(char *Caption) = 0;
    };

    extern HRESULT GetEngine(IEngine *&EngineInterface);
    extern HRESULT FreeEngine();
}
#endif //_KSU_ENGINE_H
