#pragma once
#include "PVInstance.h"
#include "Enum.h"
#define _USE_MATH_DEFINES
#include <cmath>

#define NEW_BOX_RENDER

class PartInstance : public PVInstance
{
public:
	
	PartInstance(void);
	PartInstance(const PartInstance &oinst);
	Instance* clone() const { return new PartInstance(*this); }
	virtual void PartInstance::postRender(RenderDevice* rd);
	~PartInstance(void);
	virtual void render(RenderDevice*);
	Enum::SurfaceType::Value top;
	Enum::SurfaceType::Value front;
	Enum::SurfaceType::Value right;
	Enum::SurfaceType::Value back;
	Enum::SurfaceType::Value left;
	Enum::SurfaceType::Value bottom;
	Enum::Shape::Value shape;
	CoordinateFrame cFrame;
	Color3 color;
	Vector3 getPosition();
	Vector3 getVelocity();
	Vector3 getRotVelocity();
	void setParent(Instance* parent);
	void setPosition(Vector3);
	void setVelocity(Vector3);
	void setRotVelocity(Vector3);
	CoordinateFrame getCFrame();
	void setCFrame(CoordinateFrame);
	Box getBox();
	Box getScaledBox();
	CoordinateFrame getCFrameRenderBased();
	Vector3 getSize();
	void setSize(Vector3);
	void setShape(Enum::Shape::Value shape);
	bool canCollide;
	bool anchored;
	bool collides(Box);
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
	#ifdef NEW_BOX_RENDER
	void addVertex(Vector3 vertexPos,Color3 color);
	void addNormals(Vector3 normal);
	void addSingularNormal(Vector3 normal);
	void addTriangle(Vector3 vertexPos,Vector3 vertexPos2, Vector3 vertexPos3);
	void addQuad(Vector3 v1,Vector3 v2, Vector3 v3, Vector3 v4);
	void genSmoothNormals(int);
	void addSmoothTriangle(Vector3 vertexPos,Vector3 vertexPos2, Vector3 vertexPos3);
	void makeSmoothFace(int vertex1, int vertex2, int vertex3);
	void addPlus(Vector3 v1);
	void addPlus2(Vector3 v1);
	void debugPrintVertexIDs(RenderDevice* rd, GFontRef font, Matrix3 camRot);
	void makeFace(int vertex1, int vertex2, int vertex3);
	void fromArrays(float verts[], float norms[], float ind[], unsigned int countVN, unsigned int countInd);
	bool isUniqueVertex(Vector3 pos);
	#endif
private:
	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 rotVelocity;
	float	_bevelSize;
	int		_parseVert;
	int		_debugTimer;
	std::vector<Vector3> _debugUniqueVertices;
 	#ifdef NEW_BOX_RENDER
		std::vector<GLfloat> _vertices;
		std::vector<GLfloat> _normals;
	#else
		GLfloat _vertices[96];
	#endif
	std::vector<GLushort> _indices;
	bool changed;
	Box itemBox;
	GLuint glList;
};
