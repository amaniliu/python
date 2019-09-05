#pragma once
class IUsb
{
public:
	virtual ~IUsb() {}
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool is_open() = 0;
	virtual bool is_connected() = 0;
	virtual void set_timeout(int timeout) = 0;
	virtual int read_bulk(void* data, int len) = 0;
	virtual int write_bulk(void* data, int len) = 0;
	virtual int read_int(void* data, int len) = 0;
	virtual int control_msg(int rtype, int req, int value, int index, int len, void* data) = 0;
};