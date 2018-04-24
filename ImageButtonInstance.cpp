#include "ImageButtonInstance.h"
G3D::TextureRef image = NULL;
int openGLID = 0;
G3D::TextureRef image_ovr = NULL;
int openGLID_ovr = 0;
G3D::TextureRef image_dn = NULL;
int openGLID_dn = 0;
G3D::TextureRef image_ds = NULL;
int openGLID_ds = 0;
Vector2 size;
Vector2 position;
ImageButtonInstance::ImageButtonInstance(G3D::TextureRef newImage, G3D::TextureRef overImage = NULL, G3D::TextureRef downImage = NULL, G3D::TextureRef disableImage = NULL)
{
	
	image = newImage;
	openGLID = image->getOpenGLID();
	image_ovr = overImage;
	if(!image_ovr.isNull())
	openGLID_ovr = image_ovr->getOpenGLID();
	image_dn = downImage;
	if(!image_dn.isNull())
		openGLID_dn = image_dn->getOpenGLID();
	image_ds = disableImage;
	if(!image_ds.isNull())
		openGLID_ds = image_ds->getOpenGLID();
	Vector2 size = Vector2(0,0);
	Vector2 position = Vector2(0,0);
	floatCenter = false;
	floatBottom = false;
	floatRight = false;
	disabled = false;
	className = "ImageButton";
}

ImageButtonInstance::~ImageButtonInstance(void)
{
}

void ImageButtonInstance::drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown)
{
	Vector2 positionRelative = position;
	if(floatRight && floatBottom)
	{
	    positionRelative = Vector2(rd->getWidth() + position.x, rd->getHeight() + position.y);
	}
	else if(floatBottom)
	{
	    positionRelative = Vector2(position.x, rd->getHeight() + position.y);
	}
	else if(floatRight)
	{
		positionRelative = Vector2(rd->getWidth() + position.x, position.y);
	}
	int renderimage = openGLID;
	if(disabled)
	{
		if(openGLID_ds != 0)
			renderimage = openGLID;
	}
	else if(mouseInArea(positionRelative.x, positionRelative.y, positionRelative.x + size.x, positionRelative.y + size.y, mousePos.x, mousePos.y))
	{
		if(mouseDown && !image_dn.isNull())
		{
			renderimage = openGLID_dn;
		}
		else if(!image_ovr.isNull())
		{
			renderimage = openGLID_ovr;
		}
	}


	rd->pushState();
		rd->beforePrimitive();
		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);// you enable blending function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		glBindTexture( GL_TEXTURE_2D, renderimage);
		glBegin( GL_QUADS );
		glTexCoord2d(0.0,0.0);
		glVertex2f( positionRelative.x, positionRelative.y );
		glTexCoord2d( 1.0,0.0 );
		glVertex2f( positionRelative.x + size.x, positionRelative.y );
		glTexCoord2d( 1.0,1.0 );
		glVertex2f( positionRelative.x + size.x, positionRelative.y + size.y );
		glTexCoord2d( 0.0,1.0 );
		glVertex2f( positionRelative.x, positionRelative.y + size.y );
		glEnd();
		glDisable( GL_TEXTURE_2D );
		rd->afterPrimitive();
	rd->popState();
}