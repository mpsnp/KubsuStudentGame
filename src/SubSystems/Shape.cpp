//
//  Shape.cpp
//  TheGame
//
//  Created by Рашид on 17.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#include "Shape.h"

HRESULT CShape::GetType(E_RESOURCE_TYPE &Type)
{
    Type = RT_SHAPE;
    
    return H_OK;
}

HRESULT CShape::LoadFromFile(char *FileName)
{
    //FileName = "TODO: Make something";
    
    return H_OK;
}

double CShape::GetRadius()
{
    return sqrt(_SecondPoint.x*_SecondPoint.x + _SecondPoint.y*_SecondPoint.y);
}

HRESULT CShape::SetRadius(double Radius)
{
    _SecondPoint = TVector3d(Radius,0,0);
    return H_OK;
}

std::vector<TVector3d>* CShape::GetShape()
{
    return _Shape;
}

HRESULT CShape::SetShape(std::vector<TVector3d>* shape_array)
{
    _Shape = shape_array;
    
    return H_OK;
}

HRESULT CShape::SetShapeType(E_SHAPE_TYPE ShapeType)
{
    _shapeType = ShapeType;
    
    return H_OK;
}

HRESULT CShape::GetShapeType(E_SHAPE_TYPE &ShapeType)
{
    ShapeType = _shapeType;
    
    return H_OK;
}

TVector3d CShape::GetPoint()
{
    return _SecondPoint;
}

HRESULT CShape::SetPoint(TVector3d point)
{
    _SecondPoint = point;
    
    return H_OK;
}

HRESULT CShape::GetPhysicsObjectType(E_PHYSICS_OBJECT_TYPE &PhysicsObjectType)
{
    PhysicsObjectType = POT_SHAPE;
    
    return H_OK;
}