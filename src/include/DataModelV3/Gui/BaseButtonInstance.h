#pragma once
#include <G3DAll.h>
#include "../Instance.h"

namespace B3D{
	class BaseButtonInstance : public Instance
	{
	public:
		BaseButtonInstance(void);
		virtual ~BaseButtonInstance(void);
		virtual void render(RenderDevice* rd);
		virtual void drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown);
		virtual bool mouseInButton(float, float, RenderDevice* rd);
		virtual void onMouseClick();
		void setActionCode(int actionCode);
		bool floatBottom;
		bool floatRight;
		bool floatCenter;
		volatile bool disabled;
		bool selected;
	protected:
		int actionCode;
		bool mouseInArea(float, float, float, float, float, float);
	};
}