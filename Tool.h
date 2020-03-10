#pragma once

class Tool
{
public:
	Tool(void);
	~Tool(void);
	void OnButton1MouseDown();
	void OnButton2MouseDown();	
	void OnButton3MouseDown();	
	void OnButton1MouseUp();
	void OnButton2MouseUp();
	void OnButton3MouseUp();
	void OnMouseScroll();
	void OnKeyDown();
	void OnKeyUp();
};
