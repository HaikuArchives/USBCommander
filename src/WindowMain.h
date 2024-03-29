#ifndef _WINDOWMAIN_H
#define _WINDOWMAIN_H
/*************************************/
/* WindowMain based on BWindow class */
/* Created : 24/2/2003 - 18:6:8      */
/* Code Generated by MeTOS           */
/*************************************/

#include <Window.h>
#include <Button.h>
#include <ListView.h>
#include <ScrollView.h>

class WindowMain : public BWindow
{
public:
	// public functions
	WindowMain(BRect frame,const char *title,window_look look,window_feel feel,uint32 flags,uint32 workspace = B_CURRENT_WORKSPACE);
	virtual	bool 	QuitRequested();
	virtual void	MessageReceived(BMessage* message);

protected:
	// protected members
	BButton			*fButtonInfo;
	BListView		*fListView;
	BScrollView		*fScrollListView;
	BList			 fDevList;	// A list that mirrors the indices of fListView.  I did it this way as I can't see that there is a way to retrieve items from a list of custom list item

};
#endif