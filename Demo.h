#pragma once
#include <G3DAll.h>
#include "CameraController.h"
#include "PropertyWindow.h"

class Demo { // : public GApp {
	public:
		Demo(const GAppSettings& settings,HWND parentWindow);
		void Boop();
		virtual			~Demo() {}
		virtual void	exitApplication();
		virtual void	onInit();
		virtual void	onLogic();
		virtual void	onNetwork();
		virtual void	onSimulation(RealTime rdt, SimTime sdt, SimTime idt);
		virtual void	onGraphics(RenderDevice* rd);
		virtual void	onUserInput(UserInput* ui);
		virtual void	onCleanup();

		std::vector<Instance*>	getSelection();
		void		run();
		void		QuitApp();
		void		resizeWithParent(HWND parentWindow);
		void		onCreate(HWND parentWindow);
		void		onKeyPressed(int key);
		void		onKeyUp(int key);
		void		onMouseLeftPressed(HWND hwnd,int x, int y);
		void		onMouseLeftUp(int x, int y);
		void		onMouseRightPressed(int x, int y);
		void		onMouseRightUp(int x, int y);
		void		onMouseMoved(int x, int y);
		void		onMouseWheel(int x, int y, short delta);

		CameraController	cameraController;
		RenderDevice*		renderDevice;
		UserInput*			userInput;
		PropertyWindow*		_propWindow;
	private:
		void				initGUI();
		HWND				_hWndMain;
		SkyRef				sky;
		bool				quit;
		bool				mouseOnScreen;
		bool				rightButtonHolding;
		void				main();
		GWindow*			_window;
		HWND				_hwndToolbox;
		HWND				_buttonTest;
		HWND				_hwndRenderer;
		
	protected:
		Stopwatch           m_graphicsWatch;
		Stopwatch           m_logicWatch;
		Stopwatch           m_networkWatch;
		Stopwatch           m_userInputWatch;
		Stopwatch           m_simulationWatch;
		Stopwatch           m_waitWatch;
};
