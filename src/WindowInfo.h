// WindowInfo.h

#ifndef _WINDOWINFO_H
#define _WINDOWINFO_H

#include <Window.h>
#include <OutlineListView.h>
#include <ScrollView.h>

#include "USBKit.h"

class WindowInfo : public BWindow
{
public:
	WindowInfo(BRect frame,const char *title, const USBDevice *dev,window_look look,window_feel feel,uint32 flags,uint32 workspace = B_CURRENT_WORKSPACE);
	void	ListConfiguration(const USBConfiguration *conf, BListItem *ParentItem);
	void 	ListInterface(const USBInterface *ifc, BListItem *ParentItem);
	void 	ListEndPoint(const USBEndpoint *ept, BListItem *ParentItem);
	BString	ClassName(uint8 Class);
	BString	SubclassName(uint8 Class, uint8 Subclass);
	BString	ProtocolName(uint8 Class, uint8 Subclass, uint8 Protocol);
	
private:
	BOutlineListView	* fOutlineListView;
	BScrollView			* fScrollView;
};

#endif