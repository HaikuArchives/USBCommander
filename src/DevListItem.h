// DevListItem.h

#ifndef _DEVLISTITEM_H
#define _DEVLISTITEM_H

#include <ListItem.h> 
#include "USBKit.h"

class DevListItem : public BListItem
{
	public:
		DevListItem(USBDevice * dev); 
		virtual void DrawItem(BView *owner, 
			BRect frame, 
			bool complete = false); 
		USBDevice *GetDev(void);

	private: 
		USBDevice *fDev; 
};

#endif