#include "libusbex.h"
#include <libusb-1.0/libusb.h>
#include <memory>

class CtxA
{
public:
    CtxA()
        :ctx(nullptr)
    {
        libusb_init(&ctx);
    }

    ~CtxA()
    {
        libusb_exit(ctx);
    }

    libusb_context* ctx;
};

static std::auto_ptr<CtxA> ctxa;

class Clibusb_device_handle
{
public:
    Clibusb_device_handle()
    : ldh (nullptr)
    {
        if (!ctxa.get())
        {
            ctxa.reset(new CtxA);
        }
    }

    ~Clibusb_device_handle()
    {
        close();
    }

    int open(uint16_t vendor_id, uint16_t product_id)
    {
        if (ldh != nullptr)
        {
            close();
        }
		libusb_device** list;
        libusb_device* found = nullptr;
        ssize_t cnt = libusb_get_device_list(nullptr, &list);
		ssize_t i = 0;
        int err = 0;

        (void)found;(void)cnt;(void)i;(void)err;    //消除未使用变量的警告

		libusb_free_device_list(list, 1);
        ldh = libusb_open_device_with_vid_pid(ctxa->ctx, vendor_id, product_id);
        if(ldh != nullptr)
        {
           // libusb_claim_interface(ldh, 0);
        }

        return ldh != nullptr;
    }

    void close()
    {
        if (ldh != nullptr)
        {
            libusb_release_interface(ldh, 0); //release the claimed interface
            libusb_close(ldh);
            ldh = nullptr;
        }
    }

    libusb_device_handle* get()
    {
        return ldh;
    }

private:
    libusb_device_handle* ldh;
};


LibUsbEx::LibUsbEx()
{
    m_usb.reset(new Clibusb_device_handle);
    eps[EP_INT_IN] = 0x81;
    eps[EP_BULK_IN] = 0x82;
    eps[EP_BULK_OUT] = 0x02;
	timeout = 100;
}

bool LibUsbEx::open()
{
    return m_usb->open(0x3072, 0x7824);;
}

bool LibUsbEx::close()
{
    m_usb->close();
    return true;
}

bool LibUsbEx::is_open()
{

    return m_usb.get() != nullptr;
}

bool LibUsbEx::is_connected()
{
    return false;
}

void LibUsbEx::set_timeout(int timeout)
{
  this->timeout = timeout;
}

int LibUsbEx::read_bulk(void *data, int len)
{
    libusb_bulk_transfer(m_usb->get(), static_cast<UCHAR>(eps[EP_BULK_IN]),
            reinterpret_cast<UCHAR*>(data),  len, &len, static_cast<size_t>(timeout));
    return len;
}

int LibUsbEx::write_bulk(void *data, int len)
{
    libusb_bulk_transfer(m_usb->get(), static_cast<UCHAR>(eps[EP_BULK_OUT]),
            reinterpret_cast<UCHAR*>(data),  len, &len, static_cast<size_t>(timeout));
    return len;
}

int LibUsbEx::read_int(void *data, int len)
{
    libusb_bulk_transfer(m_usb->get(), static_cast<UCHAR>(eps[EP_INT_IN]),
                         reinterpret_cast<UCHAR*>(data),  len, &len, static_cast<size_t>(timeout));
    return len;
}

int LibUsbEx::control_msg(int rtype, int req, int value, int index, int len, void *data)
{
    return libusb_control_transfer(m_usb->get(), static_cast<UCHAR>(rtype),
                                   static_cast<UCHAR>(req), static_cast<USHORT>(value),
                                   static_cast<USHORT>(index), reinterpret_cast<UCHAR*>(data),
                                   static_cast<USHORT>(len), static_cast<UINT>(timeout));
}
