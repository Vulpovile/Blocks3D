#pragma once
namespace B3D{
	typedef unsigned char SigMesg;

	const SigMesg OPT_DESTROY_LPARAM = 0x80;
	const SigMesg OPT_DESTROY_WPARAM = 0x40;

	const SigMesg MSG_MOUSECLICK = 0;
	const SigMesg MSG_KEY_STATE = 1;
	const SigMesg MSG_MOUSE_BUTTON_STATE = 2;
	const SigMesg MSG_MOUSE_WHEEL_STEP = 3;
	const SigMesg MSG_LENGTH = 4;
}