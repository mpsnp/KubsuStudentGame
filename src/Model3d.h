#ifndef _MODEL3D_H
#define _MODEL3D_H

#include <string>
#include "CommonStructs.h"
#include "glfw.h"
#include "CommonIncludes.h"

using namespace std;
class CMesh: public IMesh
{
	unsigned short _NVertexes;
	TVector3d *_Vertexes;
	TVector2d *_TexCoords;
	TVector3d *_Normals;
	unsigned short _NTriangles;
	TFace3D *_Triangles;
	TColor _Color;
	GLuint _Texture;
	bool _LoadedSuccsessfull;
	const char *_FileName;
public:
	CMesh(void);
	~CMesh(void);
    
    /*
     * Рендер модели в точке.
     * param[in] Центр объекта
     */
    HRESULT Draw(TVector3d Position);
    
    /*
     * Рендер модели в начале координат.
     */    
    HRESULT Draw();
    
    HRESULT Draw(TVector3d Position, float ZAngle);
    
    HRESULT LoadFromFile(char *FileName);
    
    HRESULT GetType(E_RESOURCE_TYPE &Type);
    /*
     * Загрузка модели из файла .3ds
     * param[in] Имя файла.
     */
	bool LoadFrom3ds(string);
    
    /*
     * Задает цвет модели. Цвета указываются в диапазоне от 0.0 до 1.0
     * param[in] Red color.
     * param[in] Green color.
     * param[in] Blue color.
     * param[in] Alpha.
     */
	void SetColor(float,float,float,float);
    
    /*
     * Возвращает имя файла.
     */
	const char* GetFileName();
private:
    
    /*
     * Загружает текстуру из файла.
     * param[in] Имя файла.
     */
	bool _LoadTextureFromFile(string);
    
    /*
     * Возвращает позицию чанка в потоке. Если чанк не найден, то возвращает 0.
     * param[in] Поток.
     * param[in] ID чанка.
     * param[in] Является ли текущий чанк родительским.
     */
	unsigned int _FindChunk(ifstream&, unsigned short, bool);
    
    /*
     * Вычисляет нормали модели.
     */
	void _ComputeNormals();
};

#endif //_MODEL3D_H
