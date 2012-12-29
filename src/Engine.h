#ifndef _ENGINE_H
#define _ENGINE_H

using namespace std;

#include <vector>
#include "CommonStructs.h"
#include "Vehicle.h"
#include "Model3d.h"

#define PI = 3.1415926535;

class CEngine
{
private:
	int _Width, _Height;
	std::vector<CVehicle> _Vehicles;
	std::vector<CModel3d> _Models;
	CModel3d _Map;
	bool _Running;
	char* _WindowTitle;

	float _Frame;// =========== Тестовый костыль ==============

public:
	CEngine();
	~CEngine();
	void MainLoop();
private:
	// _Collision implements Collision detection system it should be called everytime in every loop iteration
	void _Collision();
	void _Process();
	void _Draw();
};

#endif //_ENGINE_H
