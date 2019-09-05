#include "UsbLists.h"
#include "lib/cyusb/include/CyAPI.h"
#include "CyUsbEx.h"
#include "libusbex.h"

std::list<std::shared_ptr<IUsb>> UsbLists::find_all()
{
	return std::list<std::shared_ptr<IUsb>>();
}

std::list<std::shared_ptr<IUsb>> UsbLists::find_vid_pid(int vid, int pid)
{
    (void)vid;
    (void)pid;
	std::list<std::shared_ptr<IUsb>> usblists;

#ifdef WIN32
	CCyUSBDevice usbDevice;
	for (int i = 0; i< usbDevice.DeviceCount(); i++) {
		usblists.push_back(std::shared_ptr<IUsb>(new CyUsbEx(i)));
	}
#elif defined(WIN64)

#endif
	return usblists;
}
