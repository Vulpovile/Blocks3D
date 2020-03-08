#include "PartInstance.h"
#include "Globals.h"
#include <sstream>
#include <iomanip>


PartInstance::PartInstance(void) : _bevelSize(0.07f), _parseVert(0), _debugTimer(0)
{
	PVInstance::PVInstance();
    glList = glGenLists(1);
	name = "Unnamed PVItem";
	className = "Part";
	canCollide = true;
	anchored = false;
	size = Vector3(2,1,4);
	setCFrame(CoordinateFrame(Vector3(0,0,0)));
	color = Color3::gray();
	velocity = Vector3(0,0,0);
	rotVelocity = Vector3(0,0,0);
	top = Enum::SurfaceType::Smooth;
    front = Enum::SurfaceType::Smooth;
    right = Enum::SurfaceType::Smooth;
	back = Enum::SurfaceType::Smooth;
	left = Enum::SurfaceType::Smooth;
	bottom = Enum::SurfaceType::Smooth;
	shape = Enum::Shape::Block;
}


Vector3 PartInstance::getVelocity()
{
	return velocity;
}
Vector3 PartInstance::getRotVelocity()
{
	return rotVelocity;
}

void PartInstance::setVelocity(Vector3 v)
{
	velocity = v;
}
void PartInstance::setRotVelocity(Vector3 v)
{
	rotVelocity = v;
}

void PartInstance::postRender(RenderDevice *rd)
{
	if(!nameShown)
		return;
	G3D::GFontRef fnt = NULL;
	Instance* dm = parent;
	while(dm != NULL)
	{
		if(DataModelInstance* mod = dynamic_cast<DataModelInstance*>(dm))
		{
			fnt = mod->font;
			break;
		}
		dm = dm->getParent();
	}
	if(!fnt.isNull())
	{
		Vector3 gamepoint = position + Vector3(0,1.5,0);
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 100 && distance > -100)
		{
			if(distance < 0)
			distance = distance*-1;
			glDisable(GL_DEPTH_TEST); 
			fnt->draw3D(rd, name, CoordinateFrame(rd->getCameraToWorldMatrix().rotation, gamepoint), 0.03*distance, Color3::yellow(), Color3::black(), G3D::GFont::XALIGN_CENTER, G3D::GFont::YALIGN_CENTER);
			glEnable(GL_DEPTH_TEST); 
		}
	}
}

void PartInstance::setParent(Instance* parent)
{
	Instance * cparent = this->parent;
	while(cparent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(parent))
		{
			workspace->partObjects.erase(std::remove(workspace->partObjects.begin(), workspace->partObjects.end(), this), workspace->partObjects.end());
			break;
		}
		cparent = cparent->getParent();
	}
	Instance::setParent(parent);
	while(parent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(parent))
		{
			workspace->partObjects.push_back(this);
			break;
		}
		parent = parent->getParent();
	}
}

PartInstance::PartInstance(const PartInstance &oinst)  : _bevelSize(0.07f), _parseVert(0), _debugTimer(0)
{
	PVInstance::PVInstance(oinst);
	glList = glGenLists(1);
	//name = oinst.name;
	//className = "Part";
	name = oinst.name;
	canCollide = oinst.canCollide;
	setParent(oinst.parent);
	anchored = oinst.anchored;
	size = oinst.size;
	setCFrame(oinst.cFrame);
	color = oinst.color;
	velocity = oinst.velocity;
	rotVelocity = oinst.rotVelocity;
	top = oinst.top;
	front = oinst.front;
	right = oinst.right;
	back = oinst.back;
	left = oinst.left;
	bottom = oinst.bottom;
	shape = oinst.shape;
	changed = true;
}

void PartInstance::setSize(Vector3 newSize)
{
	int minsize = 1;
	int maxsize = 512;
	changed = true;
	int sizex = (int)newSize.x;
	if(sizex <= 0)
		sizex = 1;
	if(sizex > 512)
		sizex = 512;

	int sizey = (int)newSize.y;
	if(sizey <= 0)
		sizey = 1;
	if(sizey > 512)
		sizey = 512;

	int sizez = (int)newSize.z;
	if(sizez <= 0)
		sizez = 1;
	if(sizez > 512)
		sizez = 512;

	if(shape != Enum::Shape::Block)
	{
		int max = sizex;
		if(sizey > max)
			max = sizey;
		if(sizez > max)
			max = sizez;
		sizex = sizey = sizez = max;
	}

	size = Vector3(sizex, sizey, sizez);



}
Vector3 PartInstance::getSize()
{
	return size;
}
Vector3 PartInstance::getPosition()
{
	return position;
}
void PartInstance::setShape(Enum::Shape::Value shape)
{
	switch(shape)
	{
	case Enum::Shape::Block:
		this->shape = shape;
		break;
	default:
		this->shape = shape;
		this->setSize(this->getSize());
	}
	changed = true;
}

