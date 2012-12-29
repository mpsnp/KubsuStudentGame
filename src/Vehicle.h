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
	CModel3d *_ModelPointer;
	int _Weight;
	int _Life;
public:
	/*
	** � ����������� ���������� ������������� ����
	*/
	CVehicle(int);
	/*
	** Force - ���������� ������ � ��������
	** ���������: ����, ����
	*/
	void Force(float, float);
	/*
	** Draw - ��������� �������, �� ��� ���� �� ���
	*/
	void Draw();
	/*
	** ChangeLife - ��������� ���������� ����� �����
	** ���������: ���������� ����� (������������� - �����������, ������������� - ��������)
	*/
	void ChangeLife(int value);
	TVector3d GetPosition()const;
	float GetRadius()const;
	TVector3d GetVelocity()const;
	void SetVelocity(TVector3d new_velocity);
	int GetWeight()const;
};

#endif //_VEHICLE_H
