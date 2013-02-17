//
//  Shape.cpp
//  TheGame
//
//  Created by Рашид on 17.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#include "Shape.h"

int CShape::GetRadius()
{
    
    
    return 0;
}

HRESULT CShape::GetShape(TVector3d *&pShape)
{
    pShape = _pShape;
    return H_OK;
}

HRESULT CShape::SetShape(TVector3d *pShape)
{
    _pShape = pShape;
    
    return H_OK;
}

HRESULT CShape::SetShapeType(E_SHAPE_TYPE ShapeType)
{
    _shapeType = ShapeType;
    
    return H_OK;
}
