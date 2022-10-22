#include "PropertiesV2/BaseProperty.h"

PROPGRIDITEM BaseProperty::getPropGridItem(){
	PROPGRIDITEM pItem;
	PropGrid_ItemInit(pItem);
	pItem.lpszCatalog=_catalog;
	pItem.lpszPropName=_name;
	pItem.lpszPropDesc=_desc;
	pItem.iItemType=PIT_EDIT;
	return pItem;
}

void BaseProperty::setProperty(LPPROPGRIDITEM &pItem){
}