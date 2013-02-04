#include "Camera.h"
#include "glfw.h"
#include <cmath>

CCamera::CCamera()
{
    _Position = {0,0,1};
    _LookingForVector = {0,1,0};
    _TopVector = {0,0,1};
    _AngleHorizontal = 0.0;
    _AngleVertical = 0.0;
    _MovingLeftRightOffset = 0.1;
    _MovingForwardOffset = 0.1;
    _MovingBackOffset = -0.1;
    _MouseSensivity = 0.2;
    UpdateWindowWidthAndHeight();
    SetControlKeys(GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT);
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
    if (_AngleVertical >= PI / 2)
        _AngleVertical = PI / 2 * 0.9999;
    if (_AngleVertical <= -PI / 2)
        _AngleVertical = -PI / 2 * 0.9999;
    _UpdateLookingForVector();
}

void CCamera::_UpdateLookingForVector()
{
    _LookingForVector.x = cosf(_AngleHorizontal);
    _LookingForVector.y = sinf(_AngleHorizontal);
    _LookingForVector = _LookingForVector * cosf(_AngleVertical);
    _LookingForVector.z = sinf(_AngleVertical);
}

void CCamera::SetControlKeys(const int KeyForward,
                             const int KeyBackward,
                             const int KeyLeft,
                             const int KeyRight)
{
    _KeyForward     = KeyForward;
    _KeyBackward    = KeyBackward;
    _KeyLeft        = KeyLeft;
    _KeyRight       = KeyRight;
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

void CCamera::SetMouseSensivity(float MouseSensivity)
{
    _MouseSensivity = MouseSensivity;
}

float CCamera::GetMouseSensivity() const
{
    return _MouseSensivity;
}

void CCamera::SetMovingForwardOffset(float MovingForwardOffset)
{
    _MovingForwardOffset = MovingForwardOffset;
}

float CCamera::GetMovingForwardOffset() const
{
    return _MovingForwardOffset;
}

void CCamera::SetMovingBackOffset(float MovingBackOffset)
{
    _MovingBackOffset = MovingBackOffset;
}

float CCamera::GetMovingBackOffset() const
{
    return _MovingBackOffset;
}

void CCamera::SetMovingLeftRightOffset(float MovingLeftRightOffset)
{
    _MovingLeftRightOffset = MovingLeftRightOffset;
}

float CCamera::GetMovingLeftRightOffset() const
{
    return _MovingLeftRightOffset;
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
    if (glfwGetKey(_KeyForward)) {
        MoveForwardBack(_MovingForwardOffset);
    }
    if (glfwGetKey(_KeyBackward)) {
        MoveForwardBack(_MovingBackOffset);
    }
    if (glfwGetKey(_KeyLeft)) {
        MoveLeftRight(_MovingLeftRightOffset);
    }
    if (glfwGetKey(_KeyRight)) {
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