void PartInstance::setPosition(Vector3 pos)
{
	position = pos;
	cFrame = CoordinateFrame(cFrame.rotation, pos);
	changed = true;
}

CoordinateFrame PartInstance::getCFrame()
{
	return cFrame;
}
void PartInstance::setCFrame(CoordinateFrame coordinateFrame)
{
	cFrame = coordinateFrame;
	position = coordinateFrame.translation;
	changed = true;
}
// Can probably be deleted
CoordinateFrame PartInstance::getCFrameRenderBased()
{
	return CoordinateFrame(getCFrame().rotation,Vector3(getCFrame().translation.x, getCFrame().translation.y, getCFrame().translation.z));
}
#ifdef NEW_BOX_RENDER
Box PartInstance::getBox()
{	
	Box box = Box(Vector3(size.x/2, size.y/2, size.z/2) ,Vector3(-size.x/2,-size.y/2,-size.z/2));
	CoordinateFrame c = getCFrameRenderBased();
	itemBox = c.toWorldSpace(box);
	return itemBox;
}
#else
Box PartInstance::getBox()
{
	if(changed)
	{
		Box box = Box(Vector3(0+size.x/4, 0+size.y/4, 0+size.z/4) ,Vector3(0-size.x/4,0-size.y/4,0-size.z/4));
		CoordinateFrame c = getCFrameRenderBased();
		itemBox = c.toWorldSpace(box);
		Vector3 v0,v1,v2,v3;
		for (int f = 0; f < 6; f++) {
			itemBox.getFaceCorners(f, v0,v1,v2,v3);
			_vertices[f*16] = v0.x;
			_vertices[(f*16)+1] = v0.y;
			_vertices[(f*16)+2] = v0.z;
			_vertices[(f*16)+3] = v1.x;
			_vertices[(f*16)+4] = v1.y;
			_vertices[(f*16)+5] = v1.z;
			_vertices[(f*16)+6] = v2.x;
			_vertices[(f*16)+7] = v2.y;
			_vertices[(f*16)+8] = v2.z;
			_vertices[(f*16)+9] = v3.x;
			_vertices[(f*16)+10] = v3.y;
			_vertices[(f*16)+11] = v3.z;
			_vertices[(f*16)+12] = color.r;
			_vertices[(f*16)+13] = color.g;
			_vertices[(f*16)+14] = color.b;
			_vertices[(f*16)+15] = 1;
		}
	}
	return itemBox;
}
#endif

bool PartInstance::collides(Box box)
{
	return CollisionDetection::fixedSolidBoxIntersectsFixedSolidBox(getBox(), box);
}
#ifdef NEW_BOX_RENDER
void PartInstance::addVertex(Vector3 vertexPos,Color3 color)
{
	_vertices.push_back(vertexPos.x);
	_vertices.push_back(vertexPos.y);
	_vertices.push_back(vertexPos.z);
	_vertices.push_back(color.r);
	_vertices.push_back(color.g);
	_vertices.push_back(color.b);
}
 void PartInstance::addNormals(Vector3 normal)
{
	for (unsigned int i=0;i<3;i+=1) {
		_normals.push_back(normal.x);
		_normals.push_back(normal.y);
		_normals.push_back(normal.z);
	}
}
 void PartInstance::addSingularNormal(Vector3 normal)
{
		_normals.push_back(normal.x);
		_normals.push_back(normal.y);
		_normals.push_back(normal.z);
}
 void PartInstance::addTriangle(Vector3 v1,Vector3 v2,Vector3 v3)
{
	addVertex(v1,color);
	addVertex(v2,color);
	addVertex(v3,color);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(v3-v2,v1-v2).direction());
	addSingularNormal(cross(v1-v3,v2-v3).direction());
}

void PartInstance::addQuad(Vector3 v1,Vector3 v2, Vector3 v3, Vector3 v4)
{
	addTriangle(v1, v2, v3);
	addTriangle(v1, v3, v4);
}

void PartInstance::genSmoothNormals(int count = -1)
{
	if(count < 0)
	{
		
	}
}

void PartInstance::addSmoothTriangle(Vector3 v1, Vector3 v2, Vector3 v3)
{
	addVertex(v1,color);
	addVertex(v2,color);
	addVertex(v3,color);
	//addNormals(cross(v2-v1,v3-v1).direction());
	//addSingularNormal(Vector3(cross(v2-v1,v3-v1) + cross(v3-v2,v1-v2) + cross(v1-v3,v2-v3)).direction());
	addSingularNormal(v1.direction());
	addSingularNormal(v2.direction());
	addSingularNormal(v3.direction());
}


