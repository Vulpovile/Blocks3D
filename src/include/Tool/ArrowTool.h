#pragma once
#include "tool.h"
namespace B3D {
	class ArrowTool : public Tool
	{
	public:
		ArrowTool(void); //OnSelect?
		~ArrowTool(void); //OnDeselect?
		void onButton1MouseDown(Mouse);
		void onButton1MouseUp(Mouse);
		void onMouseMoved(Mouse mouse);
		void onSelect(Mouse mouse); 
		void onKeyDown(int key);
		void onKeyUp(int key);
		void roundDeg(float &degree);
	private:
		bool lctrlDown;
		bool rctrlDown;
		int mouseDownStartx;
		int mouseDownStarty;
		bool dragging;
		bool mouseDown;
		Vector3 draggingPartOffset;
	};
}