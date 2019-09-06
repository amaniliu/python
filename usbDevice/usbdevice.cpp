#include "usbDevice.h"
#include "IHCamera.h"
#include "HCameraLists.h"
#include <iostream>

#define LIBUSB_EXPOSURE 600
#define LIBUSB_DIVIDE 3
#define LIBUSB_DIVIDE_MODE 1
#define LIBUSB_HEIGHT 20000
#define LIBUSB_CHANNELS 6

#define SINGLE_WIDTH

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

static std::shared_ptr<IHCamera> m_camera;

static callback_data m_call_back = nullptr;

void image_call(void* buffer, int height, int width, int type)
{
    (void)type;
    if (m_call_back != nullptr)
        m_call_back(reinterpret_cast<unsigned char*>(buffer), width * height);
}

bool open_usb(callback_data callback, callback_message callback_msg)
{
    auto cameras = HCameraLists::FindAll();
    if (cameras.size() == 0)
    {
        if (m_camera.get())
        {
            m_camera->close();
            m_camera.reset();
        }
        return false;
    }

    m_camera = *cameras.begin();
    if (m_camera.get() && m_camera->open())
    {
        m_camera->set_event_call(static_cast<event_callback>(callback_msg));
        m_camera->set_option(Cam_Options::cam_exposure_gray, LIBUSB_EXPOSURE);
        m_camera->set_option(Cam_Options::cam_divide, LIBUSB_DIVIDE);
        m_camera->set_option(Cam_Options::cam_divide_mode, LIBUSB_DIVIDE_MODE);
        m_camera->set_option(Cam_Options::cam_height, LIBUSB_HEIGHT);
        m_call_back = callback;
        return true;
    }
    else
    {
        m_camera.reset();
        m_call_back = nullptr;
        return false;
    }
}

void close_usb()
{
    m_camera.reset();
}

bool start_scan()
{
    if (m_camera.get())
        return m_camera->start(image_call);
   return false;
}

bool stop_scan()
{
    if (m_camera.get())
    {
        m_camera->stop();
        return true;
    }
    return false;
}

int single_width()
{
	if (m_camera.get())
		return m_camera->get_option(Cam_Options::cam_width) / LIBUSB_CHANNELS;
	return 0;
}

long lineCount()
{
	if (m_camera.get())
		return m_camera->get_option(Cam_Options::cam_height);
	return -1;
}

void setLineCount(long length)
{
	if (m_camera.get())
		m_camera->set_option(Cam_Options::cam_height, static_cast<int>(length));
}

int exposure()
{
	if (m_camera.get())
		return m_camera->get_option(Cam_Options::cam_exposure_gray);
	return -1;
}

void set_exposure(int time)
{
	if (m_camera.get())
		m_camera->set_option(Cam_Options::cam_exposure_gray, time);
}

int encode_divide()
{
	if (m_camera.get())
		return m_camera->get_option(Cam_Options::cam_divide) + 2;
	return -1;
}

void set_encode_divide(int divide)
{
	int div = max(2, min(divide, 8));
	if (m_camera.get())
		m_camera->set_option(Cam_Options::cam_divide, divide - 2);
}

bool encode_mode()
{
	if (m_camera.get())
		return m_camera->get_option(Cam_Options::cam_divide_mode) == 0;
	return false;
}

void set_encode_mode(bool enable)
{
	if (m_camera.get())
		m_camera->set_option(Cam_Options::cam_divide_mode, enable ? 0 : 1);
}

bool is_scan()
{
    if (m_camera.get())
        return m_camera->is_run();
	return false;
}

int count_of_channel()
{
    return LIBUSB_CHANNELS;
}

Device_Status device_status(unsigned int msg, unsigned int wparam, void* lparam)
{
    (void)lparam;
    if (msg == 0x0219/*WM_DEVICECHANGE*/)
    {
        if (wparam == 0x0007/*DBT_DEVNODES_CHANGED*/)
        {
            if (HCameraLists::FindAll().empty())
            {
                m_call_back = nullptr;
                m_camera.reset();
                return removed;
            }
            else
            {
                return connected;
            }
        }
    }
	return ignore;
}

void* device_handle()
{
    if (m_camera.get())
        return &m_camera;
    return nullptr;
}

bool is_open()
{
    if (m_camera.get())
        return true;
    else
        return false;
}
