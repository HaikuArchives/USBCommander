#ifndef _MYROSTER_H
#define _MYROSTER_H
// MyRoster.h

#include "USBKit.h"

class MyUSBRoster : public USBRoster
{
public:
	virtual status_t DeviceAdded(USBDevice *dev);
	virtual void DeviceRemoved(USBDevice *dev);
	void	SetMainWin(BLooper *win) { fMainWin = win; }
//protected:
//	ApplicationUsbWatcher	* _pApp;
//public:
//	void	SetApplication(ApplicationUsbWatcher * app);
private:
	BLooper	*fMainWin;	// For sending messages to
};
#endif