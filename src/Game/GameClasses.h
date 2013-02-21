#ifndef _GAME_CLASSES_H
#define _GAME_CLASSES_H

#include "../KSUEngine.h"

using namespace KSU;

class CVehicle
{
private:
    IMesh       *_pMesh;
    ICollidable *_pCollidable;
public:
    CVehicle(IResourceManager *pRManager, IMesh *pMesh);
    void Draw();
    void Force(float Force);
    void Rotate(double AngleOffset);
    
    void SetPosition(TVector3d Position);
    void SetAngle(double Angle);
    
    TVector3d GetPosition();


};

#endif //_GAME_CLASSES_H
