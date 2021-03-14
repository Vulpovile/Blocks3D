#include "Renderer.h"
#include <G3DAll.h>

float _bevelSize = 0.07F;
std::vector<Vector3> _debugUniqueVertices;
std::vector<GLfloat> _vertices;
std::vector<GLfloat> _normals;
std::vector<GLushort> _indices;
Color3 color;

void addVertex(const Vector3& vertexPos,const Color3& color)
{
	_vertices.push_back(vertexPos.x);
	_vertices.push_back(vertexPos.y);
	_vertices.push_back(vertexPos.z);
	_vertices.push_back(color.r);
	_vertices.push_back(color.g);
	_vertices.push_back(color.b);
}
 void addNormals(const Vector3& normal)
{
	for (unsigned int i=0;i<3;i+=1) {
		_normals.push_back(normal.x);
		_normals.push_back(normal.y);
		_normals.push_back(normal.z);
	}
}
 void addSingularNormal(const Vector3& normal)
{
		_normals.push_back(normal.x);
		_normals.push_back(normal.y);
		_normals.push_back(normal.z);
}
 void addTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	addVertex(v1,color);
	addVertex(v2,color);
	addVertex(v3,color);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(v3-v2,v1-v2).direction());
	addSingularNormal(cross(v1-v3,v2-v3).direction());
}

void addQuad(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4)
{
	addTriangle(v1, v2, v3);
	addTriangle(v1, v3, v4);
}

void makeFace(int vertex1,int vertex2, int vertex3)
{
	addTriangle(Vector3(_vertices[vertex1],_vertices[vertex1+1],_vertices[vertex1+2]),
		Vector3(_vertices[vertex2],_vertices[vertex2+1],_vertices[vertex2+2]),
		Vector3(_vertices[vertex3],_vertices[vertex3+1],_vertices[vertex3+2]));
}

