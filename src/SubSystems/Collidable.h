//
//  Collidable.h
//  TheGame
//
//  Created by Рашид on 17.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#ifndef __TheGame__Collidable__
#define __TheGame__Collidable__

#include "../CommonIncludes.h"

class CCollidable : public ICollidable
{
    IShape *_pShape;
    TVector3d _Velocity;
    TVector3d _Position;
    int _Weight;
    
public:
    TVector3d GetPosition();
    TVector3d GetVelocity();
    HRESULT SetVelocity(TVector3d);
    IShape*& GetShape();
    HRESULT SetShape(IShape *pShape);
    int GetWeight();
};

#endif /* defined(__TheGame__Collidable__) */
