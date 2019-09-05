#pragma once
#include "IUsb.h"
#include <memory>

class CCyUSBDevice;

class CyUsbEx :
	public IUsb
{
public:
	CyUsbEx(int index);
	// Í¨¹ý IUsb ¼Ì³Ð
	virtual bool open() override;
	virtual bool close() override;
	virtual bool is_open() override;
	virtual bool is_connected() override;
	virtual void set_timeout(int timeout) override;
	virtual int read_bulk(void* data, int len) override;
	virtual int write_bulk(void* data, int len) override;
	virtual int read_int(void* data, int len) override;
	virtual int control_msg(int rtype, int req, int value, int index, int len, void* data) override;

private:
	std::shared_ptr<CCyUSBDevice> m_usb;
	int m_index;
	int m_timeout;
};

