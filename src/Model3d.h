#ifndef _MODEL3D_H
#define _MODEL3D_H

#include <string>
#include "CommonStructs.h"
#include "glfw.h"

using namespace std;
class CModel3d
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
public:
	CModel3d(void);
	~CModel3d(void);
	void Draw(TVector3d);
	void Draw();
	bool LoadFrom3ds(string);
	void SetColor(float,float,float,float);
private:
	bool _LoadTextureFromFile(string);
	unsigned int _FindChunk(ifstream&, unsigned short, bool);
	void _ComputeNormals();
};

#endif //_MODEL3D_H
