#include "Renderer.h"
#include <G3DAll.h>
#include "Faces.h"

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
		_vertices.clear();
		_indices.clear();
		_normals.clear();
}


const float square_arr[] = {-0.125F,-0.125F,
							-0.125F, 0.125F,
							 0.125F, 0.125F,
							 0.125F,-0.125F};
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
			glPushMatrix();
			glScalef(size.x, size.y, size.z);
			gluSphere(gluNewQuadric(), 1, 20, 20);
			glPopMatrix();
			break;
		default:
			GLUquadric * q = gluNewQuadric();
			glColor(ncolor);
			glPushMatrix();
			glScalef(size.x, size.y, size.z);
			glRotatef(90, 0, 1, 0);
			glTranslatef(0,0,1);
			gluDisk(q, 0, 1, 12, 12);
			glTranslatef(0,0,-2);
			gluCylinder(q, 1, 1, 2, 12, 1);
			glRotatef(180, 1, 0, 0);
			gluDisk(q, 0, 1, 12, 12);
			glPopMatrix();
			/*Plusses, can possibly integrate into cylinder code later on*/
			glVertexPointer(2, GL_FLOAT,0, square_arr);
			glColor3f(127,127,127);
			glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(0,0,-(size.z+0.001F));
			glScalef(0.75,0.75,0.75);
			glScalef(size.x*8,1,1);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4); 
			glScalef(1/(size.x*8),size.x*8,1);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glPopMatrix();

			glPushMatrix();
			glRotatef(-90,0,1,0);
			glTranslatef(0,0,-(size.z+0.001F));
			glScalef(0.75,0.75,0.75);
			glScalef(size.x*8,1,1);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glScalef(1/(size.x*8),size.x*8,1);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glPopMatrix();
			
	}
}

static G3D::Color3 getControllerColor(int controller)
	{
		switch(controller)
		{
			case Enum::Controller::KeyboardLeft:
				return Color3::red();
			case Enum::Controller::KeyboardRight:
				return Color3::blue();
			case Enum::Controller::Chase:
				return Color3::black();
			case Enum::Controller::Flee:
				return Color3::yellow();
		}
		return Color3::gray();
	}

void translateFace(const char face, const Vector3& size)
{
	//glTranslatef(0,0,size.z);
	switch(face)
	{
	case TOP:
		{
			glTranslatef(0,size.y,0);
			glRotatef(90,1,0,0);
		}
		break;
	case BOTTOM:
		{
			glTranslatef(0,-size.y,0);
			glRotatef(-90,1,0,0);
		}
		break;
	case LEFT:
		{
			glTranslatef(size.x,0,0);
			glRotatef(-90,0,1,0);
		}
		break;
	case RIGHT:
		{
			glTranslatef(-size.x,0,0);
			glRotatef(90,0,1,0);
		}
		break;
	case FRONT:
		{
			glTranslatef(0,0,size.z);
			glRotatef(-180,0,1,0);
		}
		break;
	default:
		{
			glTranslatef(0,0,-size.z);
		}
		break;
	}
}

/*static const GLfloat bump[] = {
    0.5f, 0.25F, 0.5f,     // Front-top-left
    -0.5f, 0.25F, 0.5f,      // Front-top-right
    0.5f, -0.25F, 0.5f,    // Front-bottom-left
    -0.5f, -0.25F, 0.5f,     // Front-bottom-right
    -0.5f, -0.25F, -0.5f,    // Back-bottom-right
    -0.5f, 0.25F, 0.5f,      // Front-top-right
    -0.5f, 0.25F, -0.5f,     // Back-top-right
    0.5f, 0.25F, 0.5f,     // Front-top-left
    0.5f, 0.25F, -0.5f,    // Back-top-left
    0.5f, -0.25F, 0.5f,    // Front-bottom-left
    0.5f, -0.25F, -0.5f,   // Back-bottom-left
    -0.5f, -0.25F, -0.5f,    // Back-bottom-right
    0.5f, 0.25F, -0.5f,    // Back-top-left
    -0.5f, 0.25F, -0.5f      // Back-top-right
};*/

static const int BMP_FACES = 5*2;
static const GLfloat bumpTriangles[] = {
	//Top
    -0.3F, 0.1F, -0.3F,
	-0.3F, 0.1F, 0.3F,
	0.3F, 0.1F, -0.3F,

	0.3F, 0.1F, -0.3F,
	-0.3F, 0.1F, 0.3F,
	0.3F, 0.1F, 0.3F,


	//Front
	-0.3F, 0.1F, 0.3F,
	-0.3F, -0.1F, 0.3F,
	0.3F, 0.1F, 0.3F,
	
	0.3F, 0.1F, 0.3F,
	-0.3F, -0.1F, 0.3F,
	0.3F, -0.1F, 0.3F,


	//Back
	-0.3F, -0.1F, -0.3F,
	-0.3F, 0.1F, -0.3F,
	0.3F, -0.1F, -0.3F,
	
	0.3F, -0.1F, -0.3F,
	-0.3F, 0.1F, -0.3F,
	0.3F, 0.1F, -0.3F,


	//Right
	0.3F, -0.1F, -0.3F,
	0.3F, 0.1F, -0.3F,
	0.3F, -0.1F, 0.3F,
	
	0.3F, -0.1F, 0.3F,
	0.3F, 0.1F, -0.3F,
	0.3F, 0.1F, 0.3F,


	//Left
	-0.3F, 0.1F, -0.3F,
	-0.3F, -0.1F, -0.3F,
	-0.3F, 0.1F, 0.3F,
	
	-0.3F, 0.1F, 0.3F,
	-0.3F, -0.1F, -0.3F,
	-0.3F, -0.1F, 0.3F,
};

