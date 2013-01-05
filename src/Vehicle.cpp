#include "Vehicle.h"

CVehicle::CVehicle(int identifier)
	: _c_Id(identifier), _c_MaxAngle(3.14/3), _c_MaxVelocity(10), _c_Radius(2), _c_MaxLife(100)
{
	_VelocityVector.x = 0;
	_VelocityVector.y = 0;
	_VelocityVector.z = 0;
	_Life = _c_MaxLife;
}

TVector3d CVehicle::GetPosition()const
{
	return _Position;
}

TVector3d CVehicle::GetVelocity()const
{
	return _VelocityVector;
}

void CVehicle::SetVelocity(TVector3d new_velocity)
{
	_VelocityVector = new_velocity;
}

int CVehicle::GetWeight()const
{
	return _Weight;
}

void CVehicle::Force(float Force,float Angle)
{
	// check angle
	if (Angle > _c_MaxAngle)
		Angle = _c_MaxAngle;
	// F = ma;
	float a = Force / _Weight;
	// V = V0 + at^2/2
	float v0 = _VelocityVector.Length();
	float v = v0 + a / 2;
	// check velocity
	if (v > _c_MaxVelocity)
		v = _c_MaxVelocity;
	// changing speed
	_VelocityVector.x *= v/v0;
	_VelocityVector.y *= v/v0;
	// changing direction
	float x = _VelocityVector.x;
	float y = _VelocityVector.y;
	_VelocityVector.x = x * cos(Angle) - y * sin(Angle);
	_VelocityVector.y = y * cos(Angle) + x * sin(Angle);
}

float CVehicle::GetRadius()const
{
	return _c_Radius;
}

void CVehicle::Draw()
{
	_ModelPointer->Draw(_Position);
}

void CVehicle::ChangeLife(int value)
{
	_Life += value;
	if (_Life > _c_MaxLife)
		_Life = _c_MaxLife;
	if (_Life <= 0)
	{
		_Life = 0;
		// TODO: vehicle fully damaged it should be removed or anything else
	}
}