void PartInstance::addPlus(Vector3 v1)
{
	float renderY = max(size.z, max(size.x, size.y))/2 * 0.775;
	Vector3 vx1 = v1 + Vector3(0, -renderY, -0.1f);
	Vector3 vx2 = v1 + Vector3(0, -renderY, 0.1f);
	Vector3 vx3 = v1 + Vector3(0, renderY, 0.1f);
	
	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx1 = v1 + Vector3(0, renderY, 0.1f);
	vx2 = v1 + Vector3(0, renderY, -0.1f);
	vx3 = v1 + Vector3(0, -renderY, -0.1f);
	
	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx3 = v1 + Vector3(0, -0.1f, -renderY);
	vx2 = v1 + Vector3(0, 0.1f, -renderY);
	vx1 = v1 + Vector3(0, 0.1f, renderY);
	
	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx3 = v1 + Vector3(0, 0.1f, renderY);
	vx2 = v1 + Vector3(0, -0.1f, renderY);
	vx1 = v1 + Vector3(0, -0.1f, -renderY);
	
	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());
	
}


void PartInstance::addPlus2(Vector3 v1)
{
	float renderY = max(size.z, max(size.x, size.y))/2 * 0.775;
	Vector3 vx3 = v1 + Vector3(0, -renderY, -0.1f);
	Vector3 vx2 = v1 + Vector3(0, -renderY, 0.1f);
	Vector3 vx1 = v1 + Vector3(0, renderY, 0.1f);
	
	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx3 = v1 + Vector3(0, renderY, 0.1f);
	vx2 = v1 + Vector3(0, renderY, -0.1f);
	vx1 = v1 + Vector3(0, -renderY, -0.1f);
	
	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx1 = v1 + Vector3(0, -0.1f, -renderY);
	vx2 = v1 + Vector3(0, 0.1f, -renderY);
	vx3 = v1 + Vector3(0, 0.1f, renderY);
	
	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx1 = v1 + Vector3(0, 0.1f, renderY);
	vx2 = v1 + Vector3(0, -0.1f, renderY);
	vx3 = v1 + Vector3(0, -0.1f, -renderY);
	
	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());
	
}
 void PartInstance::debugPrintVertexIDs(RenderDevice* rd,GFontRef font,Matrix3 rot)
{
	_debugUniqueVertices.clear();
	glDisable(GL_DEPTH_TEST);
	
	for (unsigned int i=0;i<_vertices.size();i+=6)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << i;
		Vector3 testVector = Vector3(_vertices[i],_vertices[i+1],_vertices[i+2]);
		if (isUniqueVertex(testVector))
		{
			
			font->draw3D(rd, stream.str(), CoordinateFrame(testVector) * -rot, 0.05, Color3::fromARGB(0xFF4F0000), Color4::clear());
			_debugUniqueVertices.push_back(testVector);
 		}
	}
 	glEnable(GL_DEPTH_TEST);
}
 void PartInstance::makeFace(int vertex1,int vertex2, int vertex3)
{
	addTriangle(Vector3(_vertices[vertex1],_vertices[vertex1+1],_vertices[vertex1+2]),
		Vector3(_vertices[vertex2],_vertices[vertex2+1],_vertices[vertex2+2]),
		Vector3(_vertices[vertex3],_vertices[vertex3+1],_vertices[vertex3+2]));
}
 void PartInstance::fromArrays(float verts[], float norms[], float ind[], unsigned int countVN, unsigned int countInd)
{
	for(unsigned int i = 0; i < countVN; i++)
	{
		_vertices.push_back(verts[i]);
		_normals.push_back(norms[i]);
	}
	for(unsigned int i = 0; i < countInd; i++)
	{
		_indices.push_back(ind[i]);
	}

}
void PartInstance::makeSmoothFace(int vertex1,int vertex2, int vertex3)
{
	addSmoothTriangle(Vector3(_vertices[vertex1],_vertices[vertex1+1],_vertices[vertex1+2]),
		Vector3(_vertices[vertex2],_vertices[vertex2+1],_vertices[vertex2+2]),
		Vector3(_vertices[vertex3],_vertices[vertex3+1],_vertices[vertex3+2]));
}
bool PartInstance::isUniqueVertex(Vector3 pos)
{
	for (unsigned int i=0;i<_debugUniqueVertices.size();i+=1)
	{
		if (pos==_debugUniqueVertices[i])
		{
			return false;
		}
	}
	return true;
}
//int rings = 15;
//int sectors = 15;
void PartInstance::render(RenderDevice* rd) {
	//if(nameShown)
		//postRenderStack.push_back(this);
 	if (changed)
	{
		
		getBox();
		_vertices.clear();
		_normals.clear();
		_indices.clear();
		//std::vector<GLfloat>(_vertices).swap(_vertices); //Clear the memory
		Vector3 renderSize = size/2;
		switch(this->shape)
		{
			case Enum::Shape::Ball:
				{
					/*float radius = renderSize.y / 2;
					float const R = 1./(float)(rings-1);
					float const S = 1./(float)(sectors-1);
					int r, s;
					double M_PI = pi();
					double M_PI_2 = M_PI/2;

					_vertices.resize(rings * sectors * 3);
					_normals.resize(rings * sectors * 3);
					std::vector<GLfloat>::iterator v = _vertices.begin();
					std::vector<GLfloat>::iterator n = _normals.begin();
					//std::vector<GLfloat>::iterator t = texcoords.begin();
					for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
							float const y = sin( -M_PI_2 + M_PI * r * R );
							float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
							float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );


							*v++ = x * radius;
							*v++ = y * radius;
							*v++ = z * radius;

							*n++ = x;
							*n++ = y;
							*n++ = z;
					}

					_indices.resize(rings * sectors * 4);
					std::vector<GLushort>::iterator i = _indices.begin();
					for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
							*i++ = r * sectors + s;
							*i++ = r * sectors + (s+1);
							*i++ = (r+1) * sectors + (s+1);
							*i++ = (r+1) * sectors + s;
					}
					//*/
					
				
				float sphFace = this->size.y / 3.14159F;
					// Front
				addSmoothTriangle(Vector3(renderSize.x-sphFace,renderSize.y-sphFace,renderSize.z),
					Vector3(-renderSize.x+sphFace,-renderSize.y+sphFace,renderSize.z),
					Vector3(renderSize.x-sphFace,-renderSize.y+sphFace,renderSize.z)
					);
			
				addSmoothTriangle(Vector3(-renderSize.x+sphFace,renderSize.y-sphFace,renderSize.z),
					Vector3(-renderSize.x+sphFace,-renderSize.y+sphFace,renderSize.z),
					Vector3(renderSize.x-sphFace,renderSize.y-sphFace,renderSize.z)
					);
				
				// Top
				addSmoothTriangle(Vector3(renderSize.x-sphFace,renderSize.y,renderSize.z-sphFace),
					Vector3(renderSize.x-sphFace,renderSize.y,-renderSize.z+sphFace),
					Vector3(-renderSize.x+sphFace,renderSize.y,renderSize.z-sphFace)
					);
				addSmoothTriangle(Vector3(-renderSize.x+sphFace,renderSize.y,renderSize.z-sphFace),
					Vector3(renderSize.x-sphFace,renderSize.y,-renderSize.z+sphFace),
					Vector3(-renderSize.x+sphFace,renderSize.y,-renderSize.z+sphFace)
					);
				
				// Back
				addSmoothTriangle(Vector3(renderSize.x-sphFace,renderSize.y-sphFace,-renderSize.z),
					Vector3(renderSize.x-sphFace,-renderSize.y+sphFace,-renderSize.z),
					Vector3(-renderSize.x+sphFace,-renderSize.y+sphFace,-renderSize.z)
					);
				addSmoothTriangle(Vector3(renderSize.x-sphFace,renderSize.y-sphFace,-renderSize.z),
					Vector3(-renderSize.x+sphFace,-renderSize.y+sphFace,-renderSize.z),
					Vector3(-renderSize.x+sphFace,renderSize.y-sphFace,-renderSize.z)
					);
		 		
				// Bottom
				addSmoothTriangle(Vector3(renderSize.x-sphFace,-renderSize.y,-renderSize.z+sphFace),
					Vector3(renderSize.x-sphFace,-renderSize.y,renderSize.z-sphFace),
					Vector3(-renderSize.x+sphFace,-renderSize.y,renderSize.z-sphFace)
					);
				addSmoothTriangle(Vector3(-renderSize.x+sphFace,-renderSize.y,renderSize.z-sphFace),
					Vector3(-renderSize.x+sphFace,-renderSize.y,-renderSize.z+sphFace),
					Vector3(renderSize.x-sphFace,-renderSize.y,-renderSize.z+sphFace)
					);
 				// Left
				addSmoothTriangle(Vector3(-renderSize.x,renderSize.y-sphFace,-renderSize.z+sphFace),
					Vector3(-renderSize.x,-renderSize.y+sphFace,renderSize.z-sphFace),
					Vector3(-renderSize.x,renderSize.y-sphFace,renderSize.z-sphFace)
					);
				addSmoothTriangle(Vector3(-renderSize.x,-renderSize.y+sphFace,renderSize.z-sphFace),
					Vector3(-renderSize.x,renderSize.y-sphFace,-renderSize.z+sphFace),
					Vector3(-renderSize.x,-renderSize.y+sphFace,-renderSize.z+sphFace)
					);
				
 				// Right
				addSmoothTriangle(Vector3(renderSize.x,renderSize.y-sphFace,renderSize.z-sphFace),
					Vector3(renderSize.x,-renderSize.y+sphFace,renderSize.z-sphFace),
					Vector3(renderSize.x,renderSize.y-sphFace,-renderSize.z+sphFace)
					);
				addSmoothTriangle(Vector3(renderSize.x,-renderSize.y+sphFace,-renderSize.z+sphFace),
					Vector3(renderSize.x,renderSize.y-sphFace,-renderSize.z+sphFace),
					Vector3(renderSize.x,-renderSize.y+sphFace,renderSize.z-sphFace)
					);
						

 				// Bevel Top Front
				makeSmoothFace(0,36,48);
				makeSmoothFace(48,18,0);
 				// Bevel Left Front Corner
				makeSmoothFace(18,156,162);
				makeSmoothFace(24,18,162);
 				// Bevel Left Front Top Corner
				makeSmoothFace(48,156,18);
 				// Bevel Left Front Bottom Corner
				makeSmoothFace(120,6,150);
 				// Bevel Left Top
				makeSmoothFace(48,66,156);
				makeSmoothFace(144,156,66);
 				// Bevel Bottom
				makeSmoothFace(6,120,114);
				makeSmoothFace(114,12,6);
 				// Left Bottom
				makeSmoothFace(120,150,174);
				makeSmoothFace(174,132,120);
 				// Right Front Top Corner
				makeSmoothFace(36,0,180);
 				// Right Front Corner
				makeSmoothFace(180,0,12);
				makeSmoothFace(186,180,12);
 				// Right Front Bottom Corner
				makeSmoothFace(186,12,114);
 				// Right Bottom
				makeSmoothFace(186,114,108);
				makeSmoothFace(108,198,186);
 				// Right Top Corner
				makeSmoothFace(180,192,36);
				makeSmoothFace(192,42,36);
 				// Right Back Top Corner
				makeSmoothFace(72,42,192);
 				// Right Back Bottom Corner
				makeSmoothFace(78,198,108);
 				// Right Back Corner
				makeSmoothFace(72,192,198);
				makeSmoothFace(198,78,72);
 				// Back Bottom Corner
				makeSmoothFace(78,108,132);
				makeSmoothFace(132,84,78);
 				// Back Top
				makeSmoothFace(42,72,102);
				makeSmoothFace(102,66,42);
 				// Back Left Top Corner
				makeSmoothFace(144,66,102);
 				// Back Left Corner
				makeSmoothFace(144,102,84);
				makeSmoothFace(84,174,144);
 				// Back Left Bottom Corner
				makeSmoothFace(174,84,132);
				for (unsigned short i=0;i<_vertices.size()/6;i++) {
					_indices.push_back(i);
				}
				}
				break;
			case Enum::Shape::Block:
				{
 			// Front
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
			}
			break;
			case Enum::Shape::Cylinder:
				{
					/*int fsize = renderSize.y/(pi()/2);
					//makeFace(0,0,48);
 			// Front
				addTriangle(Vector3(renderSize.x,renderSize.y-fsize,renderSize.z),
					Vector3(-renderSize.x,-renderSize.y+fsize,renderSize.z),
					Vector3(renderSize.x,-renderSize.y+fsize,renderSize.z)
					);
			
				addTriangle(Vector3(-renderSize.x,renderSize.y-fsize,renderSize.z),
					Vector3(-renderSize.x,-renderSize.y+fsize,renderSize.z),
					Vector3(renderSize.x,renderSize.y-fsize,renderSize.z)
					);
				
				// Top
				addTriangle(Vector3(renderSize.x,renderSize.y,renderSize.z-fsize),
					Vector3(renderSize.x,renderSize.y,-renderSize.z+fsize),
					Vector3(-renderSize.x,renderSize.y,renderSize.z-fsize)
					);
				addTriangle(Vector3(-renderSize.x,renderSize.y,renderSize.z-fsize),
					Vector3(renderSize.x,renderSize.y,-renderSize.z+fsize),
					Vector3(-renderSize.x,renderSize.y,-renderSize.z+fsize)
					);
				
				// Back
				addTriangle(Vector3(renderSize.x,renderSize.y-fsize,-renderSize.z),
					Vector3(renderSize.x,-renderSize.y+fsize,-renderSize.z),
					Vector3(-renderSize.x,-renderSize.y+fsize,-renderSize.z)
					);
				addTriangle(Vector3(renderSize.x,renderSize.y-fsize,-renderSize.z),
					Vector3(-renderSize.x,-renderSize.y+fsize,-renderSize.z),
					Vector3(-renderSize.x,renderSize.y-fsize,-renderSize.z)
					);
		 		
				// Bottom
				addTriangle(Vector3(renderSize.x,-renderSize.y,-renderSize.z+fsize),
					Vector3(renderSize.x,-renderSize.y,renderSize.z-fsize),
					Vector3(-renderSize.x,-renderSize.y,renderSize.z-fsize)
					);
				addTriangle(Vector3(-renderSize.x,-renderSize.y,renderSize.z-fsize),
					Vector3(-renderSize.x,-renderSize.y,-renderSize.z+fsize),
					Vector3(renderSize.x,-renderSize.y,-renderSize.z+fsize)
					);
 				// Left
				/*addTriangle(Vector3(-renderSize.x,renderSize.y-fsize,-renderSize.z+fsize),
					Vector3(-renderSize.x,-renderSize.y+fsize,renderSize.z-fsize),
					Vector3(-renderSize.x,renderSize.y-fsize,renderSize.z-fsize)
					);
				addTriangle(Vector3(-renderSize.x,-renderSize.y+fsize,renderSize.z-fsize),
					Vector3(-renderSize.x,renderSize.y-fsize,-renderSize.z+fsize),
					Vector3(-renderSize.x,-renderSize.y+fsize,-renderSize.z+fsize)
					);
 				// Right
				addTriangle(Vector3(renderSize.x,renderSize.y-fsize,renderSize.z-fsize),
					Vector3(renderSize.x,-renderSize.y+fsize,renderSize.z-fsize),
					Vector3(renderSize.x,renderSize.y-fsize,-renderSize.z+fsize)
					);
				addTriangle(Vector3(renderSize.x,-renderSize.y+fsize,-renderSize.z+fsize),
					Vector3(renderSize.x,renderSize.y-fsize,-renderSize.z+fsize),
					Vector3(renderSize.x,-renderSize.y+fsize,renderSize.z-fsize)
					);//*/
						

 				/*// Bevel Top Front
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
				makeFace(174,84,132);*/

				float radius = renderSize.y + (renderSize.y * (1 - cos(pi() / 12)));
				Vector2 xy[13];
				for(int i = 0; i < 13; i++)
				{	
					//Get the next point
					float y = radius * cos(((double)i-G3D::toRadians(29)) * pi()/6);
					float z = radius * sin(((double)i-G3D::toRadians(29)) * pi()/6);
					xy[i] = Vector2(y,z);
				}
				for(int i = 0; i < 12; i++)
				{
					//Create a Quad for the face (i to i+1)
					addSmoothTriangle(
						Vector3(renderSize.x, xy[i].x, xy[i].y),
						Vector3(-renderSize.x, xy[i].x, xy[i].y),
						Vector3(-renderSize.x, xy[i+1].x, xy[i+1].y));
					addSmoothTriangle(
						Vector3(renderSize.x, xy[i].x, xy[i].y),
						Vector3(-renderSize.x, xy[i+1].x, xy[i+1].y),
						Vector3(renderSize.x, xy[i+1].x, xy[i+1].y));
					//Cap on the right
					addTriangle(
						Vector3(renderSize.x, xy[0].x, xy[0].y),
						Vector3(renderSize.x, xy[i].x, xy[i].y),
						Vector3(renderSize.x, xy[i+1].x, xy[i+1].y));
					//Cap on the left
					addTriangle(
						Vector3(-renderSize.x, xy[i+1].x, xy[i+1].y),
						Vector3(-renderSize.x, xy[i].x, xy[i].y),
						Vector3(-renderSize.x, xy[0].x, xy[0].y));
				}
				/*float facetRatio = renderSize.x / (pi() * 0.5F);
				addQuad(
					Vector3(renderSize.x, renderSize.y, renderSize.z-facetRatio),
					Vector3(renderSize.x, renderSize.y, -renderSize.z+facetRatio),
					Vector3(-renderSize.x, renderSize.y, -renderSize.z+facetRatio),
					Vector3(-renderSize.x, renderSize.y, renderSize.z-facetRatio));

				addQuad(
					Vector3(renderSize.x, renderSize.y-facetRatio, renderSize.z),
					Vector3(-renderSize.x, renderSize.y-facetRatio, renderSize.z),
					Vector3(-renderSize.x, -renderSize.y+facetRatio, renderSize.z),
					Vector3(renderSize.x, -renderSize.y+facetRatio, renderSize.z));
				addQuad(
					Vector3(-renderSize.x, -renderSize.y, renderSize.z-facetRatio),
					Vector3(-renderSize.x, -renderSize.y, -renderSize.z+facetRatio),
					Vector3(renderSize.x, -renderSize.y, -renderSize.z+facetRatio),
					Vector3(renderSize.x, -renderSize.y, renderSize.z-facetRatio));
				addQuad(
					Vector3(renderSize.x, -renderSize.y+facetRatio, -renderSize.z),
					Vector3(-renderSize.x, -renderSize.y+facetRatio, -renderSize.z),
					Vector3(-renderSize.x, renderSize.y-facetRatio, -renderSize.z),
					Vector3(renderSize.x, renderSize.y-facetRatio, -renderSize.z));*/

				addPlus(Vector3(-renderSize.x-0.01,0,0));
				addPlus2(Vector3(renderSize.x+0.01,0,0));

				for (unsigned short i=0;i<_vertices.size()/6;i++) {
					_indices.push_back(i);
				}
				//std::reverse(_vertices.begin(), _vertices.end());
				//std::reverse(_normals.begin(), _normals.end());
				
				
						
			}
			break;
		}
		
 		changed=false;
		
		glNewList(glList, GL_COMPILE);
		glVertexPointer(3, GL_FLOAT,6 * sizeof(GLfloat), &_vertices[0]);
		glColorPointer(3, GL_FLOAT,6 * sizeof(GLfloat), &_vertices[3]);
		glNormalPointer(GL_FLOAT,3 * sizeof(GLfloat), &_normals[0]);
 		glPushMatrix();
		//glTranslatef(2,7,0);
		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_SHORT, &_indices[0]);
		glPopMatrix();
		glEndList();
	}
	rd->setObjectToWorldMatrix(cFrame);
	glCallList(glList);
	postRender(rd);
	//rd->setObjectToWorldMatrix(cFrame);
	
}
#else
void PartInstance::render(RenderDevice* rd)
{
	
	if(changed)
	{
		Box box = getBox();
	changed = false;
	glNewList(glList, GL_COMPILE);
	glColor(color);
	/*glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glBindTexture( GL_TEXTURE_2D, Globals::surfaceId);
	glBegin(GL_QUADS);*/
    for(int i = 0; i < 96; i+=16)
	{
		/*double add = 0.8;
		Enum::SurfaceType::Value face;
		if(i == 0)//Back
			face = back;
		else if(i == 16)//Right
			face = right;
		else if(i == 32)//Front
			face = front;
		else if(i == 48)//Top
			face = top;
		else if(i == 64)//Left
			face = left;
		else if(i == 80)//Bottom
			face = bottom;

		/*if(face == Snaps)
			add = 0.0;
		else if(face == Inlets)
			add = 0.2;*/

		Vector3 v0 = Vector3(_vertices[i], _vertices[i+1], _vertices[i+2]), v1 = Vector3(_vertices[i+3], _vertices[i+4], _vertices[i+5]), v3 = Vector3(_vertices[i+9], _vertices[i+10], _vertices[i+11]);
		/*glNormal3fv((v1 - v0).cross(v3 - v0).direction());
		glTexCoord2f(0.0F,0.0F);
		glVertex3fv(v0);
		glTexCoord2f(1.0F,0.0F);
		glVertex3fv(v1);
		glTexCoord2f(1.0F,0.25F);
		glVertex3f(_vertices[i+6], _vertices[i+7], _vertices[i+8]);
		glTexCoord2f(0.0F,0.25F);
		glVertex3fv(v3);*/

		glEnable(GL_BLEND);// you enable blending function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		glBegin( GL_QUADS );
		glNormal3fv((v1 - v0).cross(v3 - v0).direction());
		//glTexCoord2d(0.0,0.0+add);
		glVertex3fv(v0);
		//glTexCoord2d( 1.0,0.0+add);
		glVertex3fv(v1);
		//glTexCoord2d(1.0,0.2+add);
		glVertex3f(_vertices[i+6], _vertices[i+7], _vertices[i+8]);
		//glTexCoord2d( 0.0,0.2+add);
		glVertex3fv(v3);
		glEnd();
		//glDisable( GL_TEXTURE_2D );
	}
	glEndList();
	/*glEnd();
	glDisable(GL_TEXTURE_2D);*/
	}
	glCallList(glList);
	glColor(Color3::white());
	if(!children.empty())
	{
		for(size_t i = 0; i < children.size(); i++)
		{
			children.at(i)->render(rd);
		}
	}
	
}
#endif

