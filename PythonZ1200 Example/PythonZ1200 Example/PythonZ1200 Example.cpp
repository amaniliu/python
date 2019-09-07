// PythonZ1200 Example.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

#include "include/imageprocess.h"
#include "include/usbdevice.h"

using namespace std;

#define SINGLE_WIDTH single_width()
#define COUNTOF_CHANNEL 6

//获取拼接参数
void getMontagePrm(PixelOffset* prm, int length = COUNTOF_CHANNEL)
{
	char fileName[MAX_PATH];
	GetModuleFileName(NULL, fileName, sizeof(fileName));
	strncpy(strrchr(fileName, '\\'), "\\config.ini\0", 12);
	char section[] = "channelX\0";
	char* ptr = strrchr(section, 'X');
	for (int i = 0; i < length; i++)
	{
		_itoa(i, ptr, 10);
		prm[i].m_left = GetPrivateProfileInt(section, "left", 0, fileName);		//
		prm[i].m_right = GetPrivateProfileInt(section, "right", 0, fileName);	//
		prm[i].m_top = GetPrivateProfileInt(section, "top", 0, fileName);		//
	}

}

//加载校正数据
void getCorrectData(ImageProcess* imageProcess, string filename = "correctData.dat")
{
	ifstream f(filename, ios::binary | ios::in);

	if (!f.is_open())
	{
		f.close();
		return;
	}

	unsigned char* m_buffer_black = new unsigned char[SINGLE_WIDTH * COUNTOF_CHANNEL];
	unsigned char* m_buffer_white = new unsigned char[SINGLE_WIDTH * COUNTOF_CHANNEL];

	f.read(reinterpret_cast<char*>(m_buffer_black), SINGLE_WIDTH * COUNTOF_CHANNEL);
	f.read(reinterpret_cast<char*>(m_buffer_white), SINGLE_WIDTH * COUNTOF_CHANNEL);

	f.close();

	imageProcess->setCorrectData(m_buffer_black, m_buffer_white, SINGLE_WIDTH * COUNTOF_CHANNEL);

	delete[] m_buffer_black;
	delete[] m_buffer_white;
}

//图像处理：包括校正，拼接，和保存图像文件
void imageProcess(unsigned char* buffer, long length)
{
	//备份buffer
	unsigned char* new_buffer = new unsigned char[static_cast<unsigned int>(length)];
	memcpy(new_buffer, buffer, static_cast<unsigned int>(length));

	//创建图片
	int width = single_width() * count_of_channel();
	int height = length / width;

	ImageProcess imgproc;
	imgproc.setWidth(width);
	imgproc.setHeight(height);
	imgproc.setData(new_buffer);

	//校正
	getCorrectData(&imgproc);
	imgproc.correct();
	printf("correct\n\n");

	//拼接
	PixelOffset offset[COUNTOF_CHANNEL];
	getMontagePrm(offset);
	ImageProcess stitch;
	imgproc.montage(offset, stitch, COUNTOF_CHANNEL);
	printf("montage\n\n");

	//保存图片
	stitch.saveImage("PythonZ1200-Exmaple.bmp");
	printf("save\n\n");
}

//回调函数，获取描完成后的图像数据，并进行图像处理
void callback_getPicInfo(unsigned char* buffer, long length)
{
	//图像处理
	imageProcess(buffer, length);
	int a = 0;
}

//回调函数，获取设备状态消息
void callback_reciveMsg(int msg)
{
	if (msg == 0)	//当msg为0时，位设备启动扫描
	{
		printf("Start Scanning!\n");
	}
	else if (msg == 1)	//当msg为1时，位设备停止扫描
	{
		printf("Stop Scanning!\n");
	}
}

int main()
{
	//打开设备
	bool result = open_usb(callback_getPicInfo, callback_reciveMsg);

	//判断是否打开设备成功
	if (is_open())
	{
		printf("Open device successfully!\n");
	}
	else
	{
		printf("Open device failed!\n");
		getchar();
		return 0;
	}
	//设置最大幅面为20000行数据
	setLineCount(20000);

	//开始扫描

	printf("Press enter to start scanning!\n");
	getchar();
	start_scan();
	printf("Start Scanning!\n");

	printf("Press enter to stop scanning!\n");
	getchar();

	//停止扫描
	stop_scan();
	printf("Press enter to close USB!\n");
	getchar();

	//关闭设备
	close_usb();
	printf("Close USB!\n");

	getchar();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
