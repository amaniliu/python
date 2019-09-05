#include "CyUsbEx.h"
#include "lib/cyusb/include/CyAPI.h"

CyUsbEx::CyUsbEx(int index)
{
	m_index = index;
	m_timeout = 100;
}

bool CyUsbEx::open()
{
	if (is_open())
		return true;

	m_usb.reset(new CCyUSBDevice());
    m_usb->Open(static_cast<UCHAR>(m_index));
	if (m_usb->IsOpen())
	{
        m_usb->BulkOutEndPt->TimeOut = static_cast<ULONG>(m_timeout);
        m_usb->BulkInEndPt->TimeOut = static_cast<ULONG>(m_timeout);
        m_usb->InterruptInEndPt->TimeOut = static_cast<ULONG>(m_timeout);
	}

	return is_open();
}

bool CyUsbEx::close()
{
	return false;
}

bool CyUsbEx::is_open()
{
    if (m_usb.get() != nullptr)
		return m_usb->IsOpen();

	return false;
}

bool CyUsbEx::is_connected()
{
	return is_open();
}

void CyUsbEx::set_timeout(int timeout)
{
	m_timeout = timeout;
}

int CyUsbEx::read_bulk(void* data, int len)
{
	LONG llen = len;
    m_usb->BulkInEndPt->XferData(reinterpret_cast<UCHAR*>(data), llen);
	return llen;
}

int CyUsbEx::write_bulk(void* data, int len)
{
	LONG llen = len;
    m_usb->BulkOutEndPt->XferData(reinterpret_cast<UCHAR*>(data), llen);
	return llen;
}

int CyUsbEx::read_int(void* data, int len)
{
	LONG llen = len;
    m_usb->InterruptInEndPt->XferData(reinterpret_cast<UCHAR*>(data), llen);
	return llen;
}

int CyUsbEx::control_msg(int rtype, int req, int value, int index, int len, void* data)
{
	if (!m_usb.get() || !m_usb->ControlEndPt)
		return -1;

    m_usb->ControlEndPt->Index = static_cast<USHORT>(index);
    m_usb->ControlEndPt->Value = static_cast<USHORT>(value);
    m_usb->ControlEndPt->ReqType = static_cast<CTL_XFER_REQ_TYPE>((rtype >> 5) & 0x03);
    m_usb->ControlEndPt->Direction = static_cast<CTL_XFER_DIR_TYPE>(rtype >> 7);//
    m_usb->ControlEndPt->Target = static_cast<CTL_XFER_TGT_TYPE>(rtype & 0x3);
    m_usb->ControlEndPt->ReqCode = static_cast<UCHAR>(req);
	LONG llen = len;
    m_usb->ControlEndPt->XferData(reinterpret_cast<UCHAR*>(data), llen);
	return llen;
}
