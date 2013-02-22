//
//  Physics.cpp
//  TheGame
//
//  Created by Рашид on 16.02.13.
//  Copyright (c) 2013 Parse Smart Ideas. All rights reserved.
//

#include "Physics.h"

CPhysics::CPhysics(IEngine *engine)
{
    _EngineCore = engine;
}

void CPhysics::Process()
{
    for (int i = 0; i < _objects.size(); i++) {
        _objects[i]->SetPosition(_objects[i]->GetPosition() + _objects[i]->GetVelocity());
    }
    ComputeCollisions();
}

HRESULT CPhysics::ComputeCollisions()
{
    for (int i = 0; i < _objects.size(); i++)
    {
        E_SHAPE_TYPE type_i, type_j;
        _objects[i]->GetShape()->GetShapeType(type_i);
        
        // Collision detection between vehicles
        for (int j = i+1; j < _objects.size(); j++)
        {
            TVector3d distance;
            float min_distance;
            
            _objects[j]->GetShape()->GetShapeType(type_j);
            
            if (type_i == ST_CIRCLE && type_j == ST_CIRCLE)
            {
                min_distance = _objects[i]->GetShape()->GetRadius() + _objects[j]->GetShape()->GetRadius();
                distance = _objects[i]->GetPosition() - _objects[j]->GetPosition();
            }
            else if (type_i == ST_LINE)
            {
                min_distance = _objects[j]->GetShape()->GetRadius();
                TVector3d a, b;
                a.InitVector(_objects[i]->GetPosition().x - _objects[j]->GetPosition().x,
                             _objects[i]->GetPosition().y - _objects[j]->GetPosition().y, 0);
                b.InitVector(_objects[i]->GetPosition().x - _objects[i]->GetShape()->GetPoint().x,
                             _objects[i]->GetPosition().y - _objects[i]->GetShape()->GetPoint().y, 0);
                distance = a * b / b.Length();
            }
            else
            {
                min_distance = _objects[i]->GetShape()->GetRadius();
                TVector3d a, b;
                a.InitVector(_objects[j]->GetPosition().x - _objects[i]->GetPosition().x,
                             _objects[j]->GetPosition().y - _objects[i]->GetPosition().y, 0);
                b.InitVector(_objects[j]->GetPosition().x - _objects[j]->GetShape()->GetPoint().x,
                             _objects[j]->GetPosition().y - _objects[j]->GetShape()->GetPoint().y, 0);
                distance = a * b / b.Length();
            }
            
            if (distance.LengthSquared() <= min_distance * min_distance)
            {
                /* Collision detected!
                ** TODO: reduce life of vehicles
                ** FIXED: compute new velocity vector
                */
                // p = mv;  Ek = mv^2/2
                TVector3d v1 = _objects[i]->GetVelocity();
                int		  m1 = _objects[i]->GetWeight();
                TVector3d v2 = _objects[j]->GetVelocity();
                int		  m2 = _objects[j]->GetWeight();
                
                _objects[i]->SetVelocity((v1 * (m1 - m2) + v2 * m2 * 2) * (1./(m1 + m2)));
                _objects[j]->SetVelocity((v2 * (m2 - m1) + v1 * m1 * 2) * (1./(m1 + m2)));
                
                std::vector<CollisionObserver>::iterator it;
                for (it = _observers.begin(); it != _observers.end(); it++)
                    ((CollisionObserver)*it)(_objects[i], _objects[j]);
            }
        }
    }
    
    return H_OK;
}

HRESULT CPhysics::GetType(E_ENGINE_SUBSYSTEM_TYPE &ess)
{
    ess =  ES_PHYSICS;
    
    return H_OK;
}

HRESULT CPhysics::AddCollisionObserver(CollisionObserver observer)
{
    std::vector<CollisionObserver>::iterator it;
    it = find(_observers.begin(), _observers.end(), observer);
    
    if (_objects.size() == 0 || (it == _observers.end() && *it != observer))
        _observers.push_back(observer);
    
    return H_OK;
}

HRESULT CPhysics::AddObject(ICollidable *object)
{
    std::vector<ICollidable*>::iterator it;
    it = find(_objects.begin(), _objects.end(), object);
    
    if (_objects.size() == 0 || (it == _objects.end() && *it != object))
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