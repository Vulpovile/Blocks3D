#include "PropertiesV2/Property.h"

PROPGRIDITEM Property::getPropGridItem(){
	PROPGRIDITEM pItem;
	PropGrid_ItemInit(pItem);
	pItem.lpszCatalog=_catalog;
	pItem.lpszPropName=_name;
	pItem.lpszPropDesc=_desc;
	pItem.iItemType=PIT_EDIT;
	return pItem;
}

void Property::setProperty(LPPROPGRIDITEM &pItem){
}