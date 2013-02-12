#ifndef _COMMON_STRUCTS_H
#define _COMMON_STRUCTS_H

#include <cmath>

const float PI = 3.1415926535;

/*
 Структура для хранения трехмерного вектора/точки
 */
struct TVector3d
{
	float x,y,z;

	void InitVector(float X,float Y,float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

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

/*
 Структура для хранения двумерного вектора/точки
 */
struct TVector2d
{
	float x,y;
};

/*
 Структура для хранения индексов вершин полигона(треугольника)
 */
struct TFace3D
{
	unsigned short v0,v1,v2;
};

/*
 Структура для хранения цвета
 */
struct TColor
{
	float r,g,b,a;
};

#endif //_COMMON_STRUCTS_H
