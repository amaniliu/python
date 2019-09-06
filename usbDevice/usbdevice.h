/************************************************************************/
/*文件介绍：头文件usbDevice.h
  对应动态链接库usbDevice.dll文件，同时需要配套文件usbDevice.lib*/
/*功能简介：该模块功能主要用于PYTHONZ1200-QZ设备的控制。*/
/*更新时间：2017年3月3日*/

#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#ifndef USB_DEVICE_BUILD
#define USB_DEVICE_API extern __declspec(dllexport)
#else
#define USB_DEVICE_API extern __declspec(dllimport)
#endif

//设备消息
enum Message
{
	start_message,	//开始扫描消息
	stop_message	//停止扫描消息
};

//设备状态
enum Device_Status
{
	connected,		//连接到设备
	removed,		//设备被移除
	ignore			//无效
};

//回调函数：扫描完成后调用，用于传输扫描数据以及数据长度
typedef void (*callback_data)(unsigned char* data, long length);

//回调函数：设备消息调用，用于传输硬件发送的消息指令
typedef void (*callback_message)(int msg);

//打开设备
//参数 callback_data [in]:处理图像扫描数据的回调函数指针
//参数 callback_msg [in]:处理设备消息的回调函数指针。默认值为0
//返回值：true为打开成功，false为失败
//相关函数：close_usb，is_open
USB_DEVICE_API bool open_usb(callback_data callback, callback_message callback_msg = nullptr);

//关闭设备
//停止所有关于设备的后台工作
//相关函数：open_usb
USB_DEVICE_API void close_usb();

//开始扫描
//返回值：true为发送指令成功，false为失败
//相关函数：stop_scan
USB_DEVICE_API bool start_scan();

//停止扫描
//返回值：true为发送指令成功，false为失败
//相关函数：start_scan
USB_DEVICE_API bool stop_scan();

//扫描行数上限
//返回值：扫描图像高度,获取失败返回-1
//相关函数：setLineCount
USB_DEVICE_API long lineCount();

//设置最大扫描图像高度
//参数 length [in]:扫描图像高度。默认值为20000行
//相关函数：lineCount
USB_DEVICE_API void setLineCount(long length = 20000);

//曝光时间
//返回值：曝光时间，单位时钟数,时间换算=时钟数/8M，获取失败返回-1
//相关函数：lineCount
USB_DEVICE_API int exposure();

//设置曝光时间
//参数 time [in]:曝光时长，单位时钟数。时间换算=时钟数/8M
//相关函数：exposure
USB_DEVICE_API void set_exposure(int time);

//编码器分频
//返回值：分频数量,获取失败返回-1
//相关函数：lineCount
USB_DEVICE_API int encode_divide();

//设置编码器分频，1分2，1分3，...1分8
//参数 time [in]:分频数，取值范围2~8
//相关函数：exposure
USB_DEVICE_API void set_encode_divide(int divide);

//编码器分频使能
//返回值：true 为开，false 为关
//相关函数：lineCount
USB_DEVICE_API bool encode_mode();

//编码器分频使能
//参数 enable [in]:编码器类型,true为开，false为关
//相关函数：encode_mode
USB_DEVICE_API void set_encode_mode(bool enable);

//获取设备句柄
//返回值：设备句柄（HANLD）
USB_DEVICE_API void* device_handle();

//获取当前设备状态，判断设备连接上位机的状态
//参数 msg [in]:WinUser.h中tagMSG.message
//参数 wparam [in]:WinUser.h中tagMSG.wParam
//参数 lparam [in]:WinUser.h中tagMSG.lParam
//返回值：设备连接上位机状态。
USB_DEVICE_API Device_Status device_status(unsigned int msg, unsigned int wparam, void* lparam);

//获取当前设备是否已经打开
//返回值:true为打开，false为为打开或者为连接设备
//相关函数：open_usb
USB_DEVICE_API bool is_open();

USB_DEVICE_API bool is_scan();

//获取单个通道像素长度
//返回值：通道像素长度
USB_DEVICE_API int single_width();

//获取通道数量
//返回值：通道数量
USB_DEVICE_API int count_of_channel();


#endif
