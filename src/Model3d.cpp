#include "Model3d.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

CMesh::CMesh(void)
	:_Vertexes(NULL), _TexCoords(NULL), _Triangles(NULL), _Normals(NULL), _LoadedSuccsessfull(false)
{
	SetColor(1,1,1,1);
}

HRESULT CMesh::Draw(TVector3d Position, float ZAngle)
{
    //TODO: Проверить правильность работы.
    glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
    glRotatef(ZAngle, 0, 0, 1);
	Draw();
    glPopMatrix();
    return H_OK;
}

HRESULT CMesh::SetTexture(ITexture *Texture)
{
    _Texture = Texture;
    return H_OK;
}

HRESULT CMesh::LoadFromFile(char *FileName)
{
    if (strcmp("3ds", GetExtencion(FileName)))
        _LoadFrom3ds(FileName);
    return H_OK;
}


HRESULT CMesh::GetType(E_RESOURCE_TYPE &Type)
{
    Type = RT_MESH;
    return H_OK;
}

void CMesh::SetColor(float R,float G,float B, float A)
{
	_Color.r=R;
	_Color.g=G;
	_Color.b=B;
	_Color.a=A;
}

CMesh::~CMesh(void)
{
	if(_Vertexes)	delete[] _Vertexes;
	if(_TexCoords)	delete[] _TexCoords;
	if(_Triangles)	delete[] _Triangles;
	if(_Normals)	delete[] _Normals;
}

HRESULT CMesh::Draw(TVector3d vector)
{
    glPushMatrix();
	glTranslatef(vector.x,vector.y,vector.z);
	Draw();
    glPopMatrix();
	return H_OK;
}

const char *CMesh::GetFileName()
{
	return _FileName;
}

HRESULT CMesh::Draw()
{
	if (!_LoadedSuccsessfull)
	{
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex3f(0.0,0.0,0.0);
		glEnd();
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		_Texture->BindTexture();
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
		glDisable(GL_TEXTURE_2D);
	}
    return H_OK;
}

void CMesh::_ComputeNormals()
{
	TVector3d vVector1, vVector2, vNormal, vPoly[3];

	TVector3d	*pTempNormals	= new TVector3d [_NTriangles];
	if(_Normals) delete[] _Normals;
	_Normals = new TVector3d [_NVertexes];

	for(int i=0; i < _NTriangles; i++)
	{
		vPoly[0] = _Vertexes[_Triangles[i].v0];
		vPoly[1] = _Vertexes[_Triangles[i].v1];
		vPoly[2] = _Vertexes[_Triangles[i].v2];
		vVector1 = vPoly[0] - vPoly[2];
		vVector2 = vPoly[1] - vPoly[2];
		vNormal  = vVector1 * vVector2;
		pTempNormals[i] = vNormal;
	}

	TVector3d vSum = {0.0, 0.0, 0.0};
	TVector3d vZero = vSum;
	int iShared=0;

	for (int i = 0; i < _NVertexes; i++)
	{
		for (int j = 0; j < _NTriangles; j++)
		{
			if (_Triangles[j].v0 == i || _Triangles[j].v1 == i || _Triangles[j].v2 == i)
			{
			vSum = vSum + pTempNormals[j];
			iShared++;
			}
		}
		_Normals[i] = vSum / float(-iShared);
		_Normals[i].Normalize();
		vSum = vZero;
		iShared = 0;
	}

	delete [] pTempNormals;
}

