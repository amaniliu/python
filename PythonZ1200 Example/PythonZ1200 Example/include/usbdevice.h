/************************************************************************/
/*�ļ����ܣ�ͷ�ļ�usbDevice.h
  ��Ӧ��̬���ӿ�usbDevice.dll�ļ���ͬʱ��Ҫ�����ļ�usbDevice.lib*/
/*���ܼ�飺��ģ�鹦����Ҫ����PYTHONZ1200-QZ�豸�Ŀ��ơ�*/
/*����ʱ�䣺2017��3��3��*/

#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#ifndef USB_DEVICE_BUILD
#define USB_DEVICE_API extern __declspec(dllexport)
#else
#define USB_DEVICE_API extern __declspec(dllimport)
#endif

//�豸��Ϣ
enum Message
{
	start_message,	//��ʼɨ����Ϣ
	stop_message	//ֹͣɨ����Ϣ
};

//�豸״̬
enum Device_Status
{
	connected,		//���ӵ��豸
	removed,		//�豸���Ƴ�
	ignore			//��Ч
};

//�ص�������ɨ����ɺ���ã����ڴ���ɨ�������Լ����ݳ���
typedef void (*callback_data)(unsigned char* data, long length);

//�ص��������豸��Ϣ���ã����ڴ���Ӳ�����͵���Ϣָ��
typedef void (*callback_message)(int msg);

//���豸
//���� callback_data [in]:����ͼ��ɨ�����ݵĻص�����ָ��
//���� callback_msg [in]:�����豸��Ϣ�Ļص�����ָ�롣Ĭ��ֵΪ0
//����ֵ��trueΪ�򿪳ɹ���falseΪʧ��
//��غ�����close_usb��is_open
USB_DEVICE_API bool open_usb(callback_data callback, callback_message callback_msg = nullptr);

//�ر��豸
//ֹͣ���й����豸�ĺ�̨����
//��غ�����open_usb
USB_DEVICE_API void close_usb();

//��ʼɨ��
//����ֵ��trueΪ����ָ��ɹ���falseΪʧ��
//��غ�����stop_scan
USB_DEVICE_API bool start_scan();

//ֹͣɨ��
//����ֵ��trueΪ����ָ��ɹ���falseΪʧ��
//��غ�����start_scan
USB_DEVICE_API bool stop_scan();

//ɨ����������
//����ֵ��ɨ��ͼ��߶�,��ȡʧ�ܷ���-1
//��غ�����setLineCount
USB_DEVICE_API long lineCount();

//�������ɨ��ͼ��߶�
//���� length [in]:ɨ��ͼ��߶ȡ�Ĭ��ֵΪ20000��
//��غ�����lineCount
USB_DEVICE_API void setLineCount(long length = 20000);

//�ع�ʱ��
//����ֵ���ع�ʱ�䣬��λʱ����,ʱ�任��=ʱ����/8M����ȡʧ�ܷ���-1
//��غ�����lineCount
USB_DEVICE_API int exposure();

//�����ع�ʱ��
//���� time [in]:�ع�ʱ������λʱ������ʱ�任��=ʱ����/8M
//��غ�����exposure
USB_DEVICE_API void set_exposure(int time);

//��������Ƶ
//����ֵ����Ƶ����,��ȡʧ�ܷ���-1
//��غ�����lineCount
USB_DEVICE_API int encode_divide();

//���ñ�������Ƶ��1��2��1��3��...1��8
//���� time [in]:��Ƶ����ȡֵ��Χ2~8
//��غ�����exposure
USB_DEVICE_API void set_encode_divide(int divide);

//��������Ƶʹ��
//����ֵ��true Ϊ����false Ϊ��
//��غ�����lineCount
USB_DEVICE_API bool encode_mode();

//��������Ƶʹ��
//���� enable [in]:����������,trueΪ����falseΪ��
//��غ�����encode_mode
USB_DEVICE_API void set_encode_mode(bool enable);

//��ȡ�豸���
//����ֵ���豸�����HANLD��
USB_DEVICE_API void* device_handle();

//��ȡ��ǰ�豸״̬���ж��豸������λ����״̬
//���� msg [in]:WinUser.h��tagMSG.message
//���� wparam [in]:WinUser.h��tagMSG.wParam
//���� lparam [in]:WinUser.h��tagMSG.lParam
//����ֵ���豸������λ��״̬��
USB_DEVICE_API Device_Status device_status(unsigned int msg, unsigned int wparam, void* lparam);

//��ȡ��ǰ�豸�Ƿ��Ѿ���
//����ֵ:trueΪ�򿪣�falseΪΪ�򿪻���Ϊ�����豸
//��غ�����open_usb
USB_DEVICE_API bool is_open();

USB_DEVICE_API bool is_scan();

//��ȡ����ͨ�����س���
//����ֵ��ͨ�����س���
USB_DEVICE_API int single_width();

//��ȡͨ������
//����ֵ��ͨ������
USB_DEVICE_API int count_of_channel();


#endif