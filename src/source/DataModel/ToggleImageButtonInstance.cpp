#include "DataModel/ToggleImageButtonInstance.h"

ToggleImageButtonInstance::ToggleImageButtonInstance(G3D::TextureRef newImage,
										 G3D::TextureRef overImage,
										 G3D::TextureRef downImage,
										 G3D::TextureRef disableImage,
										 G3D::TextureRef newImage2,
										 G3D::TextureRef overImage2,
										 G3D::TextureRef downImage2,
										 G3D::TextureRef disableImage2) : ImageButtonInstance(newImage, overImage, downImage, disableImage)
{
	image2 = newImage2;
	openGLID2 = image2->getOpenGLID();
	image_ovr2 = overImage2;
	if(!image_ovr2.isNull())
	openGLID2_ovr = image_ovr2->getOpenGLID();
	image_dn2 = downImage2;
	if(!image_dn2.isNull())
		openGLID2_dn = image_dn2->getOpenGLID();
	image_ds2 = disableImage2;
	if(!image_ds2.isNull())
		openGLID2_ds = image_ds2->getOpenGLID();
	checked = false;
	className = "ToggleImageButton";
}

ToggleImageButtonInstance::~ToggleImageButtonInstance(void)
{
	//Delete everything on destruction
	image2.~ReferenceCountedPointer();
	delete image2.getPointer();
	image_ovr2.~ReferenceCountedPointer();
	delete image_ovr2.getPointer();
	image_ds2.~ReferenceCountedPointer();
	delete image_ds2.getPointer();
	image_dn2.~ReferenceCountedPointer();
	delete image_dn2.getPointer();
	image = NULL;
	image_ovr = NULL;
	image_ds = NULL;
	image_dn = NULL;
	delete listener;
	listener = NULL;
	selected = false;
}


void ToggleImageButtonInstance::drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown)
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
	if(checked)
	{
		renderimage = openGLID2;
		if(selected == true && !image_dn2.isNull() && !disabled)
		{
			renderimage = openGLID2_dn;
		}
		else if(disabled)
		{
			if(!image_ds2.isNull())
				renderimage = openGLID2_ds;
			else
				drawDisabledBox = true;
		}
		else if(mouseInArea(positionRelative.x, positionRelative.y, positionRelative.x + size.x, positionRelative.y + size.y, mousePos.x, mousePos.y))
		{
			if(mouseDown && !image_dn2.isNull())
			{
				renderimage = openGLID2_dn;
			}
			else if(!image_ovr2.isNull())
			{
				renderimage = openGLID2_ovr;
			}
		}
	}
	else
	{
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