#pragma once
#include <G3DAll.h>
#include "CameraController.h"

class Demo : public GApp {
	public:
		Demo(const GAppSettings& settings,Win32Window* wind);
		virtual			~Demo() {}
		virtual void	exitApplication();
		virtual void	onInit();
		virtual void	onLogic();
		virtual void	onNetwork();
		virtual void	onSimulation(RealTime rdt, SimTime sdt, SimTime idt);
		virtual void	onGraphics(RenderDevice* rd);
		virtual void	onUserInput(UserInput* ui);
		virtual void	onCleanup();

		Instance*	getSelection();
		void		QuitApp();
		void		onKeyPressed(int key);
		void		onKeyUp(int key);
		void		onMouseLeftPressed(int x, int y);
		void		onMouseLeftUp(int x, int y);
		void		onMouseRightPressed(int x, int y);
		void		onMouseRightUp(int x, int y);
		void		onMouseMoved(int x, int y);
		void		onMouseWheel(int x, int y, short delta);
		CameraController	cameraController;
	private:
		void				initGUI();
		HWND				hWndMain;
		SkyRef				sky;
		bool				quit;
		bool				rightButtonHolding;
		void				main();
};
