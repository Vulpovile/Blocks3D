#include "PropertiesV2/BoolProperty.h"

PROPGRIDITEM BoolProperty::getPropGridItem(){
	PROPGRIDITEM pItem;
	PropGrid_ItemInit(pItem);
	pItem.lpszCatalog=_catalog;
	pItem.lpszPropName=_name;
	pItem.lpszPropDesc=_desc;
	pItem.lpCurValue=_value;
	pItem.iItemType=PIT_CHECK;
	return pItem;
}

void BoolProperty::setProperty(LPPROPGRIDITEM &pItem){
	setValue(pItem->lpCurValue == TRUE);
}