#ifndef _ENGINE_H
#define _ENGINE_H

#include <vector>
#include "CommonStructs.h"
#include "Vehicle.h"
#include "Model3d.h"
#include "glfw.h"
#include "map.h"

#define PI = 3.1415926535;

/*
 * Класс движка. 
 */
class CEngine
{
private:
	int _Width, _Height;
	std::vector<CVehicle> _Vehicles;
	std::vector<CModel3d> _Models;
	CMap _Map;
	bool _Running;
	const char* _c_WindowTitle;
	double _ProcessPerSecond;

	float _Frame;// =========== Тестовый костыль ==============

public:
	CEngine(string);
	~CEngine();
    
    /*
     * Основной цикл программы. Запускает
     * _Process() & _Draw();
     */
	void MainLoop();
    
    /*
     * Устанавливает кол-во исполнений _Process() в секунду
     */
	void SetProcessPerSecond(int);
private:
    

	/*
	 *функция загрузки ресурсов
	 *запускаеться 1 раз в конструкторе
	 */
	void _LoadResource();
    /*
     * Реализует систему просчета столкновений. Вызывается после каждого _Process()
     */
	void _Collision();
    
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
	void _WindowInit();
    
    /*
     * Реализует весь код инициализации OpenGL.
     * Вызывается 1 раз в конструкторе движка.
     */
	void _OpenGLInit();
};

#endif //_ENGINE_H
