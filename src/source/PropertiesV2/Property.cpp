#include "PropertiesV2/Property.h"

template <typename T>
PROPGRIDITEM Property<T>::getPropGridItem(){
	PROPGRIDITEM pItem;
	PropGrid_ItemInit(pItem);
	pItem.lpszCatalog=_catalog;
	pItem.lpszPropName=_name;
	pItem.lpszPropDesc=_desc;
	pItem.lpCurValue="invalid";
	pItem.iItemType=PIT_EDIT;
	return pItem;
}

template <typename T>
void Property<T>::setProperty(LPPROPGRIDITEM &pItem){
}