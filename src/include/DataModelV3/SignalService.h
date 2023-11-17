#pragma once
#include "Instance.h"
#include "SignalTypes.h"
#include <set>

namespace B3D
{

	class SignalService : public Instance
	{
	public:
		SignalService(void);
		~SignalService(void);
		bool registerInstance(Instance * instance, SigMesg msgType);
		bool revokeInstance(Instance * instance, SigMesg msgType);
		bool revokeInstance(Instance * instance);
		void revokeType(SigMesg msgType);
		void revokeAll();
		bool postMessage(SigMesg msgId, void* lParam, void* wParam);
	private:
		static const SigMesg MSG_MASK = 0x3F;
		std::set<Instance *> messengerTable[SignalService::MSG_LENGTH];
	};
}