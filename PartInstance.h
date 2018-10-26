#pragma once
#include "PVInstance.h"
#include "Enum.h"

#define NEW_BOX_RENDER

class PartInstance : public PVInstance
{
public:
	PartInstance(void);
	PartInstance(const PartInstance &oinst);
	Instance* clone() const { return new PartInstance(*this); }
	void PartInstance::postRender(RenderDevice* rd);
	~PartInstance(void);
	virtual void render(RenderDevice*);
	Vector3 velocity;
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
	void setPosition(Vector3);
	CoordinateFrame getCFrame();
	void setCFrame(CoordinateFrame);
	Box getBox();
	Box getScaledBox();
	CoordinateFrame getCFrameRenderBased();
	Vector3 getSize();
	void setSize(Vector3);
	bool canCollide;
	bool anchored;
	Vector3 rotVelocity;
	bool collides(Box);
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
	void addVertex(Vector3 vertexPos,Color3 color);
	void addNormals(Vector3 normal);
	void addTriangle(Vector3 vertexPos,Vector3 vertexPos2, Vector3 vertexPos3);
	void debugPrintVertexIDs(RenderDevice* rd, GFontRef font, Matrix3 camRot);
	void makeFace(int vertex1, int vertex2, int vertex3);
	bool isUniqueVertex(Vector3 pos);
private:
	Vector3 position;
	Vector3 size;
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
};
