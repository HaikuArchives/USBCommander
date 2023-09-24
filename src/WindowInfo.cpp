// WindowInfo.cpp

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
 

#include "WindowInfo.h"

#include <String.h>

#include <stdio.h>

/***** Constructor ****/
WindowInfo::WindowInfo(BRect frame,const char *title, const USBDevice *dev,window_look look,window_feel feel,uint32 flags,uint32 workspace)
: BWindow(frame,title,look,feel,flags,workspace)
{
	// Allocate objects
	BRect	r;
	r = Bounds();
	r.right -= B_V_SCROLL_BAR_WIDTH;
	fOutlineListView = new BOutlineListView(
					r,
					"InfoList",
					B_SINGLE_SELECTION_LIST,
					B_FOLLOW_ALL_SIDES
					);
					
	fScrollView = new BScrollView("ScrollViewInfo", fOutlineListView, B_FOLLOW_ALL_SIDES, 0, false, true, B_FANCY_BORDER);
	// Add objects
	AddChild(fScrollView);	
	
	if (!dev)
	{
		BListItem *nullDevice;
		fOutlineListView->AddItem(nullDevice = new BStringItem("Null device"));
	}
	else
	{	
		BString		entry;
		BListItem	*mfgString;
		entry = ""; entry << "Manufacturer: " << dev->ManufacturerString();
		fOutlineListView->AddItem(mfgString = new BStringItem(entry.String()));
		BListItem	*prodString;
		entry = ""; entry << "Product: " << dev->ProductString();
		fOutlineListView->AddItem(prodString = new BStringItem(entry.String()));
		entry = ""; entry << "Serial number: " << dev->SerialNumberString();
		BListItem	*serNumString;
		fOutlineListView->AddItem(serNumString = new BStringItem(entry.String()));
		entry = "Class: "; entry << (uint32)dev->Class() << " (" << ClassName(dev->Class()) << ")";
		fOutlineListView->AddItem(new BStringItem(entry.String()));
		entry = "Subclass: "; entry << (uint32)dev->Subclass() << " (" << SubclassName(dev->Class(), dev->Subclass()) << ")";
		fOutlineListView->AddItem(new BStringItem(entry.String()));
		entry = "Protocol: "; entry << (uint32)dev->Protocol() << " (" << ProtocolName(dev->Class(), dev->Subclass(), dev->Protocol()) << ")";
		fOutlineListView->AddItem(new BStringItem(entry.String()));
		entry = "VendorID: "; entry << (uint32)dev->VendorID();
		fOutlineListView->AddItem(new BStringItem(entry.String()));
		entry = "ProductID: "; entry << (uint32)dev->ProductID();
		fOutlineListView->AddItem(new BStringItem(entry.String()));
		entry = "Version: "; entry << (uint32)dev->Version();
		fOutlineListView->AddItem(new BStringItem(entry.String()));
#if 0
		// template
		entry = ": "; entry << dev->();
		fOutlineListView->AddItem(new BStringItem(entry.String()));
#endif
		uint32 i;
		i = dev->CountConfigurations();
		while (i > 0)
		{
			i--; // Have to count down as AddUnder adds items backwards
			printf("config %ld\n", i);
			BListItem	*config;
			entry = "Configuration "; entry << i;
			fOutlineListView->AddItem(config = new BStringItem(entry.String()));
			ListConfiguration(dev->ConfigurationAt(i), config);
		};

	}
}

void WindowInfo::ListConfiguration(const USBConfiguration *conf, BListItem *ParentItem)
{
	BString		entry;
	
	uint32 i;
	if (!conf) 
		return;
	i = conf->CountInterfaces();
	while (i > 0) 
	{
		i--;
		printf("interface %ld\n", i);
		entry = "Interface "; entry << i;
		BListItem	*interface;
		fOutlineListView->AddUnder(interface = new BStringItem(entry.String()), ParentItem);
		ListInterface(conf->InterfaceAt(i), interface);
	};
}

