#include "ImageButtonInstance.h"

ImageButtonInstance::ImageButtonInstance(G3D::TextureRef newImage, G3D::TextureRef overImage = NULL, G3D::TextureRef downImage = NULL, G3D::TextureRef disableImage = NULL)
{
	BaseButtonInstance::BaseButtonInstance();
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
	//Delete everything on destruction
	image.~ReferenceCountedPointer();
	delete image.getPointer();
	image_ovr.~ReferenceCountedPointer();
	delete image_ovr.getPointer();
	image_ds.~ReferenceCountedPointer();
	delete image_ds.getPointer();
	image_dn.~ReferenceCountedPointer();
	delete image_dn.getPointer();
	image = NULL;
	image_ovr = NULL;
	image_ds = NULL;
	image_dn = NULL;
	delete listener;
	listener = NULL;
	selected = false;
}

bool ImageButtonInstance::mouseInButton(float mousex, float mousey, RenderDevice* rd)
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
	if(mousex >= positionRelative.x && mousey >= positionRelative.y)
	{
		if(mousex < positionRelative.x + size.x && mousey < positionRelative.y + size.y)
		{
			return true;
		}
	}
	return false;
}

void ImageButtonInstance::drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown)
{
	bool drawDisabledBox = false;
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
	if(selected == true && !image_dn.isNull() && !disabled)
	{
		renderimage = openGLID_dn;
	}
	else if(disabled)
	{
		if(!image_ds.isNull())
			renderimage = openGLID_ds;
		else
			drawDisabledBox = true;
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
	
	if(drawDisabledBox)
	{
		Draw::box(Box(Vector3(positionRelative.x, positionRelative.y, 0), Vector3(positionRelative.x+size.x, positionRelative.y+size.y, 0)), rd, Color4(0.7F,0.7F,0.7F,0.3F), Color4::clear());
	}
}