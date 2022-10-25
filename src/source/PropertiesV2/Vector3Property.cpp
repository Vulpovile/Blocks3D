#include "PropertiesV2/Vector3Property.h"

PROPGRIDITEM Vector3Property::getPropGridItem(){
	std::stringstream s;
	s << _value.x << ", " << _value.y << ", " << _value.z;
	stringRep = s.str();
	PROPGRIDITEM pItem;
	PropGrid_ItemInit(pItem);
	pItem.lpszCatalog=_catalog;
	pItem.lpszPropName=_name;
	pItem.lpszPropDesc=_desc;
	pItem.lpCurValue=(LPARAM)stringRep.c_str();
	pItem.iItemType=PIT_EDIT;
	return pItem;
}

void Vector3Property::setProperty(LPPROPGRIDITEM &pItem){

	std::string str = (LPTSTR)pItem->lpCurValue;
	std::vector<float> vect;
	std::stringstream ss(str);
	float i;
	while (ss >> i)
	{
		vect.push_back(i);
		if (ss.peek() == ',')
			ss.ignore();
	}
	if(vect.size() == 3)
	{
		setValue(Vector3(vect.at(0),vect.at(1),vect.at(2)));
	}
}