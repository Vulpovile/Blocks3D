#include "PropertiesV2/Color3Property.h"

PROPGRIDITEM Color3Property::getPropGridItem(){
	PROPGRIDITEM pItem;
	PropGrid_ItemInit(pItem);
	pItem.lpszCatalog=_catalog;
	pItem.lpszPropName=_name;
	pItem.lpszPropDesc=_desc;
	pItem.lpCurValue=RGB((_value.r*255),(_value.g*255),(_value.b*255));
	pItem.iItemType=PIT_COLOR;
	return pItem;
}

void Color3Property::setProperty(LPPROPGRIDITEM &pItem){

	setValue(Color3(
			GetRValue(pItem->lpCurValue)/255.0F,
			GetGValue(pItem->lpCurValue)/255.0F,
			GetBValue(pItem->lpCurValue)/255.0F
		));
}