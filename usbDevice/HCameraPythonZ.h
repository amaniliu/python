#pragma once
#include "IHCamera.h"
#include <memory>
#include <thread>
#include <mutex>

class IUsb;
class HCameraPythonZ : public IHCamera
{
public:
	HCameraPythonZ(std::shared_ptr<IUsb> usb);
    virtual ~HCameraPythonZ() override;
	// 通过 IHCamera 继承
	virtual bool open() override;
	virtual void close() override;
	virtual bool is_open() override;
    bool start(image_callback callfunc) override;
    void set_event_call(event_callback event_callfunc) override;
	virtual void stop() override;
	virtual int is_run() override;
	virtual void reset() override;

private:
	void recv_main();
	void Int_main();

	int read_reg(int addr);
	void write_reg(int addr, int value);

	std::shared_ptr<IUsb> m_usb;
	const int buffer_size = 32 * 1024;
	volatile bool m_bScan;
	volatile bool m_bListen;
	std::shared_ptr<unsigned char> m_imBuffer;
	std::shared_ptr<std::thread> m_threadInt;
	std::shared_ptr<std::thread> m_threadrecv;
	std::mutex m_mtxInt;
	image_callback image_call;
	event_callback event_call;
	const int to_device = 0x40;
	const int from_device = 0xc0;
	int linecout = 1000;
	const int sigleWidth = 1272;
	const int count = 6;
	int minCallLine = 100;

	// 通过 IHCamera 继承
	virtual void set_option(Cam_Options option, int value) override;
	virtual int get_option(Cam_Options option) override;
	virtual std::vector<Cam_Options> support_options() override;
};
