/*****************************************************/
/* ApplicationUsbWatcher based on BApplication class */
/* Created : 24/2/2003 - 18:6:8                      */
/* Code Generated by MeTOS                           */
/*****************************************************/

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
 
#include "ApplicationUsbWatcher.h"

#include <stdio.h>
//#include <iostream.h>
#include <Roster.h>
#include "WindowMain.h"
//#include "USBKit.h"
#include "Messages.h"
#include "MyRoster.h"

// Global variable
class ApplicationUsbWatcher *app = NULL;

/**** main function ****/
int main(void)
{
	//ApplicationUsbWatcher application("application/x-vnd.MeTOS.Application");
	app = new ApplicationUsbWatcher("application/x-vnd.MeTOS.Application");
	// Start Application
	//application.Run();
	app->Run();
	
	delete app;

	return 0;
}


/***** Constructor ****/
ApplicationUsbWatcher::ApplicationUsbWatcher(const char *signature)
: BApplication(signature)
{
	// Allocate object
	_windowmain = new WindowMain(BRect(100.00,100.00,480.00,255.00),"USB Commander 0.1", B_DOCUMENT_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,B_NOT_ZOOMABLE,0);

	// Adding object
	puts("show win");
	_windowmain->Show();
}

/***** ReadyToRun ****/
void ApplicationUsbWatcher::ReadyToRun()
{	
	puts("Ready to run");

	puts("Ready to run end");
}

void ApplicationUsbWatcher::MessageReceived(BMessage* message)
{
	static bool	rosterStarted = FALSE;
	MyUSBRoster *myUSBRoster;
	
	switch(message->what)
	{
		case B_SOME_APP_ACTIVATED:
			puts("Some app activated");
			if (!rosterStarted)
			{
				myUSBRoster = new MyUSBRoster();
				myUSBRoster->SetMainWin(_windowmain);
				myUSBRoster->Start();
				rosterStarted = TRUE;
			}
			break;
		
		default:
			//printf("App messageReceived %ld\n", message->what);
			//message->PrintToStream();
			BApplication::MessageReceived(message);
	}
	
}

void ApplicationUsbWatcher::AppActivated(bool active)
{
	printf("AppActivated %d\n", active);
}



