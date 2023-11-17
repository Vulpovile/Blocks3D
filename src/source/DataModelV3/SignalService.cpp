#include "DataModelV3/SignalService.h"
using namespace B3D;

SignalService::SignalService(void) : Instance() {
	
}

SignalService::~SignalService(void){

}

bool SignalService::registerInstance(Instance * instance, SigMesg msgType){
	SigMesg maskedMessage = (msgType & MSG_MASK);
	if(maskedMessage < MSG_LENGTH)
	{
		return this->messengerTable[maskedMessage].insert(instance).second;
	}
	//Perhaps throw error in the future
	return false;
}

bool SignalService::revokeInstance(Instance * instance, SigMesg msgType){
	SigMesg maskedMessage = (msgType & MSG_MASK);
	if(maskedMessage < MSG_LENGTH)
	{
		this->messengerTable[maskedMessage].erase(instance);		
		return true;
	}
	return false;
}

bool SignalService::revokeInstance(Instance * instance){
	for(SigMesg i = 0; i < MSG_LENGTH; i++)
	{
		this->messengerTable[i].erase(instance);		
	}
	return true;
}

void SignalService::revokeType(SigMesg msgType){
	SigMesg maskedMessage = (msgType & MSG_MASK);
	if(maskedMessage < MSG_LENGTH)
	{
		this->messengerTable[maskedMessage].clear();		
	}
}

void SignalService::revokeAll(){
	for(SigMesg i = 0; i < MSG_LENGTH; i++)
	{
		this->messengerTable[i].clear();		
	}
}

bool SignalService::postMessage(SigMesg msgType, void* lParam, void* wParam){
	SigMesg maskedMessage = (msgType & MSG_MASK);
	if(maskedMessage < MSG_LENGTH)
	{
		std::set<Instance*>::iterator itr;
		for(itr = this->messengerTable[maskedMessage].begin(); itr != this->messengerTable[maskedMessage].end(); itr++)
		{
			if((*itr)->postMessage(msgType, lParam, wParam))
				break;
		}
	}
	if(msgType & OPT_DESTROY_LPARAM)
		delete lParam;
	if(msgType & OPT_DESTROY_WPARAM)
		delete wParam;
	//There should be no signal service that posts messages to signal service!!!
	return true;
}