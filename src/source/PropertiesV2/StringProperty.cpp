#include "PropertiesV2/StringProperty.h"

PROPGRIDITEM StringProperty::getPropGridItem(){
	PROPGRIDITEM pItem;
	PropGrid_ItemInit(pItem);
	pItem.lpszCatalog=_catalog;
	pItem.lpszPropName=_name;
	pItem.lpszPropDesc=_desc;
	pItem.lpCurValue=(LPARAM)_value.c_str();
	pItem.iItemType=PIT_EDIT;
	return pItem;
}

void StringProperty::setProperty(LPPROPGRIDITEM &pItem){
	setValue((LPSTR)pItem->lpCurValue);
}