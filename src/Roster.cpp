extern class ApplicationUsbWatcher app;

void	Roster::SetApplication(ApplicationUsbWatcher * app) {
	_pApp = app;
}
	
virtual status_t Roster::DeviceAdded(USBDevice *dev){
	fprintf(stderr,"added %s @ '%s'\n",
			dev->IsHub() ? "hub" : "device", dev->Location());
	if (_pApp)
		_pApp->SetText("Added hub");
	return B_OK;
}
virtual void Roster::DeviceRemoved(USBDevice *dev){
	//fprintf(stderr,"removed %s @ '%s'\n",
	//		dev->IsHub() ? "hub" : "device", dev->Location());
	;
}	
