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
        RT_MESH,
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
        int x,y;
        int dx,dy;
        float WorldX,WorldY,WorldZ;
        int dWheeel;
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
    
    class IMesh;
    class ICamera;
    class ITexture;
    class ISoundSample;
    class IPhysicsObject;
    class ICollidable;
    class IShape;
    
    class IResource: public IEngineBase
    {
    public:
        virtual HRESULT GetType(E_RESOURCE_TYPE &Type) = 0;
        virtual HRESULT LoadFromFile(char *FileName) = 0;
    };
    
    class IMesh: public IResource
    {
    public:
        virtual HRESULT Draw() = 0;
        virtual HRESULT Draw(TVector3d Position) = 0;
        virtual HRESULT Draw(TVector3d Position, float ZAngle) = 0;
        virtual HRESULT SetTexture(ITexture *Texture) = 0;
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
        virtual TVector3d GetPosition() = 0;
        virtual TVector3d GetVelocity() = 0;
        virtual HRESULT SetVelocity(TVector3d) = 0;
        virtual float GetRadius() = 0;
        virtual int GetWeight() = 0;
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
    };
    
    class IPhysics: public IEngineSubsystem
    {
    public:
        virtual HRESULT AddCollisionObserver() = 0;
        virtual HRESULT AddObject(ICollidable *) = 0;
        virtual HRESULT RemoveObject(ICollidable *) = 0;
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

//Physics collision observer function typedef
typedef void (*CollisionObserver)(KSU::ICollidable*,KSU::ICollidable*);


#endif //_KSU_ENGINE_H
