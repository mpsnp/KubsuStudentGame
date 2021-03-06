//
//  Collidable.cpp
//  TheGame
//
//  Created by Рашид on 17.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#include "Collidable.h"

HRESULT CCollidable::GetType(E_RESOURCE_TYPE &Type)
{
    Type = RT_COLLIDABLE;
    
    return H_OK;
}

HRESULT CCollidable::LoadFromFile(char *FileName)
{
    FileName = "TODO: Make something";
    
    return H_OK;
}


HRESULT CCollidable::SetPosition(TVector3d pos)
{
    _Position = pos;
    
    return H_OK;
}

CCollidable::CCollidable(IEngine *engine)
{
    _pEngineCore = engine;
}

TVector3d CCollidable::GetPosition()
{
    return _Position;
}

TVector3d CCollidable::GetVelocity()
{
    return _Velocity;
}

HRESULT CCollidable::SetVelocity(TVector3d vel)
{
    _Velocity = vel;
    
    return H_OK;
}

IShape*& CCollidable::GetShape()
{
    return _pShape;
}

HRESULT CCollidable::SetShape(IShape *pShape)
{//скопировал указатель в надежде, что объект не будет удален по другому указателю извне
    _pShape = pShape;
    
    return H_OK;
}

int CCollidable::GetWeight()
{
    return _Weight;
}

HRESULT CCollidable::Force(float Force)
{
	double t = _pEngineCore->GetProcessInterval();
	// F = ma;
	float a = Force / _Weight;
	// V = V0 + at
	float v0y = _Velocity.y;
    float v0x = _Velocity.x;
	float vx = v0x + a * t;
    float vy = v0y + a * t;
	// changing speed
	_Velocity.x = vx;
	_Velocity.y = vy;
	// changing direction
	float x = _Velocity.x;
	float y = _Velocity.y;
	_Velocity.x = x * cos(_Angle - _PrevAngle) - y * sin(_Angle - _PrevAngle);
	_Velocity.y = y * cos(_Angle - _PrevAngle) + x * sin(_Angle - _PrevAngle);
    
    return H_OK;
}

HRESULT CCollidable::SetWeight(int newWeight)
{
    _Weight = newWeight;
    
    return H_OK;
}

HRESULT CCollidable::GetPhysicsObjectType(E_PHYSICS_OBJECT_TYPE &PhysicsObjectType)
{
    PhysicsObjectType = POT_COLLIDABLE;
    
    return H_OK;
}

double CCollidable::GetAngle()
{
    return _Angle;
}

HRESULT CCollidable::SetAngle(double newAngle)
{
    _PrevAngle = _Angle;
    _Angle = newAngle;
    
    return H_OK;
}