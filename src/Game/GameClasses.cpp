#include "GameClasses.h"
#include <vector>

const int WEIGHT = 10;

CVehicle::CVehicle(IResourceManager *pRManager, IMesh *pMesh)
{
    IShape *pTempShape;
    pRManager->GenerateResource(RT_COLLIDABLE, (IResource *&)_pCollidable);
    pRManager->GenerateResource(RT_SHAPE, (IResource *&)pTempShape);
    pTempShape->SetShapeType(ST_CIRCLE);
    pTempShape->SetRadius(2);
    _pCollidable->SetShape(pTempShape);
    _pCollidable->SetWeight(WEIGHT);
    _pCollidable->SetVelocity({0,0,0});
    _pMesh = pMesh;
}

void CVehicle::Draw()
{
    _pMesh->Draw(_pCollidable->GetPosition(), _pCollidable->GetAngle());
}

void CVehicle::SetPosition(TVector3d Position)
{
    _pCollidable->SetPosition(Position);
}

void CVehicle::Force(float Force)
{
    _pCollidable->Force(Force);
}

void CVehicle::SetAngle(double Angle)
{
    _pCollidable->SetAngle(Angle);
}

void CVehicle::Rotate(double AngleOffset)
{
    _pCollidable->SetAngle(_pCollidable->GetAngle() + AngleOffset);
}

TVector3d CVehicle::GetPosition()
{
    return _pCollidable->GetPosition();
}
