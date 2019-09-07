/************************************************************************/
/*文件介绍：头文件ImageProcess.h。
  对应动态链接库ImageProcess.dll文件，
  同时需要配套文件ImageProcess.lib，opencv_core243.dll，opencv_highgui243.dll和opencv_imgproc243.dll*/
/*功能简介：类ImageProcess主要用于图像处理工作，实现对原始图像的校正、拼接以及保存等功能*/
/*更新时间：2017年3月3日*/
/************************************************************************/

#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <vector>

using namespace std;

#ifndef IMAGE_PROCESS_API_BULID
#define IMAGE_PROCESS_API_DLL  __declspec(dllexport)
#else
#define IMAGE_PROCESS_API_DLL  __declspec(dllimport)
#endif

#define PIX_CHANNEL 1272
#define COUNTOF_CHANNEL 6

//结构体：拼接参数（像素偏移量）
//该结构体表示一个通道的顶部，左侧以及右侧的像素的裁剪量
struct PixelOffset
{
    int m_top;		//顶部裁剪量
    int m_left;	//左侧裁剪量
    int m_right;	//右侧裁剪量
};

struct HTS_Point
{
    int x;
    int y;
};

//类：图像处理
//该类主要作用为创建图像，校正，拼接以及保存等功能
class IMAGE_PROCESS_API_DLL ImageProcess
{
public:
	//构造函数
	ImageProcess();

	//构造函数，创建8位图像
	//参数 data [in]:图像原始数据头指针。图像数据空间不会在对象释放时释放，须外部进行管理
	//参数 width [in]:图像像素宽度
	//参数 height [in]:图像像素高度
    ImageProcess(unsigned char* data, const int& width, const int& height);

    //构造函数，创建8位图像, 内部创建width*height的内存空间，由析构函数释放
    //参数 width [in]:图像像素宽度
    //参数 height [in]:图像像素高度
    ImageProcess(const int& width, const int& height);

	//析构函数
    ~ImageProcess();

	//获取图像像素宽度
	//返回值：图像像素宽度
	//相关函数：height，setWidth，setHeight
	int width();

	//获取图像像素高度
	//返回值：图像像素高度
	//相关函数：width，setWidth，setHeight
	int height();

	//设置图像像素宽度
	//参数 value [in]:宽度值（非零整数）
	//相关函数：width，height，setHeight
	void setWidth(int value);

	//设置图像像素高度
	//参数 value [in]:高度值（非零整数）
	//相关函数：width，height，setWidth
	void setHeight(int value);

	//设置图像数据指针
	//
	//参数 data [in]：图像数据头指针。图像数据空间不会在对象释放时释放，须外部进行管理
	//相关函数：bits
	void setData(unsigned char* data);

	//获取图像数据指针
	//返回值：图像数据指针。返回0时，表示为空
	//相关函数：setData
	unsigned char* bits();

	//保存图像文件，格式为8位BMP格式
	//参数 data [in]：图像数据头指针
	//返回值：true为完成，false失败
    bool saveImage(const char* fileName);
	
	//图像数据平场校正，当完成setCorrectData之后使用
	//数据校正须在图像拼接之前使用
	//返回值：true为完成，false失败
	//相关函数：setCorrectData
	bool correct();

	//对比度亮度
	//参数 contrast [in]:对比度偏移量
	//参数 bright [in]:亮度偏移量
	void contrast_and_bright(int contrast, int bright);

	//设置校正数据
	//传入黑白校正原始数据后，会生成最终的校正数据。传入的黑白校正原始数据空间须外部进行管理
	//参数 black [in]:黑色校正数据指针
	//参数 white [in]:白色校正数据指针
	//参数 width [in]:数据宽度。black和white长度须一致
	//相关函数：correct
	void setCorrectData(unsigned char* black, unsigned char* white, int width);

	//图像拼接,生成拼接后的图像对象
	//参数 offset [in]：拼接参数，类型为PixelOffset。详情请参见PixelOffset说明
	//参数 count [in]：offset长度，也表示图像通道数量。默认值为6（6个通道）
	//返回值：拼接后的图像对象
	void montage(PixelOffset* offset, ImageProcess& newImage, int count = COUNTOF_CHANNEL);

	//图像轮廓提取，生成轮廓图像对象
    //参数 thre [in]:灰度图二值化阈值，默认值为100
	//参数 area [in]:轮廓面积过滤，忽略小于area面积的较小轮廓
	//参数 backgroud_is_black [in]：true为黑底白图案，false为白底黑图案。默认值为true
	//参数 optimize [in]：轮廓平滑优化参数，取值范围为[0, 1）。0为不优化，1为最大优化。默认值为0.01
	//返回值：轮廓提取后的图像对象
    void findContour(vector<vector<HTS_Point>>& contours, int thre = 100, int area = 400, bool background_is_black = true, int optimize = 0);

	//图像缩放，生成缩放后的图像对象
	//参数 scale_x [in]:横向缩放比例
	//参数 scale_y [in]:纵向缩放比例
	//返回值：缩放后的图像对象
	void zoom(double scale_x, double scale_y, ImageProcess& newImage);

	//获取横向DPI
	long getBiXPelsPerMeter();

	//获取纵向DPI
	long getBiYPelsPerMeter();

	//设置横向DPI
	void setBiXPelsPerMeter(long pelsPerMeter);

	//设置纵向DPI
	void setBiYPelsPerMeter(long pelsPerMeter);

private:
	void setSize(int width, int height);

private:
	int m_src_width;
	int m_src_height;
    unsigned char* m_data;
	unsigned char* m_data2;
    unsigned char* m_correct_table;
	long m_biXPelsPerMeter;
	long m_biYPelsPerMeter;
};
#endif
