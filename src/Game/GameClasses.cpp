#include "GameClasses.h"
#include <vector>
#include "glfw.h"

const int WEIGHT = 10;
const int RADIUS = 2;

CVehicle::CVehicle(IResourceManager *pRManager, IMesh *pMesh)
{
    IShape *pTempShape;
    pRManager->GenerateResource(RT_COLLIDABLE, (IResource *&)_pCollidable);
    pRManager->GenerateResource(RT_SHAPE, (IResource *&)pTempShape);
    pTempShape->SetShapeType(ST_CIRCLE);
    pTempShape->SetRadius(RADIUS);
    _pCollidable->SetShape(pTempShape);
    _pCollidable->SetWeight(WEIGHT);
    _pCollidable->SetVelocity(TVector3d(0, 0, 0));
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

double CVehicle::GetAngle()
{
    return _pCollidable->GetAngle();
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

TVector3d CVehicle::GetVelocity()
{
    return _pCollidable->GetVelocity();
}

CWall::CWall(IResourceManager *pRManager)
{
    IShape *pTempShape;
    pRManager->GenerateResource(RT_COLLIDABLE, (IResource*&)_pCollidable);
    pRManager->GenerateResource(RT_SHAPE, (IResource*&)pTempShape);
    pTempShape->SetShapeType(ST_LINE);
    pTempShape->SetPoint(TVector3d(10,10,0));
    _pCollidable->SetShape(pTempShape);
    _pCollidable->SetWeight(100000);
    _pCollidable->SetVelocity(TVector3d(0,0,0));
}

void CWall::Draw()
{
    glBegin(GL_QUADS);
    IShape *shape = _pCollidable->GetShape();
    TVector3d p = shape->GetPoint();
    TVector3d p2 = _pCollidable->GetPosition();
    glVertex3f(p.x, p.y, p.z);
    glVertex3f(p.x, p.y, p.z+2);
    glVertex3f(p2.x, p2.y, p2.z+2);
    glVertex3f(p2.x, p2.y, p2.z);
    glEnd();
}

void CWall::SetPoints(TVector3d pos1, TVector3d pos2)
{
    _pCollidable->GetShape()->SetPoint(pos1);
    _pCollidable->SetPosition(pos2);
}