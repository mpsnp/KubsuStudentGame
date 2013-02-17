//
//  Physics.h
//  TheGame
//
//  Created by Рашид on 16.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#ifndef __CPhysics__File__
#define __CPhysics__File__

#include "../CommonIncludes.h"

class CPhysics : IPhysics
{
    std::vector<ICollidable *> _objects;
    std::vector<CollisionObserver> _observers;
public:
    virtual HRESULT AddCollisionObserver(CollisionObserver);
    virtual HRESULT AddObject(ICollidable *);
    virtual HRESULT RemoveObject(ICollidable *);
    HRESULT ComputeCollisions();
};


#endif /* defined(__TheGame__File__) */