void renderBlock(const Vector3& renderSize)
{
	_vertices.clear();
	_indices.clear();
	_normals.clear();
	addTriangle(Vector3(renderSize.x-_bevelSize,renderSize.y-_bevelSize,renderSize.z),
					Vector3(-renderSize.x+_bevelSize,-renderSize.y+_bevelSize,renderSize.z),
					Vector3(renderSize.x-_bevelSize,-renderSize.y+_bevelSize,renderSize.z)
					);

				addTriangle(Vector3(-renderSize.x+_bevelSize,renderSize.y-_bevelSize,renderSize.z),
					Vector3(-renderSize.x+_bevelSize,-renderSize.y+_bevelSize,renderSize.z),
					Vector3(renderSize.x-_bevelSize,renderSize.y-_bevelSize,renderSize.z)
					);

				// Top
				addTriangle(Vector3(renderSize.x-_bevelSize,renderSize.y,renderSize.z-_bevelSize),
					Vector3(renderSize.x-_bevelSize,renderSize.y,-renderSize.z+_bevelSize),
					Vector3(-renderSize.x+_bevelSize,renderSize.y,renderSize.z-_bevelSize)
					);
				addTriangle(Vector3(-renderSize.x+_bevelSize,renderSize.y,renderSize.z-_bevelSize),
					Vector3(renderSize.x-_bevelSize,renderSize.y,-renderSize.z+_bevelSize),
					Vector3(-renderSize.x+_bevelSize,renderSize.y,-renderSize.z+_bevelSize)
					);

				// Back
				addTriangle(Vector3(renderSize.x-_bevelSize,renderSize.y-_bevelSize,-renderSize.z),
					Vector3(renderSize.x-_bevelSize,-renderSize.y+_bevelSize,-renderSize.z),
					Vector3(-renderSize.x+_bevelSize,-renderSize.y+_bevelSize,-renderSize.z)
					);
				addTriangle(Vector3(renderSize.x-_bevelSize,renderSize.y-_bevelSize,-renderSize.z),
					Vector3(-renderSize.x+_bevelSize,-renderSize.y+_bevelSize,-renderSize.z),
					Vector3(-renderSize.x+_bevelSize,renderSize.y-_bevelSize,-renderSize.z)
					);

				// Bottom
				addTriangle(Vector3(renderSize.x-_bevelSize,-renderSize.y,-renderSize.z+_bevelSize),
					Vector3(renderSize.x-_bevelSize,-renderSize.y,renderSize.z-_bevelSize),
					Vector3(-renderSize.x+_bevelSize,-renderSize.y,renderSize.z-_bevelSize)
					);
				addTriangle(Vector3(-renderSize.x+_bevelSize,-renderSize.y,renderSize.z-_bevelSize),
					Vector3(-renderSize.x+_bevelSize,-renderSize.y,-renderSize.z+_bevelSize),
					Vector3(renderSize.x-_bevelSize,-renderSize.y,-renderSize.z+_bevelSize)
					);
 				// Left
				addTriangle(Vector3(-renderSize.x,renderSize.y-_bevelSize,-renderSize.z+_bevelSize),
					Vector3(-renderSize.x,-renderSize.y+_bevelSize,renderSize.z-_bevelSize),
					Vector3(-renderSize.x,renderSize.y-_bevelSize,renderSize.z-_bevelSize)
					);
				addTriangle(Vector3(-renderSize.x,-renderSize.y+_bevelSize,renderSize.z-_bevelSize),
					Vector3(-renderSize.x,renderSize.y-_bevelSize,-renderSize.z+_bevelSize),
					Vector3(-renderSize.x,-renderSize.y+_bevelSize,-renderSize.z+_bevelSize)
					);

 				// Right
				addTriangle(Vector3(renderSize.x,renderSize.y-_bevelSize,renderSize.z-_bevelSize),
					Vector3(renderSize.x,-renderSize.y+_bevelSize,renderSize.z-_bevelSize),
					Vector3(renderSize.x,renderSize.y-_bevelSize,-renderSize.z+_bevelSize)
					);
				addTriangle(Vector3(renderSize.x,-renderSize.y+_bevelSize,-renderSize.z+_bevelSize),
					Vector3(renderSize.x,renderSize.y-_bevelSize,-renderSize.z+_bevelSize),
					Vector3(renderSize.x,-renderSize.y+_bevelSize,renderSize.z-_bevelSize)
					);


 				// Bevel Top Front
				makeFace(0,36,48);
				makeFace(48,18,0);
 				// Bevel Left Front Corner
				makeFace(18,156,162);
				makeFace(24,18,162);
 				// Bevel Left Front Top Corner
				makeFace(48,156,18);
 				// Bevel Left Front Bottom Corner
				makeFace(120,6,150);
 				// Bevel Left Top
				makeFace(48,66,156);
				makeFace(144,156,66);
 				// Bevel Bottom
				makeFace(6,120,114);
				makeFace(114,12,6);
 				// Left Bottom
				makeFace(120,150,174);
				makeFace(174,132,120);
 				// Right Front Top Corner
				makeFace(36,0,180);
 				// Right Front Corner
				makeFace(180,0,12);
				makeFace(186,180,12);
 				// Right Front Bottom Corner
				makeFace(186,12,114);
 				// Right Bottom
				makeFace(186,114,108);
				makeFace(108,198,186);
 				// Right Top Corner
				makeFace(180,192,36);
				makeFace(192,42,36);
 				// Right Back Top Corner
				makeFace(72,42,192);
 				// Right Back Bottom Corner
				makeFace(78,198,108);
 				// Right Back Corner
				makeFace(72,192,198);
				makeFace(198,78,72);
 				// Back Bottom Corner
				makeFace(78,108,132);
				makeFace(132,84,78);
 				// Back Top
				makeFace(42,72,102);
				makeFace(102,66,42);
 				// Back Left Top Corner
				makeFace(144,66,102);
 				// Back Left Corner
				makeFace(144,102,84);
				makeFace(84,174,144);
 				// Back Left Bottom Corner
				makeFace(174,84,132);
				for (unsigned short i=0;i<_vertices.size()/6;i++) {
					_indices.push_back(i);
				}

		glVertexPointer(3, GL_FLOAT,6 * sizeof(GLfloat), &_vertices[0]);
		glColorPointer(3, GL_FLOAT,6 * sizeof(GLfloat), &_vertices[3]);
		glNormalPointer(GL_FLOAT,3 * sizeof(GLfloat), &_normals[0]);
		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_SHORT, &_indices[0]);
}

void renderShape(const Enum::Shape::Value& shape, const Vector3& size, const Color3& ncolor)
{
	color = ncolor;
	switch(shape)
	{
		case Enum::Shape::Block:
			renderBlock(size);
			break;
		case Enum::Shape::Ball:
			glColor(ncolor);
			glScalef(size.x, size.y, size.z);
			gluSphere(gluNewQuadric(), 1, 20, 20);
			break;
		default:
			glColor(ncolor);
			glScalef(size.x, size.y, size.z);
			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0,0,1);
			gluDisk(gluNewQuadric(), 0, 1, 12, 12);
			glTranslatef(0,0,-2);
			gluCylinder(gluNewQuadric(), 1, 1, 2, 12, 1);
			glRotatef(180, 1, 0, 0);
			gluDisk(gluNewQuadric(), 0, 1, 12, 12);
			glPopMatrix();
	}
}