static const GLfloat bumpTriangleNormals[] = {
	0.000000F, 1.000000F, 0.000000F,
	0.000000F, 1.000000F, 0.000000F,
	0.000000F, 1.000000F, 0.000000F,
	0.000000F, 1.000000F, -0.000000F,
	-0.000000F, 1.000000F, 0.000000F,
	0.000000F, 1.000000F, 0.000000F,
	-0.000000F, 0.000000F, 1.000000F,
	0.000000F, 0.000000F, 1.000000F,
	0.000000F, 0.000000F, 1.000000F,
	0.000000F, 0.000000F, 1.000000F,
	0.000000F, 0.000000F, 1.000000F,
	0.000000F, -0.000000F, 1.000000F,
	0.000000F, 0.000000F, -1.000000F,
	0.000000F, 0.000000F, -1.000000F,
	0.000000F, 0.000000F, -1.000000F,
	0.000000F, 0.000000F, -1.000000F,
	0.000000F, 0.000000F, -1.000000F,
	-0.000000F, -0.000000F, -1.000000F,
	1.000000F, 0.000000F, 0.000000F,
	1.000000F, 0.000000F, 0.000000F,
	1.000000F, 0.000000F, 0.000000F,
	1.000000F, -0.000000F, 0.000000F,
	1.000000F, 0.000000F, -0.000000F,
	1.000000F, 0.000000F, 0.000000F,
	-1.000000F, 0.000000F, 0.000000F,
	-1.000000F, 0.000000F, 0.000000F,
	-1.000000F, 0.000000F, -0.000000F,
	-1.000000F, -0.000000F, 0.000000F,
	-1.000000F, 0.000000F, 0.000000F,
	-1.000000F, 0.000000F, 0.000000F,
};


void renderSurface(const char face, const Enum::SurfaceType::Value& surface, const Vector3& size, const Enum::Controller::Value& controller, const Color3& nColor)
{
	glPushMatrix();
	translateFace(face, size);
	switch(surface)
	{
	case Enum::SurfaceType::Motor:
		{
			printf("MOTOR\n");
			glDisable(GL_LIGHTING);
			glColor(getControllerColor(controller));
			GLUquadric * q = gluNewQuadric();
			gluQuadricNormals(q, GLU_NONE);
			glPushMatrix();
			glTranslatef(0,0,-0.2F);
			gluCylinder(q, 0.4F, 0.4F, 0.4F, 6, 1);
			glTranslatef(0,0,0.4F);
			gluDisk(q, 0, 0.4F, 6, 1);
			glTranslatef(0,0,-0.4F);
			glRotatef(180, 1, 0, 0);
			gluDisk(q, 0, 0.4F, 6, 1);
			glPopMatrix();
		}
	case Enum::SurfaceType::Hinge:
		{
			glDisable(GL_LIGHTING);
			glColor3f(1,1,0);
			GLUquadric * q = gluNewQuadric();
			gluQuadricNormals(q, GLU_NONE);
			glPushMatrix();	
			glTranslatef(0,0,-0.5F);
			gluCylinder(q, 0.2F, 0.2F, 1, 6, 1);
			glTranslatef(0,0,1);
			gluDisk(q, 0, 0.2F, 6, 1);
			glTranslatef(0,0,-1);
			glRotatef(180, 1, 0, 0);
			gluDisk(q, 0, 0.2F, 6, 1);
			glPopMatrix();
			glEnable(GL_LIGHTING);
		}
	break;
	case Enum::SurfaceType::Bumps:
		{
			glRotatef(-90,1,0,0);
			float x;
			float y;
			switch(face)
			{
				case TOP:
				case BOTTOM:
					x = size.x * 2;
					y = size.z * 2;
					break;
				case LEFT:
				case RIGHT:
					y = size.y * 2;
					x = size.z * 2;
					break;
				case FRONT:
				case BACK:
					x = size.x * 2;
					y = size.y * 2;
					break;
			}
			glTranslatef(-x/2+0.5F,0,-y/2+0.5F);
			glColor(color);
			glDisableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, bumpTriangles);
			glNormalPointer(GL_FLOAT, 0, bumpTriangleNormals);
			for(float i = 0; i < y; i++)
			{
				glPushMatrix();
				for(float j = 0; j < x; j++)
				{
					glDrawArrays(GL_TRIANGLES, 0, 30);
					glTranslatef(1,0,0);
				}
				glPopMatrix();
				glTranslatef(0,0,1);
			}
			glEnableClientState(GL_COLOR_ARRAY);
		}
	break;
	default:
		break;
	}
	glPopMatrix();
}