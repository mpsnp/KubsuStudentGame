#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "CommonStructs.h"

class CCamera
{
    TVector3d _Position;
    TVector3d _LookingForVector;
    TVector3d _TopVector;
    
    float _AngleHorizontal;
    float _AngleVertical;
    
    float _MouseSensivity;
    
    float _MovingForwardOffset;
    float _MovingBackOffset;
    float _MovingLeftRightOffset;
    
    int _Width;
    int _Height;
public:
    /*
     * Конструктор. 
     * Инициализирует начальное положение камеры.
     */
    CCamera();
    
    /*
     * Устанавливает позицию камеры.
     * param[in] Позиция камеры.
     */
    void SetPosition(const TVector3d);
    
    /*
     * Устанавливает точку взгляда.
     * param[in] Точка взгляда.
     */
    void SetTrackingPoint(const TVector3d);
    
    /*
     * Устанавливает вектор верха камеры.
     * param[in] Вектор верха.
     */
    void SetTopVector(const TVector3d);
    
    /*
     * Поворачивает камеру в плоскости oXY
     * param[in] Угол поворота.
     */
    void RotateHorizontal(const float);
    
    /*
     * Поворачивает камеру вверх и вниз
     * param[in] Угол поворота
     */
    void RotateVertical(const float);
    
    /*
     * Передвигает вперед
     * param[in] Величина сдвига
     */
    void MoveForwardBack(const float);
        
    /*
     * Передвигает влево
     * param[in] Величина сдвига
     */
    void MoveLeftRight(const float);

    /*
     * Выводит камеру
     */
    void Draw() const;
    
    /*
     * Обрабатывает клавиатуру и мышь. Автоматически поворачивает и перемещает камеру. Свободный полет.
     */
    void AutomaticProcessingInput();
    
    /*
     * Обновляет размеры окна для корректной работы AutomaticProcessingInput().
     */
    void UpdateWindowWidthAndHeight();
private:
    
    /*
     * Обновляет _LookingForVector в соответствии с углами
     */
    void _UpdateLookingForVector();
    
    /*
     * Обновляет _TopVector в соответствии с _LookingForVector и старым _TopVector
     */
    void _UpdateTopVector();
    
    //TODO: MouseSensivity Setter and Getter
    //TODO: MovingOffsets Setters and Getters
};

#endif //_CAMERA_H_
