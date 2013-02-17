//
//  Collidable.cpp
//  TheGame
//
//  Created by Рашид on 17.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#include "Collidable.h"

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