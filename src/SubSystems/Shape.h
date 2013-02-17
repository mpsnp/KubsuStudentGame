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
    TVector3d _SecondPoint;
    TVector3d *_pShape;
    E_SHAPE_TYPE _shapeType;
    
public:
    int GetRadius();
    HRESULT GetShape(TVector3d *&pShape);
    HRESULT SetShape(TVector3d *pShape);
    HRESULT SetShapeType(E_SHAPE_TYPE ShapeType);
    HRESULT GetShapeType(E_SHAPE_TYPE &ShapeType);
};

#endif /* defined(__TheGame__Shape__) */