void WindowInfo::ListInterface(const USBInterface *ifc, BListItem *ParentItem)
{
	if (!ifc)
		return;

	BString		entry;
	uint32		i;

	entry = "Protocol: "; entry << (uint32)ifc->Protocol() << " (" << ProtocolName(ifc->Class(), ifc->Subclass(), ifc->Protocol()) << ")";
	fOutlineListView->AddUnder(new BStringItem(entry.String()), ParentItem);
	entry = "Subclass: "; entry << (uint32)ifc->Subclass() << " (" << SubclassName(ifc->Class(), ifc->Subclass()) << ")";
	fOutlineListView->AddUnder(new BStringItem(entry.String()), ParentItem);
	entry = "Class: "; entry << (uint32)ifc->Class() << " (" << ClassName(ifc->Class()) << ")";
	fOutlineListView->AddUnder(new BStringItem(entry.String()), ParentItem);
	// EndPoints
	i = ifc->CountEndpoints();
	while (i > 0) 
	{
		i--;
		printf("Endpoint %lu\n", i);
		entry = "Endpoint "; entry << i;
		BListItem	*endpoint;
		fOutlineListView->AddUnder(endpoint = new BStringItem(entry.String()), ParentItem);
		ListEndPoint(ifc->EndpointAt(i), endpoint);
	};
	// Descriptors
	uchar data[256];
	usb_descriptor *descr = (usb_descriptor *) data;
	i = 0;
	uint8	j;
	char	hexByteStr[2];
	while (ifc->OtherDescriptorAt(i, descr, 256) == B_OK)
	{
		entry = "Descriptor "; entry << i << ": ";
		for(j=0;j<descr->generic.length;j++){
			sprintf(hexByteStr, "%02x", descr->generic.data[j]);
			entry << hexByteStr;
		}
		fOutlineListView->AddUnder(new BStringItem(entry.String()), ParentItem);
		i++;
	}
}

void WindowInfo::ListEndPoint(const USBEndpoint *ept, BListItem *ParentItem)
{
	if (!ept)
		return;

	BString		entry;

	entry = "MaxPacketSize: "; entry << (uint32)ept->MaxPacketSize();
	fOutlineListView->AddUnder(new BStringItem(entry.String()), ParentItem);
	entry = "Interval: "; entry << (uint32)ept->Interval();
	fOutlineListView->AddUnder(new BStringItem(entry.String()), ParentItem);
	if (ept->IsBulk())
		fOutlineListView->AddUnder(new BStringItem("Bulk"), ParentItem);
	if (ept->IsIsochronous())
		fOutlineListView->AddUnder(new BStringItem("Isochronous"), ParentItem);
	if (ept->IsInterrupt())
		fOutlineListView->AddUnder(new BStringItem("Interrupt"), ParentItem);
	if (ept->IsInput())
		fOutlineListView->AddUnder(new BStringItem("Direction: Input"), ParentItem);
	else
		fOutlineListView->AddUnder(new BStringItem("Direction: Output"), ParentItem);
}


BString	WindowInfo::ClassName(uint8 Class)
{
	switch (Class)
	{
		case 1:
			return "Audio";
		case 2:
			return "Communication";
		case 3:
			return "Human interface";
		case 5:
			return "Physical";
		case 6:
			return "Image";
		case 7:
			return "Printer";
		case 8:
			return "Mass storage";
		case 9:
			return "Hub";
		case 10:
			return "Data interface";
		case 11:
			return "Smart card";
		case 13:
			return "Content-security";
		case 255:
			return "Vendor specific";
		default:
			return "?";
	}
}

BString		WindowInfo::SubclassName(uint8 Class, uint8 Subclass)
{
	switch (Class)
	{
		case 1:	// Audio
			switch (Subclass)
			{
				case 1:
					return "Audio control";		//	1_1_0
				case 2:
					return "Audio streaming";	// 	1_2_0
				case 3:
					return "MIDI streaming";	//	1_3_0
				default:
					return "?";
			}
		case 10:
			if (Subclass == 255)
				return "Webcam";				// 10_255_0
			else
				return "?";
		default:
			return "?";
	}
}

BString		WindowInfo::ProtocolName(uint8 Class, uint8 Subclass, uint8 Protocol)
{
		
	switch (Class)
	{
		case 3: // "Human interface";
			switch (Subclass)
			{
				case 1:
					switch (Protocol)
					{
						case 1:
							return "Keyboard";					//	3_1_1
						case 2:
							return "Mouse";						//	3_1_2
						case 3:
							return "Tablet";					//	3_1_3
						default:
							return "?";
					}
				default:
					return "?";
			}
		case 7: // "Printer";
			switch (Subclass)
			{
				case 1:
					switch (Protocol)
					{
						case 1:
							return "Unidirectional";			//	7_1_1
						case 2:
							return "Bi-directional";			//	7_1_2
						case 3:
							return "IEEE 1284.4 compatible";	//	7_1_3
						default:
							return "?";
					}
				default:
					return "?";
			}
		default:
			return "?";
	}
}
