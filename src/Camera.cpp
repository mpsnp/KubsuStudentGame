#include "Camera.h"
#include "glfw.h"
#include <cmath>

CCamera::CCamera()
{
    _Position = {0,0,0};
    _LookingForVector = {0,1,0};
    _TopVector = {0,0,1};
    _AngleHorizontal = 0.0;
    _AngleVertical = 0.0;
    _MovingLeftRightOffset = 0.1;
    _MovingForwardOffset = 0.1;
    _MovingBackOffset = -0.1;
    _MouseSensivity = 0.2;
}

void CCamera::SetTrackingPoint(const TVector3d TrackingPoint)
{
    _LookingForVector = TrackingPoint - _Position;
    _LookingForVector.Normalize();
}

void CCamera::SetTopVector(const TVector3d TopVector)
{
    _TopVector = TopVector;
    _TopVector.Normalize();
}

void CCamera::SetPosition(const TVector3d Position)
{
    _Position = Position;
}

void CCamera::RotateHorizontal(const float Angle)
{
    _AngleHorizontal += Angle;
    _UpdateLookingForVector();
}

void CCamera::RotateVertical(const float Angle)
{
    _AngleVertical += Angle;
    _UpdateLookingForVector();
}

void CCamera::_UpdateLookingForVector()
{
    _LookingForVector.x = cosf(_AngleHorizontal);
    _LookingForVector.y = sinf(_AngleHorizontal);
    _LookingForVector = _LookingForVector * cosf(_AngleVertical);
    _LookingForVector.z = sinf(_AngleVertical);
}

void CCamera::_UpdateTopVector()
{
    TVector3d Normal = _LookingForVector * _TopVector;
    _TopVector = Normal * _LookingForVector;
}

void CCamera::Draw() const
{
    gluLookAt(_Position.x, _Position.y, _Position.z,
              _Position.x + _LookingForVector.x,
              _Position.y + _LookingForVector.y,
              _Position.z + _LookingForVector.z,
              _TopVector.x, _TopVector.y, _TopVector.z);
}

void CCamera::MoveForwardBack(const float Offset)
{
    _Position = _Position + _LookingForVector * Offset;
}

void CCamera::MoveLeftRight(const float Offset)
{
    TVector3d OffsetVector = (_TopVector * _LookingForVector);
    OffsetVector.Normalize();
    _Position = _Position + OffsetVector * Offset;
}

void CCamera::UpdateWindowWidthAndHeight()
{
    glfwGetWindowSize(&_Width, &_Height);
}

void CCamera::AutomaticProcessingInput()
{
    //TODO: Убрать магические GLFW_KEY_UP итд.
    //TODO: Сделать ограничители вертикального угла, чтобы изображение не переворачивалось.
    if (glfwGetKey(GLFW_KEY_UP)) {
        MoveForwardBack(_MovingForwardOffset);
    }
    if (glfwGetKey(GLFW_KEY_DOWN)) {
        MoveForwardBack(_MovingBackOffset);
    }
    if (glfwGetKey(GLFW_KEY_LEFT)) {
        MoveLeftRight(_MovingLeftRightOffset);
    }
    if (glfwGetKey(GLFW_KEY_RIGHT)) {
        MoveLeftRight(-_MovingLeftRightOffset);
    }
    int MousePositionX,MousePositionY;
    glfwGetMousePos(&MousePositionX, &MousePositionY);
    MousePositionX -= _Width / 2;
    MousePositionY -= _Height / 2;
    RotateHorizontal(((-MousePositionX * PI) / 180.0) * _MouseSensivity);
    RotateVertical(((-MousePositionY * PI) / 180.0) * _MouseSensivity);
    glfwSetMousePos(_Width / 2, _Height / 2);
}