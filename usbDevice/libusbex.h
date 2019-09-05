#ifndef LIBUSBEX_H
#define LIBUSBEX_H
#include "IUsb.h"
#include <memory>

class Clibusb_device_handle;

class LibUsbEx : public IUsb
{
public:
    LibUsbEx();
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
    const int epnum = 3;
    enum EP_TYPE
    {
        EP_INT_IN,
        EP_BULK_IN,
        EP_BULK_OUT
    };

    int timeout;
    int eps[3];

    std::shared_ptr<Clibusb_device_handle> m_usb;
};

#endif // LIBUSBEX_H
