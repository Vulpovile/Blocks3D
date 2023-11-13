#pragma once
#include "Instance.h"
namespace B3D
{
	typedef unsigned short SigMesg;
	const SigMesg OPT_DESTROY_LPARAM = 0x8000;
	const SigMesg OPT_DESTROY_WPARAM = 0x4000;

	class SignalService : public Instance
	{
	public:
		SignalService(void);
		~SignalService(void);
		bool registerInstance(Instance * instance);
		bool revokeInstance(Instance * instance);
		void revokeAll();
		void dispatchSignal(SigMesg& msgId, void* lParam, void* wParam);
	};
}