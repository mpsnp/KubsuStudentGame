//
//  Shape.h
//  TheGame
//
//  Created by Рашид on 17.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#ifndef __TheGame__Shape__
#define __TheGame__Shape__

#include "../CommonIncludes.h"

class CShape : public IShape
{
    TVector2d _SecondPoint;
    std::vector<TVector3d> *_Shape;
    E_SHAPE_TYPE _shapeType;
    
public:
    HRESULT GetPhysicsObjectType(E_PHYSICS_OBJECT_TYPE &PhysicsObjectType);
    double GetRadius();
    HRESULT SetRadius(double Radius);
    TVector2d GetPoint();
    std::vector<TVector3d> * GetShape();
    HRESULT SetShape(std::vector<TVector3d> *);
    HRESULT SetShapeType(E_SHAPE_TYPE ShapeType);
    HRESULT GetShapeType(E_SHAPE_TYPE &ShapeType);
    HRESULT GetType(E_RESOURCE_TYPE &Type);
    HRESULT LoadFromFile(char *FileName);
};

#endif /* defined(__TheGame__Shape__) */
