// DevListItem.cpp

/* USBCommander - USB device information aid
 * Copyright (c) 2003 Dan Pidcock
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
#include "DevListItem.h"
#include <View.h>

DevListItem::DevListItem(USBDevice * dev)
{
	fDev = dev;
} 

 
void DevListItem::DrawItem(BView *owner, BRect frame, bool complete = false)
{
rgb_color kHighlightColor;
kHighlightColor.red = 100;
kHighlightColor.green = 200;
kHighlightColor.blue = 100;
		rgb_color color, loColor, hiColor;
	if (IsSelected() || complete)
	{
		loColor = owner->LowColor();
		hiColor = owner->HighColor();
		if (IsSelected()) {
			color = kHighlightColor; 
		} 
		else { 
			color = owner->ViewColor(); 
		} 
		owner->SetHighColor(color); 
		owner->FillRect(frame);
	}

	if (IsSelected() || complete) {
		owner->SetLowColor(kHighlightColor); 
	}
	else {
		owner->SetLowColor(owner->ViewColor());
	}
	owner->SetHighColor(hiColor);
	float left, bottom;
	left = frame.left+4;
	bottom = frame.bottom-2;
	owner->MovePenTo(left, bottom);
	if (!fDev)
	{
		owner->DrawString("Device not present");
	}
	else
	{
		if (fDev->IsHub())
			owner->DrawString("Hub");
		else
			owner->DrawString("Dev");
		left += 30;
		owner->MovePenTo(left, bottom);
		owner->DrawString(fDev->Location());
		left += 30;
		owner->MovePenTo(left, bottom);
		owner->DrawString(fDev->ManufacturerString());
		left += 70;
		owner->MovePenTo(left, bottom);
		owner->DrawString(fDev->ProductString());
	}
	
}

USBDevice *DevListItem::GetDev(void)
{
	return fDev;
}