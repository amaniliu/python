/************************************************************************/
/*�ļ����ܣ�ͷ�ļ�ImageProcess.h��
  ��Ӧ��̬���ӿ�ImageProcess.dll�ļ���
  ͬʱ��Ҫ�����ļ�ImageProcess.lib��opencv_core243.dll��opencv_highgui243.dll��opencv_imgproc243.dll*/
/*���ܼ�飺��ImageProcess��Ҫ����ͼ��������ʵ�ֶ�ԭʼͼ���У����ƴ���Լ�����ȹ���*/
/*����ʱ�䣺2017��3��3��*/
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

//�ṹ�壺ƴ�Ӳ���������ƫ������
//�ýṹ���ʾһ��ͨ���Ķ���������Լ��Ҳ�����صĲü���
struct PixelOffset
{
    int m_top;		//�����ü���
    int m_left;	//���ü���
    int m_right;	//�Ҳ�ü���
};

struct HTS_Point
{
    int x;
    int y;
};

//�ࣺͼ����
//������Ҫ����Ϊ����ͼ��У����ƴ���Լ�����ȹ���
class IMAGE_PROCESS_API_DLL ImageProcess
{
public:
	//���캯��
	ImageProcess();

	//���캯��������8λͼ��
	//���� data [in]:ͼ��ԭʼ����ͷָ�롣ͼ�����ݿռ䲻���ڶ����ͷ�ʱ�ͷţ����ⲿ���й���
	//���� width [in]:ͼ�����ؿ��
	//���� height [in]:ͼ�����ظ߶�
    ImageProcess(unsigned char* data, const int& width, const int& height);

    //���캯��������8λͼ��, �ڲ�����width*height���ڴ�ռ䣬�����������ͷ�
    //���� width [in]:ͼ�����ؿ��
    //���� height [in]:ͼ�����ظ߶�
    ImageProcess(const int& width, const int& height);

	//��������
    ~ImageProcess();

	//��ȡͼ�����ؿ��
	//����ֵ��ͼ�����ؿ��
	//��غ�����height��setWidth��setHeight
	int width();

	//��ȡͼ�����ظ߶�
	//����ֵ��ͼ�����ظ߶�
	//��غ�����width��setWidth��setHeight
	int height();

	//����ͼ�����ؿ��
	//���� value [in]:���ֵ������������
	//��غ�����width��height��setHeight
	void setWidth(int value);

	//����ͼ�����ظ߶�
	//���� value [in]:�߶�ֵ������������
	//��غ�����width��height��setWidth
	void setHeight(int value);

	//����ͼ������ָ��
	//
	//���� data [in]��ͼ������ͷָ�롣ͼ�����ݿռ䲻���ڶ����ͷ�ʱ�ͷţ����ⲿ���й���
	//��غ�����bits
	void setData(unsigned char* data);

	//��ȡͼ������ָ��
	//����ֵ��ͼ������ָ�롣����0ʱ����ʾΪ��
	//��غ�����setData
	unsigned char* bits();

	//����ͼ���ļ�����ʽΪ8λBMP��ʽ
	//���� data [in]��ͼ������ͷָ��
	//����ֵ��trueΪ��ɣ�falseʧ��
    bool saveImage(const char* fileName);
	
	//ͼ������ƽ��У���������setCorrectData֮��ʹ��
	//����У������ͼ��ƴ��֮ǰʹ��
	//����ֵ��trueΪ��ɣ�falseʧ��
	//��غ�����setCorrectData
	bool correct();

	//�Աȶ�����
	//���� contrast [in]:�Աȶ�ƫ����
	//���� bright [in]:����ƫ����
	void contrast_and_bright(int contrast, int bright);

	//����У������
	//����ڰ�У��ԭʼ���ݺ󣬻��������յ�У�����ݡ�����ĺڰ�У��ԭʼ���ݿռ����ⲿ���й���
	//���� black [in]:��ɫУ������ָ��
	//���� white [in]:��ɫУ������ָ��
	//���� width [in]:���ݿ�ȡ�black��white������һ��
	//��غ�����correct
	void setCorrectData(unsigned char* black, unsigned char* white, int width);

	//ͼ��ƴ��,����ƴ�Ӻ��ͼ�����
	//���� offset [in]��ƴ�Ӳ���������ΪPixelOffset��������μ�PixelOffset˵��
	//���� count [in]��offset���ȣ�Ҳ��ʾͼ��ͨ��������Ĭ��ֵΪ6��6��ͨ����
	//����ֵ��ƴ�Ӻ��ͼ�����
	void montage(PixelOffset* offset, ImageProcess& newImage, int count = COUNTOF_CHANNEL);

	//ͼ��������ȡ����������ͼ�����
    //���� thre [in]:�Ҷ�ͼ��ֵ����ֵ��Ĭ��ֵΪ100
	//���� area [in]:����������ˣ�����С��area����Ľ�С����
	//���� backgroud_is_black [in]��trueΪ�ڵװ�ͼ����falseΪ�׵׺�ͼ����Ĭ��ֵΪtrue
	//���� optimize [in]������ƽ���Ż�������ȡֵ��ΧΪ[0, 1����0Ϊ���Ż���1Ϊ����Ż���Ĭ��ֵΪ0.01
	//����ֵ��������ȡ���ͼ�����
    void findContour(vector<vector<HTS_Point>>& contours, int thre = 100, int area = 400, bool background_is_black = true, int optimize = 0);

	//ͼ�����ţ��������ź��ͼ�����
	//���� scale_x [in]:�������ű���
	//���� scale_y [in]:�������ű���
	//����ֵ�����ź��ͼ�����
	void zoom(double scale_x, double scale_y, ImageProcess& newImage);

	//��ȡ����DPI
	long getBiXPelsPerMeter();

	//��ȡ����DPI
	long getBiYPelsPerMeter();

	//���ú���DPI
	void setBiXPelsPerMeter(long pelsPerMeter);

	//��������DPI
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