bool CMesh::_LoadFrom3ds(string FileName)
{
	const int CHUNK_HEADER_LENGTH = 6;

	const int MAIN3DS				=0x4D4D;
	const int EDIT3DS				=0x3D3D;
	const int EDIT_OBJECT			=0x4000;
	const int OBJ_TRIMESH			=0x4100;
	const int TRI_VERTEXLIST		=0x4110;
	const int TRI_MAPPINGCOORS		=0x4140;
	const int TRI_FACELIST			=0x4120;
	const int TRI_LOCAL             =0x4160;

	uint16      usChunkID;
	uint32      uiChunkPosition;
	uint32      uiChunkTempPosition;
	uint        uiChunkLength;


	_LoadedSuccsessfull = false;

	ifstream InputStream;
	InputStream.open(FileName.c_str(),ios::in | ios::binary);
	//if(!InputStream.is_open()) throw new CFileNotFoundException(1, FileName);

	//Free if it is not first loading
	if(_Vertexes) delete[] _Vertexes;
	if(_TexCoords) delete[] _TexCoords;
	if(_Triangles) delete[] _Triangles;

	InputStream.read((char*)&usChunkID,2);
	InputStream.read((char*)&uiChunkLength,4);
	//if(usChunkID != MAIN3DS) throw new CChunkNotFoundException(MAIN3DS, FileName);

	InputStream.seekg((int)InputStream.tellg()-CHUNK_HEADER_LENGTH);
	uiChunkPosition = _FindChunk(InputStream,EDIT3DS,true);
	//if(uiChunkPosition == 0) throw new CChunkNotFoundException(EDIT3DS, FileName);

	uiChunkPosition = _FindChunk(InputStream,EDIT_OBJECT,true);
	//if (uiChunkPosition == 0) throw new CChunkNotFoundException(EDIT_OBJECT, FileName);
	uiChunkPosition = _FindChunk(InputStream,OBJ_TRIMESH,true);
	//if (uiChunkPosition == 0) throw new CChunkNotFoundException(OBJ_TRIMESH, FileName);

	//Remember chunk position
	uiChunkTempPosition = uiChunkPosition;

	//Reading vertexes
	uiChunkPosition = _FindChunk(InputStream,TRI_VERTEXLIST,true);
	//if (uiChunkPosition == 0) throw new CChunkNotFoundException(TRI_VERTEXLIST, FileName);
	InputStream.ignore(6);
	InputStream.read((char*)&_NVertexes,2);
	_Vertexes = new TVector3d[_NVertexes];
	InputStream.read((char*)(_Vertexes),_NVertexes*3*4);
	InputStream.seekg(uiChunkTempPosition);

	//Reading texture coords
	uiChunkPosition = _FindChunk(InputStream,TRI_MAPPINGCOORS,true);
	//if (uiChunkPosition == 0) throw new CChunkNotFoundException(TRI_MAPPINGCOORS, FileName);
	InputStream.ignore(6);
	unsigned short nTexCoords;
	InputStream.read((char*)&nTexCoords,2);
	_TexCoords = new TVector2d[nTexCoords];
	InputStream.read((char*)(_TexCoords),nTexCoords*2*4);
	InputStream.seekg(uiChunkTempPosition);

	//Reading faces
	uiChunkPosition = _FindChunk(InputStream,TRI_FACELIST,true);
	//if (uiChunkPosition == 0) throw new CChunkNotFoundException(TRI_FACELIST, FileName);
	InputStream.ignore(6);
	InputStream.read((char*)&_NTriangles,2);
	_Triangles = new TFace3D[_NTriangles];
	for(int i = 0;i < _NTriangles;i++)
	{
		InputStream.read((char*)&(_Triangles[i]),6);
		InputStream.ignore(2);
	}
	InputStream.seekg(uiChunkTempPosition);
/*
	//Reading local coordinate system
	uiChunkPosition = _FindChunk(InputStream,TRI_LOCAL,true);
	//if (uiChunkPosition == 0) throw new CChunkNotFoundException(TRI_LOCAL, FileName);
	InputStream.ignore(6);
	float Local[12] = {0.0f};
	float x0,x1,x2;
	InputStream.read((char*)&Local,sizeof(float)*12);
	for(int i=0;i<_NVertexes;i++)
	{
		_Vertexes[i].x -= Local[9];
		_Vertexes[i].y -= Local[10];
		_Vertexes[i].z -= Local[11];
		x0 = _Vertexes[i].x;
		x1 = _Vertexes[i].y;
		x2 = _Vertexes[i].z;
		_Vertexes[i].x = Local[0]*x0+Local[2]*x1+Local[1]*x2;
		_Vertexes[i].y = Local[3]*x0+Local[5]*x1+Local[4]*x2;
		_Vertexes[i].z = Local[6]*x0+Local[8]*x1+Local[7]*x2;
	}
*/
	_ComputeNormals();
	_FileName = FileName.c_str();
	_LoadedSuccsessfull = true;
	return true;
}

uint32 CMesh::_FindChunk(ifstream& InputStream, unsigned short id, bool isParent = true)
{
	const int EDIT_OBJECT =0x4000;
	unsigned short usChunkID;
	unsigned int uiChunkLength;
	if(isParent)
	{
		InputStream.read((char*)&usChunkID,2);
		InputStream.read((char*)&uiChunkLength,4);
		if(usChunkID==EDIT_OBJECT)
		{
			//Skip object name
			char ch;
			do
			{
				InputStream.read((char*)&ch,1);
			}while(ch!='\0' && !InputStream.eof());
		}
	}

	do
	{
		InputStream.read((char*)&usChunkID,2);
		InputStream.read((char*)&uiChunkLength,4);
		if(usChunkID!=id)
            InputStream.seekg((int)InputStream.tellg()+uiChunkLength-6);
		else
		{
			InputStream.seekg((int)InputStream.tellg()-6);
			return (InputStream.tellg());
		}
	}while(!InputStream.eof());
	return false;
}
