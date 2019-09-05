#include "HCameraPythonZ.h"
#include "IUsb.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <Windows.h>

#if defined(_DEBUG) && defined(QT_VERSION)
#include <QDebug>
#endif

using namespace std;

union CamZ_Reg_5_6
{
	unsigned short exposure[2];
	int value;
};

union CamZ_Reg_4
{
	int value;
	struct
	{	
		int bit1_2 : 2;
		int mode : 1;
		int user_io_out : 2;
		int encode_divide : 3;
		int encode_mode : 1;
		int reserved : 23;
	} val;
};

union CamZ_Reg_2
{
	int value;
	struct
	{
		int over : 1;
		int usbfull : 1;
		int backempty : 1;
		int empty_sdram : 1;
		int General_in_usb : 2;
		int General_int_interface : 1;
		int reserved : 25;
	}val;
};

HCameraPythonZ::HCameraPythonZ(std::shared_ptr<IUsb> usb)
{
	m_bScan = false;
	m_bListen = false;
	m_usb = usb;
    event_call = nullptr;
    image_call = nullptr;
    m_imBuffer.reset(new unsigned char[static_cast<size_t>(linecout*sigleWidth*count + buffer_size)](), std::default_delete<unsigned char[]>());
}

HCameraPythonZ::~HCameraPythonZ()
{
	close();
}

bool HCameraPythonZ::open()
{
	if (m_usb.get() && m_usb->open()) {
		m_bListen = true;
		m_threadInt.reset(new std::thread(&HCameraPythonZ::Int_main, this));
		m_usb->set_timeout(100);
		m_usb->read_bulk(m_imBuffer.get(), ((sigleWidth * count * linecout) / buffer_size) * buffer_size);
		m_usb->set_timeout(200);
		return true;
	}
	return false;
}

void HCameraPythonZ::close()
{
	if (m_usb.get()) {
		stop();

		if (m_threadInt.get() && m_threadInt->joinable()) {
			m_bListen = false;
#if defined(_DEBUG) && defined(QT_VERSION)
			qDebug("close: threadint join");
#endif
			m_threadInt->join();
		}
#if defined(_DEBUG) && defined(QT_VERSION)
		qDebug("close: threadint joined");
#endif
		m_threadInt.reset();
		m_usb->close();
	}
}

bool HCameraPythonZ::is_open()
{
	if (m_usb.get())
		return m_usb->is_open();
	return false;
}

bool HCameraPythonZ::start(image_callback callfunc)
{
	int ready = 1;

	if (m_usb->control_msg(to_device, 0xe1, 0, 0, sizeof(ready), &ready)) {
		m_bScan = true;
		image_call = callfunc;
		m_threadrecv.reset(new std::thread(&HCameraPythonZ::recv_main, this));
	}
	return true;
}

void HCameraPythonZ::set_event_call(event_callback callfunc)
{
	event_call = callfunc;
}

void HCameraPythonZ::stop()
{
	int over = 0;
	m_usb->control_msg(to_device, 0xe1, 0, 0, sizeof(over), &over);
	m_bScan = false;
	if (m_threadrecv.get() && m_threadrecv->joinable()) {
#if defined(_DEBUG) && defined(QT_VERSION)
		qDebug("stop:m_threadrecv join");
#endif
		m_threadrecv->join();
	}
#if defined(_DEBUG) && defined(QT_VERSION)
	qDebug("stop:m_threadrecv joined");
#endif

	m_threadrecv.reset();
}

int HCameraPythonZ::is_run()
{
	return m_bScan;
}

void HCameraPythonZ::reset()
{

}

void HCameraPythonZ::recv_main()
{
	long length;
	unsigned long offset = 0;
    unsigned long  imsize = static_cast<unsigned long>(sigleWidth * count * linecout);
	while (m_bScan) {
		length = buffer_size;
		length = m_usb->read_bulk(m_imBuffer.get() + offset, length);

		if (length > 0) {
            offset += static_cast<unsigned long>(length);
			if (offset >= imsize){
				if (image_call) {
					image_call(m_imBuffer.get(), linecout, sigleWidth * count, 0);
				}
				offset -= imsize;
				memcpy(m_imBuffer.get(), m_imBuffer.get() + imsize, offset);
			}
		}
	}

	if (m_usb.get())
	{
		m_usb->set_timeout(100);
		m_usb->read_bulk(m_imBuffer.get(), ((sigleWidth * count * linecout) / buffer_size) * buffer_size);
		m_usb->set_timeout(200);
	}

    if (offset > static_cast<unsigned long>(sigleWidth * count * minCallLine)) {
		if (image_call) {
            image_call(m_imBuffer.get(), static_cast<int>(offset) / (sigleWidth * count), sigleWidth * count, 0);
		}
	}

#if defined(_DEBUG) && defined(QT_VERSION)
    qDebug() << "recv_main:exit";
#endif
}

void HCameraPythonZ::Int_main()
{
	unsigned char data[64];
	while (m_bListen) {
		if (m_usb->read_int(data, sizeof(data))) {
			if (event_call) {
#if defined(_DEBUG) && defined(QT_VERSION)
				qDebug("Int_main:call in");
#endif
				event_call(data[0]);
#if defined(_DEBUG) && defined(QT_VERSION)
				qDebug("Int_main:call out");
#endif
			}
		}
	}
#if defined(_DEBUG) && defined(QT_VERSION)
	qDebug("Int_main:exit");
#endif
}