PartInstance::~PartInstance(void)
{
	glDeleteLists(glList, 1);
}
char pto[512];
char pto2[512];
#include <sstream>

static Enum::Shape::Value strEnum(TCHAR* shape)
{
	if(strcmp("Block", shape) == 0)
		return Enum::Shape::Block;
	if(strcmp("Cylinder", shape) == 0)
		return Enum::Shape::Cylinder;
	return Enum::Shape::Ball;
}

static TCHAR* enumStr(int shape)
{
	switch(shape)
	{
		case Enum::Shape::Block:
			return "Block";
		case Enum::Shape::Ball:
			return "Ball";
		case Enum::Shape::Cylinder:
			return "Cylinder";
	}
}

void PartInstance::PropUpdate(LPPROPGRIDITEM &item)
{
	if(strcmp(item->lpszPropName, "Color3") == 0)
	{
		color = Color3(GetRValue(item->lpCurValue)/255.0F,GetGValue(item->lpCurValue)/255.0F,GetBValue(item->lpCurValue)/255.0F);
		changed=true;
	}
	if(strcmp(item->lpszPropName, "Anchored") == 0)
	{
		anchored=(bool)item->lpCurValue;
		changed=true;
	}
	else if(strcmp(item->lpszPropName, "Offset") == 0)
	{
		std::string str = (LPTSTR)item->lpCurValue;
		std::vector<float> vect;
		std::stringstream ss(str);
		float i;

		while (ss >> i)
		{
			vect.push_back(i);

			if (ss.peek() == ',')
				ss.ignore();
		}

		//if(vect.size() != 3)
		//{
			//sprintf(pto, "%g, %g, %g", cFrame.translation.x, cFrame.translation.y, cFrame.translation.z, "what");
			//LPCSTR str = LPCSTR(pto);
			//item->lpCurValue = (LPARAM)str;
		//}
		//else
		if(vect.size() == 3)
		{
			Vector3 pos(vect.at(0),vect.at(1),vect.at(2));
			setPosition(pos);
		}
	}

	else if(strcmp(item->lpszPropName, "Size") == 0)
	{
		std::string str = (LPTSTR)item->lpCurValue;
		std::vector<float> vect;
		std::stringstream ss(str);
		float i;

		while (ss >> i)
		{
			vect.push_back(i);

			if (ss.peek() == ',')
				ss.ignore();
		}

		/*if(vect.size() != 3)
		{
			sprintf(pto, "%g, %g, %g", cFrame.translation.x, cFrame.translation.y, cFrame.translation.z, "what");
			LPCSTR str = LPCSTR(pto);
			item->lpCurValue = (LPARAM)str;
		}
		else*/
		if(vect.size() == 3)
		{
			Vector3 size(vect.at(0),vect.at(1),vect.at(2));
			setSize(size);
		}
	}
	if(strcmp(item->lpszPropName, "Shape") == 0)
	{
		printf("%s", enumStr(strEnum((TCHAR*)item->lpCurValue)));
		setShape(strEnum((TCHAR*)item->lpCurValue));
	}
	else PVInstance::PropUpdate(item);
}



std::vector<PROPGRIDITEM> PartInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = PVInstance::getProperties();
	

	properties.push_back(createPGI(
		"Properties",
		"Color3",
		"The color of the selected part",
		RGB((color.r*255),(color.g*255),(color.b*255)),
		PIT_COLOR
		));
	properties.push_back(createPGI(
		"Item",
		"Anchored",
		"Whether the block can move or not",
		(LPARAM)anchored,
		PIT_CHECK
		));
	sprintf_s(pto, "%g, %g, %g", position.x, position.y, position.z);
	properties.push_back(createPGI(
		"Item",
		"Offset",
		"The position of the object in the workspace",
		(LPARAM)pto,
		PIT_EDIT
		));
	sprintf_s(pto2, "%g, %g, %g", size.x, size.y, size.z);
	properties.push_back(createPGI(
		"Item",
		"Size",
		"The position of the object in the workspace",
		(LPARAM)pto2,
		PIT_EDIT
		));
	properties.push_back(createPGI(
		"Item",
		"Shape",
		"The shape of the object in the workspace",
		(LPARAM)enumStr(shape),
		PIT_COMBO,
		TEXT("Ball\0Block\0Cylinder\0")
		));
	return properties;
}


