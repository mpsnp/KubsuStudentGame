#include "Model3d.h"
#include "glfw.h"
#include <fstream>

//TODO: в LoadFrom3ds подгрузить материал
//FIXED: сделать расчет нормалей

CModel3d::CModel3d(void)
	:_Vertexes(NULL), _TexCoords(NULL), _Triangles(NULL), _Normals(NULL)
{
	_Color.r=1;
	_Color.g=1;
	_Color.b=1;
	_Color.a=1;
}

void CModel3d::SetColor(float R,float G,float B, float A)
{
	_Color.r=R;
	_Color.g=G;
	_Color.b=B;
	_Color.a=A;
}

CModel3d::~CModel3d(void)
{
}

void CModel3d::Draw(TVector3d vector)
{
	glTranslatef(vector.x,vector.y,vector.z);
	glColor4f(_Color.r,_Color.g,_Color.b,_Color.a);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _TexCoords);
	glVertexPointer(3, GL_FLOAT, 0, _Vertexes);
	glNormalPointer(GL_FLOAT, 0, _Normals);
	glDrawElements(GL_TRIANGLES, _NTriangles * 3, GL_UNSIGNED_INT, _Triangles);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CModel3d::Draw()
{
	glColor4f(_Color.r,_Color.g,_Color.b,_Color.a);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _TexCoords);
	glVertexPointer(3, GL_FLOAT, 0, _Vertexes);
	glNormalPointer(GL_FLOAT, 0, _Normals);
	glDrawElements(GL_TRIANGLES, _NTriangles*3, GL_UNSIGNED_SHORT, _Triangles);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CModel3d::_ComputeNormals()
{
	TVector3d vVector1, vVector2, vNormal, vPoly[3];

	TVector3d	*pNormals		= new TVector3d [_NTriangles];
	TVector3d	*pTempNormals	= new TVector3d [_NTriangles];
				_Normals		= new TVector3d [_NVertexes];

	for(int i=0; i < _NTriangles; i++)
	{
		// Сохраняем 3 точки этого полигона, чтобы избежать большого кода
		vPoly[0] = _Vertexes[_Triangles[i].v0];
		vPoly[1] = _Vertexes[_Triangles[i].v1];
		vPoly[2] = _Vertexes[_Triangles[i].v2];
		// нормали полигонов
		vVector1.Vector(vPoly[0], vPoly[2]);
		vVector2.Vector(vPoly[2], vPoly[1]);
		vNormal  = vVector1 * vVector2;
		pTempNormals[i] = vNormal;
		vNormal.Normalize();
		pNormals[i] = vNormal;
	}

	//////////////// Теперь получаем вершинные нормали /////////////////

	TVector3d vSum = {0.0, 0.0, 0.0};
	TVector3d vZero = vSum;
	int shared=0;

	for (int i = 0; i < _NVertexes; i++)
	{
		for (int j = 0; j < _NTriangles; j++)
		{
			if (_Triangles[j].v0 == i || _Triangles[j].v1 == i || _Triangles[j].v2 == i)
			{
			vSum = vSum + pTempNormals[j];
			shared++;
			}
		}
		_Normals[i] = vSum / float(-shared);
		_Normals[i].Normalize();
		vSum = vZero;
		shared = 0;
	}

	delete [] pTempNormals;
	delete [] pNormals;
}

