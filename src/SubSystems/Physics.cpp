//
//  Physics.cpp
//  TheGame
//
//  Created by Рашид on 16.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#include "Physics.h"

HRESULT CPhysics::ComputeCollisions()
{
    for (int i = 0; i < _objects.size(); i++)
    {
        // Collision detection between vehicles
        for (int j = i+1; j < _objects.size(); j++)
        {
            TVector3d distance = _objects[i]->GetPosition() - _objects[j]->GetPosition();
            float min_distance = _objects[i]->GetShape()->GetRadius() + _objects[j]->GetShape()->GetRadius();
            if (distance.LengthSquared() <= min_distance * min_distance)
            {
                /*Collision detected!
                ** TODO: reduce vehicles life
                ** FIXED: compute new velocity vector
                */
                // p = mv;  Ek = mv^2/2
                TVector3d v1 = _objects[i]->GetVelocity();
                int		  m1 = _objects[i]->GetWeight();
                TVector3d v2 = _objects[j]->GetVelocity();
                int		  m2 = _objects[j]->GetWeight();
                
                _objects[i]->SetVelocity((v1 * (m1 - m2) + v2 * m2 * 2) * (1/(m1 + m2)));
                _objects[j]->SetVelocity((v2 * (m2 - m1) + v1 * m1 * 2) * (1/(m1 + m2)));
                
                std::vector<CollisionObserver>::iterator it;
                for (it = _observers.begin(); it != _observers.end(); it++)
                    ((CollisionObserver)*it)(_objects[i], _objects[j]);
            }
        }
    }
    
    return H_OK;
}

HRESULT CPhysics::AddCollisionObserver(CollisionObserver observer)
{
    std::vector<CollisionObserver>::iterator it;
    it = find(_observers.begin(), _observers.end(), observer);
    
    if (it == _observers.end() && *it != observer)
        _observers.push_back(observer);
    
    return H_OK;
}

HRESULT CPhysics::AddObject(ICollidable *object)
{
    std::vector<ICollidable*>::iterator it;
    it = find(_objects.begin(), _objects.end(), object);
    
    if (it == _objects.end() && *it != object)
        _objects.push_back(object);
    
    return H_OK;
}

HRESULT CPhysics::RemoveObject(ICollidable *object)
{
    std::vector<ICollidable*>::iterator it;
    it = find(_objects.begin(), _objects.end(), object);
    
    if (*it == object)
        _objects.erase(it);
    
    return H_OK;
}