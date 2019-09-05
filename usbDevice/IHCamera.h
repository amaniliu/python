#pragma once
#include <vector>
#include "htdevdefs.h"


typedef void(*image_callback)(void*, int, int, int);
typedef void(*event_callback)(int);

enum Cam_Options {
	cam_mode,  //!< color, gray
	cam_frequency,
	cam_divide,
	cam_divide_mode,
	cam_exposure_gray,
	cam_exposure_green,
	cam_exposure_blue,
	cam_exposure_red,
	cam_user_out,
	cam_user_in,
	cam_width,
	cam_height,
	cam_trigger_mode,
	cam_trigger_sig,
	cam_status
};

class /*HTDEVICE_SHARED_EXPORT*/ IHCamera
{
public:
    virtual ~IHCamera() {}
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual bool is_open() = 0;
    virtual bool start(image_callback imagecall= nullptr) = 0;
	virtual void stop() = 0;
	virtual int is_run() = 0;
	virtual void reset() = 0;
	virtual void set_event_call(event_callback event_callfunc) = 0;
	virtual void set_option(Cam_Options option, int value) = 0;
	virtual int get_option(Cam_Options option) = 0;
	virtual std::vector<Cam_Options> support_options() = 0;
};

