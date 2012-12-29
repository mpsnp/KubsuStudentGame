#ifndef _COMMON_STRUCTS_H
#define _COMMON_STRUCTS_H

#include <cmath>
struct TVector3d
{
	float x,y,z;

	TVector3d operator *(TVector3d &vector)const
	{
		TVector3d res;
		res.x = y * vector.z - vector.y * z;
		res.y = z * vector.x - vector.z * x;
		res.z = x * vector.y - vector.x * y;

		return res;
	}

	TVector3d operator *(float scalar)const
	{
		TVector3d res = {x,y,z};
		res.x *= scalar;
		res.y *= scalar;
		res.z *= scalar;
		return res;
	}

	TVector3d operator /(float scalar)const
	{
		TVector3d res = {x,y,z};
		res.x /= scalar;
		res.y /= scalar;
		res.z /= scalar;
		return res;
	}

	TVector3d operator +(TVector3d vector)const
	{
		TVector3d res;
		res.x = x + vector.x;
		res.y = y + vector.y;
		res.z = z + vector.z;

		return res;
	}

	TVector3d operator -(TVector3d vector)const
	{
		TVector3d res;
		res.x = x - vector.x;
		res.y = y - vector.y;
		res.z = z - vector.z;

		return res;
	}

	TVector3d Vector(TVector3d v1,TVector3d v2)
	{
		return v1 - v2;
	}

	float Length()const
	{
		return sqrt(x*x + y*y + z*z);
	}

	void Normalize()
	{
		float length = Length();
		x = x/length;
		y = y/length;
		z = z/length;
	}

	float LengthSquared()const
	{
		return (x*x + y*y + z*z);
	}
};

struct TVector2d
{
	float x,y;
};

struct TFace3D
{
	unsigned short v0,v1,v2;
};

struct TColor
{
	float r,g,b,a;
};

#endif //_COMMON_STRUCTS_H
