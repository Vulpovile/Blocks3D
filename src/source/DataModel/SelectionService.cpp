#include "DataModelV2/SelectionService.h"

SelectionService::SelectionService(void){
	Instance::Instance();
	propertyWindow = NULL;
}

SelectionService::~SelectionService(void){
}

SelectionService::SelectionService(const SelectionService &oinst){
	Instance::Instance(oinst);
	propertyWindow = NULL;
}


std::vector<Instance *> SelectionService::getSelection(){
	return this->selection;
}
void SelectionService::clearSelection(){
	this->selection.clear();
	if(propertyWindow != NULL)
		propertyWindow->ClearProperties();
}
bool SelectionService::isSelected(Instance * instance){
	return std::find(selection.begin(), selection.end(), instance) != selection.end();
}
void SelectionService::addSelected(Instance * instance){
	if(!isSelected(instance))
		this->selection.push_back(instance);
	if(propertyWindow != NULL)
		propertyWindow->UpdateSelected(selection);
}
void SelectionService::removeSelected(Instance * instance){
	selection.erase(std::remove(selection.begin(), selection.end(), instance), selection.end());
	if(propertyWindow != NULL)
		propertyWindow->UpdateSelected(selection);
}
void SelectionService::addSelected(const std::vector<Instance *> &instances){
	for(size_t i = 0; i < instances.size(); i++)
	{
		if(!isSelected(instances[i]))
			this->selection.push_back(instances[i]);
	}
	if(propertyWindow != NULL)
		propertyWindow->UpdateSelected(selection);
}
void SelectionService::setPropertyWindow(PropertyWindow * propertyWindow)
{
	this->propertyWindow = propertyWindow;
	if(propertyWindow != NULL)
		propertyWindow->ClearProperties();
}