int HCameraPythonZ::read_reg(int addr)
{
	int value;
	m_usb->control_msg(from_device, 0xb0, 0, addr, sizeof(value), &value);
	return value;
}

void HCameraPythonZ::write_reg(int addr, int value)
{
	m_usb->control_msg(to_device, 0xb0, 0, addr, sizeof(value), &value);
}

void HCameraPythonZ::set_option(Cam_Options option, int value)
{
	switch (option)
	{
	case cam_mode:
	{
		CamZ_Reg_4 reg4;
		reg4.value = read_reg(0x04);
		reg4.val.mode = value;
		write_reg(0x04, reg4.value);
	}
        break;
	case cam_frequency:
		break;
	case cam_divide:
	{
		CamZ_Reg_4 reg4;
		reg4.value = read_reg(0x04);
		reg4.val.encode_divide = value;
		write_reg(0x04, reg4.value);
	}
        break;
	case cam_divide_mode:
	{
		CamZ_Reg_4 reg4;
		reg4.value = read_reg(0x04);
		reg4.val.encode_mode = value;
		write_reg(0x04, reg4.value);
	}
        break;
	case cam_exposure_gray:
	{
		CamZ_Reg_5_6 reg5;
		reg5.value = read_reg(0x05);
        reg5.exposure[0] = static_cast<USHORT>(value);
		write_reg(0x05, reg5.value);
	}
        break;
	case cam_exposure_green:
	{
		CamZ_Reg_5_6 reg6;
		reg6.value = read_reg(0x06);
        reg6.exposure[0] = static_cast<USHORT>(value);
		write_reg(0x06, reg6.value);
	}
        break;
	case cam_exposure_blue:
	{
		CamZ_Reg_5_6 reg6;
		reg6.value = read_reg(0x06);
        reg6.exposure[1] = static_cast<USHORT>(value);
		write_reg(0x06, reg6.value);
    }
        break;
	case cam_exposure_red:
	{
		CamZ_Reg_5_6 reg5;
		reg5.value = read_reg(0x05);
        reg5.exposure[1] = static_cast<USHORT>(value);
		write_reg(0x05, reg5.value);
    }
        break;
	case cam_user_out:
	{
		CamZ_Reg_4 reg4;
		reg4.value = read_reg(0x04);
		reg4.val.user_io_out = value;
		write_reg(0x04, reg4.value);
	}
        break;
	case cam_user_in:
		write_reg(0x02, value);
		break;
	case cam_width:
		break;
	case cam_height:
		linecout = max(1, min(value, 30000));
        m_imBuffer.reset(new unsigned char[static_cast<size_t>(linecout * sigleWidth * count + buffer_size)](), std::default_delete<unsigned char[]>());
		break;
	default:
		break;
	}
}

int HCameraPythonZ::get_option(Cam_Options option)
{
	int value = 0;
	switch (option)
	{
	case cam_mode:
	{
		CamZ_Reg_4 reg4;
		reg4.value = read_reg(0x04);
		value = reg4.val.mode;
	}
		break;
	case cam_frequency:
		break;
	case cam_divide:
	{
		CamZ_Reg_4 reg4;
		reg4.value = read_reg(0x04);
		value = reg4.val.encode_divide;
	}
		break;
	case cam_divide_mode:
	{
		CamZ_Reg_4 reg4;
		reg4.value = read_reg(0x04);
		value = reg4.val.encode_mode;
	}
		break;
	case cam_exposure_gray:
	{
		CamZ_Reg_5_6 reg5;
		reg5.value = read_reg(0x05);
		value = reg5.exposure[0];
	}
		break;
	case cam_exposure_green:
	{
		CamZ_Reg_5_6 reg6;
		reg6.value = read_reg(0x06);
		value = reg6.exposure[0];
	}
		break;
	case cam_exposure_blue:
	{
		CamZ_Reg_5_6 reg6;
		reg6.value = read_reg(0x06);
		value = reg6.exposure[1];
	}
		break;
	case cam_exposure_red:
	{
		CamZ_Reg_5_6 reg5;
		reg5.value = read_reg(0x05);
		value = reg5.exposure[1];
	}
		break;
	case cam_user_out:
	{
		CamZ_Reg_4 reg4;
		reg4.value = read_reg(0x04);
		value = reg4.val.user_io_out;
	}
		break;
	case cam_user_in:
		value = read_reg(0x02);
		break;
	case cam_width:
		value = sigleWidth * count;
		break;
	case cam_height:
		value = linecout;
		break;
	default:
		break;
	}
	return value;
}

std::vector<Cam_Options> HCameraPythonZ::support_options()
{
	std::set<Cam_Options>  options;
	options.insert(Cam_Options::cam_divide);
	options.insert(Cam_Options::cam_width);
	options.insert(Cam_Options::cam_height);
	options.insert(Cam_Options::cam_exposure_blue);
	options.insert(Cam_Options::cam_exposure_gray);
	options.insert(Cam_Options::cam_exposure_red);

	return std::vector<Cam_Options>(options.begin(), options.end());
}