bool CModel3d::LoadFrom3ds(string FileName)
{
	const int CHUNK_HEADER_LENGTH = 6;

	 //Переменные и константы
    const int MAIN3DS               =0x4D4D;//Идентификатор *.3DS файла
    const int EDIT3DS               =0x3D3D;//Блок редактора (this is the start of the editor config)
    const int EDIT_OBJECT           =0x4000;//Объект (сетка, источник света, камера)
    //------ sub defines of EDIT_OBJECT
    const int OBJ_TRIMESH           =0x4100;
    //------ sub defines of OBJ_TRIMESH
    const int TRI_VERTEXLIST        =0x4110;
    const int TRI_VERTEXOPTIONS     =0x4111;
    const int TRI_MAPPINGCOORS      =0x4140;
    const int TRI_MAPPINGSTANDARD   =0x4170;
    const int TRI_FACELIST          =0x4120;
    const int TRI_SMOOTH            =0x4150;
    const int TRI_MATERIAL          =0x4130;
    const int TRI_LOCAL             =0x4160;
    const int TRI_VISIBLE           =0x4165;
    //Все остальные блоки нас не волнуют
    unsigned short	chunk_id;//Идентификатор блока
    unsigned int	chunk_pos;//Позиция начала блока
    unsigned int	chunk_temppos;//Временная позиция начала блока
    unsigned int	chunk_len;//Смещение к следующему блоку (от chunk_id)

    //Откроем файл 3DS
    ifstream ifs;
    ifs.open(FileName.c_str(),ios::in); //| ios::binary | ios::beg);
    if(!ifs.is_open())
    {
        //Не удалось открыть файл
        return false;
    }
    else
    {
        //Проверим является ли файл *.3DS формата
        ifs.read((char*)&chunk_id,2);
        ifs.read((char*)&chunk_len,4);
        if(chunk_id!=MAIN3DS) return false;
        ifs.seekg((int)ifs.tellg()-CHUNK_HEADER_LENGTH);
        //Следующий должен быть блок редактора
        chunk_pos=_FindChunk(ifs,EDIT3DS,true);
        if(chunk_pos==0) return false;
        //Пропускаем все кроме блока объекта
        chunk_pos=_FindChunk(ifs,EDIT_OBJECT,true);
        if(chunk_pos==0) return false;
        //Читаем имя объекта (если оно нам нужно)
        //...
        //Пропускаем все кроме блока объекта
        chunk_pos=_FindChunk(ifs,OBJ_TRIMESH,true);
        if(chunk_pos==0) return false;
        //Запомним позицию блока OBJ_TRIMESH
        chunk_temppos=chunk_pos;
        //Если мы дошли до сюда, то мы нашли объект-сетку. Считаем его
        //---Дойдем до блока вершин---
        chunk_pos=_FindChunk(ifs,TRI_VERTEXLIST,true);
        if(chunk_pos==0) return false;
        ifs.ignore(6);
        //Считаем вершины предварительно выделив память
        ifs.read((char*)&_NVertexes,2);
        //Выделим память
            //Если уже выделяли уничтожим и выделим снова
            if(_Vertexes) delete[] _Vertexes;
            if(_TexCoords) delete[] _TexCoords;
            if(_Triangles) delete[] _Triangles;
        _Vertexes = new TVector3d[_NVertexes];
        //Считаем
		ifs.read((char*)(_Vertexes),_NVertexes*3*4);
        //---Дойдем до списка текстурных вершин---
        ifs.seekg(chunk_temppos);
        chunk_pos=_FindChunk(ifs,TRI_MAPPINGCOORS,true);
        if(chunk_pos==0) return false;
        ifs.ignore(6);
        //Считаем текстурные вершины предварительно выделив память
        unsigned short nTexCoords;
        ifs.read((char*)&nTexCoords,2);
        //Вылелим память
        _TexCoords=new TVector2d[nTexCoords];
        //Считаем
		ifs.read((char*)(_TexCoords),nTexCoords*2*4);
        //---Дойдем до списка граней---
        ifs.seekg(chunk_temppos);
        chunk_pos=_FindChunk(ifs,TRI_FACELIST,true);
        if(chunk_pos==0) return false;
        ifs.ignore(6);
        //Считаем грани предварительно выделив память
        ifs.read((char*)&_NTriangles,2);
        //Вылелим память
        _Triangles=new TFace3D[_NTriangles];
        //Считаем
        for(int i=0;i<_NTriangles;i++)
        {
            ifs.read((char*)&(_Triangles[i]),6);
            ifs.ignore(2);
        }
        //---Дойдем к данным о локальной системе объекта---
        ifs.seekg(chunk_temppos);
        chunk_pos=_FindChunk(ifs,TRI_LOCAL,true);
        if(chunk_pos==0) return false;
        ifs.ignore(6);
        //Совершим необходимые преобразования над вершинами объекта
        float Local[12]={0.0f};
        float x0,x1,x2;
        ifs.read((char*)&Local,sizeof(float)*12);
        for(int i=0;i<_NVertexes;i++)//y и z поменяны местами
        {
            _Vertexes[i].x-=Local[9];
            _Vertexes[i].z-=Local[10];
            _Vertexes[i].y-=Local[11];
            x0=_Vertexes[i].x;
            x1=_Vertexes[i].y;
            x2=_Vertexes[i].z;
            _Vertexes[i].x=Local[0]*x0+Local[2]*x1+Local[1]*x2;
            _Vertexes[i].z=Local[3]*x0+Local[5]*x1+Local[4]*x2;
            _Vertexes[i].y=Local[6]*x0+Local[8]*x1+Local[7]*x2;
        }
        //---Дойдем к данным о материале объекта---
        ifs.seekg(chunk_temppos);
        chunk_pos=_FindChunk(ifs,TRI_FACELIST,true);
        /*
		chunk_pos=_FindChunk(ifs,TRI_MATERIAL,false);
        if(chunk_pos==0) return false;
        ifs.ignore(6);
        //Считаем название первого попавшегося материала
        //(он у нас один для всего объекта)

        //...
		*/
        //Все хорошо - объект считан
		//Рассчитаем нормали
		_ComputeNormals();
        return true;
    }
}

unsigned int CModel3d::_FindChunk(ifstream& ifs, unsigned short id, bool isParent = true)

/* Данная функция получает ссылку на файловый поток, идентификатор искомого блока и
   логическую переменную указывающую как начинается поиск, с родительского блока или
   внутри его. Это нужно для возможности поиска подблоков одного и того же типа
   в одном родительском блоке (в перспективе) */
{
    unsigned short chunk_id;//Идентификатор блока
    unsigned int chunk_len;//Смещение к следующему блоку (от chunk_id)
    //Найдем нужный блок в файле *.3DS
    //Если файловый указатель указывает на родительский chunk, то
    //нужно прочитать заголовочные данные родительского блока
    if(isParent)
    {
        //Читаем идентификатор родительского блока и его длину
        ifs.read((char*)&chunk_id,2);
        ifs.read((char*)&chunk_len,4);
        //Если это блок объекта, то нужно пропустить строку имени объекта
        if(chunk_id==0x4000)
        {
            char ch;
            do
            {
                ifs.read((char*)&ch,1);
            }while(ch!='\0' && !ifs.eof());
        }
    }
    //Начинаем поиск внутри родительского блока
    do
    {
        //Читаем идентифекатор очередного блока и его длинну
        ifs.read((char*)&chunk_id,2);
        ifs.read((char*)&chunk_len,4);
        //Пропускаем все кроме блока объекта
        if(chunk_id!=id) ifs.ignore(chunk_len-6);
        else
        {
            //Вернемся к началу найденого блока и вернем его позицию
            ifs.seekg((int)ifs.tellg()-6);
            return (ifs.tellg());
        }
    }while(!ifs.eof());
    return false;
}
