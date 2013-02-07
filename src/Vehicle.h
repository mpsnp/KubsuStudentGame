#ifndef _VEHICLE_H
#define _VEHICLE_H

#include "Model3d.h"

class CVehicle
{
	const int _c_Id;
	const int _c_MaxVelocity;
	const int _c_MaxLife;
	const float _c_MaxAngle;
	const float _c_Radius;
	TVector3d _Position;
	TVector3d _VelocityVector;
	CMesh *_ModelPointer;
	int _Weight;
	int _Life;
public:
	CVehicle(int);
    
	/*
     * Приложение силы машине.
     * param[in] Сила.
     * param[in] Угол.
	 */
	void Force(float, float);
    
	/*
	 * Отрисовка машинки.
	 */
	void Draw();
    
	/*
	 * Изменение очков жизни.
	 * param[in] Кол-во очков жизни. Положительное - прибавить. Отрицательное - отнять.
	 */
	void ChangeLife(int);
    
    /*
     * Возвращает позицию машинки.
     */
	TVector3d GetPosition()const;
    
    /*
     * Возвращает радиус машинки.
     */
	float GetRadius()const;
    
    /*
     * Возвращает вектор скорости.
     */
	TVector3d GetVelocity()const;
    
    /*
     * Устанавливает вектор скорости.
     * param[in] Новый вектор скорости.
     */
	void SetVelocity(TVector3d);
    
    /*
     * Возвращает вес.
     */
	int GetWeight()const;
};

#endif //_VEHICLE_H
