#include "Model3d.h"
#include <fstream>
#include <iostream>

CModel3d::CModel3d(void)
	:_Vertexes(NULL), _TexCoords(NULL), _Triangles(NULL), _Normals(NULL), _LoadedSuccsessfull(false)
{
	SetColor(1,1,1,1);
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
	if(_Vertexes)	delete[] _Vertexes;
	if(_TexCoords)	delete[] _TexCoords;
	if(_Triangles)	delete[] _Triangles;
	if(_Normals)	delete[] _Normals;
}

void CModel3d::Draw(TVector3d vector)
{
	glTranslatef(vector.x,vector.y,vector.z);
	Draw();
}

const char *CModel3d::GetFileName()
{
	return _FileName;
}

void CModel3d::Draw()
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
		glBindTexture(GL_TEXTURE_2D,_Texture);
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
}

void CModel3d::_ComputeNormals()
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

bool CModel3d::LoadFrom3ds(string FileName)
{
	const int CHUNK_HEADER_LENGTH = 6;

	const int MAIN3DS				=0x4D4D;
	const int EDIT3DS				=0x3D3D;
	const int EDIT_OBJECT			=0x4000;
	const int OBJ_TRIMESH			=0x4100;
	const int TRI_VERTEXLIST		=0x4110;
	const int TRI_VERTEXOPTIONS	=0x4111;
	const int TRI_MAPPINGCOORS		=0x4140;
	const int TRI_MAPPINGSTANDARD	=0x4170;
	const int TRI_FACELIST			=0x4120;
	const int TRI_SMOOTH			=0x4150;
	const int EDIT_MATERIAL		=0xAFFF;
	const int CHUNK_MATNAME		=0xA000;
    const int CHUNK_TEXTURE		=0xA200;
    const int CHUNK_TEXTURE_FILE	=0xA300;
	const int TRI_MATERIAL			=0x4130;
	const int TRI_LOCAL			=0x4160;
	const int TRI_VISIBLE			=0x4165;

	unsigned short	usChunkID;
	unsigned int		uiChunkPosition;
	unsigned int		uiChunkTempPosition;
	unsigned int		uiChunkLength;


	_LoadedSuccsessfull = false;

	ifstream InputStream;
	InputStream.open(FileName.c_str(),ios::in);
	if(!InputStream.is_open()) throw new CFileNotFoundException(1, FileName);

	//Free if it is not first loading
	if(_Vertexes) delete[] _Vertexes;
	if(_TexCoords) delete[] _TexCoords;
	if(_Triangles) delete[] _Triangles;

	InputStream.read((char*)&usChunkID,2);
	InputStream.read((char*)&uiChunkLength,4);
	if(usChunkID != MAIN3DS) throw new CChunkNotFoundException(MAIN3DS, FileName);

	InputStream.seekg((int)InputStream.tellg()-CHUNK_HEADER_LENGTH);
	uiChunkPosition = _FindChunk(InputStream,EDIT3DS,true);
	if(uiChunkPosition == 0) throw new CChunkNotFoundException(EDIT3DS, FileName);

	//Remember chunk position
	uiChunkTempPosition = uiChunkPosition;
	//Loading texture
	uiChunkPosition = _FindChunk(InputStream,EDIT_MATERIAL,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(EDIT_MATERIAL, FileName);

	uiChunkPosition = _FindChunk(InputStream,CHUNK_TEXTURE,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(CHUNK_TEXTURE, FileName);

	uiChunkPosition = _FindChunk(InputStream,CHUNK_TEXTURE_FILE,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(CHUNK_TEXTURE_FILE, FileName);

	InputStream.ignore(2);
	InputStream.read((char*)&uiChunkLength,4);
	char *cTextureFileName = new char[uiChunkLength - 6];
	InputStream.read((char*)cTextureFileName,uiChunkLength);
	_LoadTextureFromFile((string)"models/textures/"+(string)cTextureFileName);
	InputStream.seekg(uiChunkTempPosition);
	delete cTextureFileName;


	uiChunkPosition = _FindChunk(InputStream,EDIT_OBJECT,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(EDIT_OBJECT, FileName);
	uiChunkPosition = _FindChunk(InputStream,OBJ_TRIMESH,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(OBJ_TRIMESH, FileName);

	//Remember chunk position
	uiChunkTempPosition = uiChunkPosition;

	//Reading vertexes
	uiChunkPosition = _FindChunk(InputStream,TRI_VERTEXLIST,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(TRI_VERTEXLIST, FileName);
	InputStream.ignore(6);
	InputStream.read((char*)&_NVertexes,2);
	_Vertexes = new TVector3d[_NVertexes];
	InputStream.read((char*)(_Vertexes),_NVertexes*3*4);
	InputStream.seekg(uiChunkTempPosition);

	//Reading texture coords
	uiChunkPosition = _FindChunk(InputStream,TRI_MAPPINGCOORS,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(TRI_MAPPINGCOORS, FileName);
	InputStream.ignore(6);
	unsigned short nTexCoords;
	InputStream.read((char*)&nTexCoords,2);
	_TexCoords = new TVector2d[nTexCoords];
	InputStream.read((char*)(_TexCoords),nTexCoords*2*4);
	InputStream.seekg(uiChunkTempPosition);

	//Reading faces
	uiChunkPosition = _FindChunk(InputStream,TRI_FACELIST,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(TRI_FACELIST, FileName);
	InputStream.ignore(6);
	InputStream.read((char*)&_NTriangles,2);
	_Triangles = new TFace3D[_NTriangles];
	for(int i = 0;i < _NTriangles;i++)
	{
		InputStream.read((char*)&(_Triangles[i]),6);
		InputStream.ignore(2);
	}
	InputStream.seekg(uiChunkTempPosition);

	//Reading local coordinate system
	uiChunkPosition = _FindChunk(InputStream,TRI_LOCAL,true);
	if (uiChunkPosition == 0) throw new CChunkNotFoundException(TRI_LOCAL, FileName);
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
	_ComputeNormals();
	_FileName = FileName.c_str();
	_LoadedSuccsessfull = true;
	return true;
}

bool CModel3d::_LoadTextureFromFile(string TextureName)
{
	glGenTextures(1,&_Texture);
	glBindTexture(GL_TEXTURE_2D,_Texture);
	if(!glfwLoadTexture2D(TextureName.c_str(), GLFW_BUILD_MIPMAPS_BIT))
		return false;
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	};
	return true;
}

unsigned int CModel3d::_FindChunk(ifstream& InputStream, unsigned short id, bool isParent = true)
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
		if(usChunkID!=id) InputStream.ignore(uiChunkLength-6);
		else
		{
			InputStream.seekg((int)InputStream.tellg()-6);
			return (InputStream.tellg());
		}
	}while(!InputStream.eof());
	return false;
}
