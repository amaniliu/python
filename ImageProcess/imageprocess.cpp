#include "ImageProcess.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <include/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define NULL 0
#define LUT_CHANNELS 318

ImageProcess::ImageProcess()
    : m_src_width(0)
    , m_src_height(0)
    , m_data(nullptr)
    , m_data2(nullptr)
    , m_correct_table(nullptr)
    , m_biXPelsPerMeter(5906)
    , m_biYPelsPerMeter(5906)
{

}

ImageProcess::ImageProcess(unsigned char* data, const int& width, const int& height)
    : m_src_width(width)
    , m_src_height(height)
    , m_data(data)
    , m_data2(nullptr)
    , m_correct_table(nullptr)
    , m_biXPelsPerMeter(5906)
    , m_biYPelsPerMeter(5906)
{
}

ImageProcess::ImageProcess(const int& width, const int& height)
    : m_src_width(width)
    , m_src_height(height)
    , m_data(nullptr)
    , m_correct_table(nullptr)
    , m_biXPelsPerMeter(5906)
    , m_biYPelsPerMeter(5906)
	, m_data2()
{
    m_data2 = new unsigned char[static_cast<unsigned int>((width + 3) / 4 * 4 * height)];
}

ImageProcess::~ImageProcess()
{
    if (m_correct_table != nullptr)
    {
        delete[] m_correct_table;
	}

    if (m_data2 != nullptr)
    {
        delete[] m_data2;
    }
}

int ImageProcess::width()
{
	return m_src_width;
}

int ImageProcess::height()
{
	return m_src_height;
}

void ImageProcess::setWidth(int value)
{
	m_src_width = value;
}

void ImageProcess::setHeight(int value)
{
	m_src_height = value;
}

void ImageProcess::setData(unsigned char* data)
{
	m_data = data;
}

unsigned char* ImageProcess::bits()
{
    if (m_data2 != nullptr)
    {
        return m_data2;
    }
    else
    {
        return m_data;
    }
}

bool ImageProcess::correct()
{
    if (m_correct_table == nullptr)
	{
		return false;
    }

    int cols = PIX_CHANNEL * COUNTOF_CHANNEL / LUT_CHANNELS;
    Mat src(m_src_height, cols, CV_8UC(LUT_CHANNELS), bits());
    Mat table(cols, 256, CV_8UC(LUT_CHANNELS), m_correct_table);

    for (int i = 0; i < cols; ++i)
    {
        Mat temp_src = src(Rect(i, 0, 1, m_src_height));
        Mat temp_table = table(Rect(0, i, 256, 1));
        LUT(temp_src, temp_table, temp_src);
    }
	return true;
}

void ImageProcess::contrast_and_bright(int contrast, int bright)
{
	static unsigned char table_data[256];
	for (int i = 0; i < 128; i++)
	{
		table_data[i] = max(0, min(max(min(127, i - contrast), 0) + bright, 255));
	}

	for (int i = 128; i < 256; i++)
	{
		table_data[i] = max(0, min(max(min(255, i + contrast), 128) + bright, 255));
	}

	Mat src(m_src_height, m_src_width, CV_8UC1, bits());
	Mat table(1, 256, CV_8UC1, table_data);
	LUT(src, table, src);
}

void ImageProcess::setSize(int width, int height)
{
	m_src_width = width;
	m_src_height = height;

	if (m_data == nullptr)
	{
		if (m_data2 != nullptr)
		{
			delete[] m_data2;
		}

		m_data2 = new unsigned char[static_cast<unsigned int>((width + 3) / 4 * 4 * height)];
	}
}

bool ImageProcess::saveImage(const char* filename)
{
    Mat img(m_src_height, m_src_width, CV_8UC1, bits());

    imwrite(filename, img);
	return true;
}

void ImageProcess::montage(PixelOffset* offset, ImageProcess& newImage, int count)
{
	int newWidth = m_src_width;
	for (int i = 0; i < count; i++)
	{
        newWidth = newWidth - offset[i].m_left - offset[i].m_right;
	}
	int lineBits = (newWidth + 3) / 4 * 4;

	int newHeight = m_src_height;
    int max = offset[0].m_top;
	for (int i = 1; i < count; i++)
	{
        if (offset[i].m_top > max)
		{
            max = offset[i].m_top;
		}
	}
	newHeight -= (max * 2);
	newImage.setSize(newWidth, newHeight);
	if (newHeight < 0)
	{
		return;
	}

    Mat src_(m_src_height, m_src_width, CV_8UC1, bits());
    Mat dst_(newHeight, lineBits, CV_8UC1, newImage.bits());

    int offset_x = 0;
    for (int i = 0; i < count; i++)
    {
        int left = PIX_CHANNEL * i + offset[i].m_left;
        int top = offset[i].m_top;
        int width = PIX_CHANNEL - offset[i].m_left - offset[i].m_right;
        Mat temp_src = src_(Rect(left, top, width, newHeight));
        Mat temp_dst = dst_(Rect(offset_x, 0, width, newHeight));

        temp_src.copyTo(temp_dst);
        offset_x += width;
    }

    newImage.setWidth(lineBits);
	newImage.setHeight(newHeight);
	newImage.setBiXPelsPerMeter(m_biXPelsPerMeter);
	newImage.setBiXPelsPerMeter(m_biYPelsPerMeter);
}

void findContours(const Mat& src, vector<vector<Point>>& contours, vector<Vec4i>& hierarchy,
    int retr = RETR_LIST, int method = CHAIN_APPROX_SIMPLE, Point offset = Point(0, 0))
{
    CvMat c_image = src;
    MemStorage storage(cvCreateMemStorage());
    CvSeq* _ccontours = nullptr;
    cvFindContours(&c_image, storage, &_ccontours, sizeof(CvContour), retr, method, CvPoint(offset));

    if (!_ccontours)
    {
        contours.clear();
        return;
    }
    Seq<CvSeq*> all_contours(cvTreeToNodeSeq(_ccontours, sizeof(CvSeq), storage));
    size_t total = all_contours.size();
    contours.resize(total);

    SeqIterator<CvSeq*> it = all_contours.begin();
    for (size_t i = 0; i < total; i++, ++it)
    {
        CvSeq* c = *it;
        ((CvContour*)c)->color = static_cast<int>(i);
        size_t count = static_cast<size_t>(c->total);
        int* data = new int[count * 2];
        cvCvtSeqToArray(c, data);
        for (size_t j = 0; j < count; j++)
        {
            contours[i].push_back(Point(data[j * 2], data[j * 2 + 1]));
        }
        delete[] data;
    }

    hierarchy.resize(total);
    it = all_contours.begin();
    for (size_t i = 0; i < total; i++, ++it)
    {
        CvSeq* c = *it;
        int h_next = c->h_next ? ((CvContour*)c->h_next)->color : -1;
        int h_prev = c->h_prev ? ((CvContour*)c->h_prev)->color : -1;
        int v_next = c->v_next ? ((CvContour*)c->v_next)->color : -1;
        int v_prev = c->v_prev ? ((CvContour*)c->v_prev)->color : -1;
        hierarchy[i] = Vec4i(h_next, h_prev, v_next, v_prev);
    }

    cvClearMemStorage(storage);
}

void ImageProcess::findContour(vector<vector<HTS_Point>>& contours, int thre, int area, bool background_is_black, int optimize)
{
    Mat src(m_src_height, m_src_width, CV_8UC1, bits());
    Mat dst;
    threshold(src, dst, thre, 255, background_is_black ? THRESH_BINARY : THRESH_BINARY_INV);

    Mat element = getStructuringElement(MORPH_RECT,Size(10,10));
    morphologyEx(dst, dst, MORPH_OPEN, element);

    vector<vector<Point>> contours_temp;
    vector<Vec4i> hierarchy;
    findContours(dst, contours_temp, hierarchy, CV_RETR_EXTERNAL);

    for (size_t i = 0, length = contours_temp.size(); i < length; ++i)
    {
        if (contourArea(contours_temp[i]) < area)
        {
            continue;
        }
		if (optimize > 0)
		{
			approxPolyDP(contours_temp[i], contours_temp[i], optimize, true);
		}
        vector<HTS_Point> hts_points;
        for (size_t j = 0, total = contours_temp[i].size(); j < total; ++j)
        {
            hts_points.push_back(HTS_Point{contours_temp[i][j].x, contours_temp[i][j].y});
        }
        contours.push_back(hts_points);
    }
}

void ImageProcess::setCorrectData(unsigned char* black, unsigned char* white, int width)
{
    if (m_correct_table != nullptr)
    {
        delete[] m_correct_table;
	}

	m_correct_table = new unsigned char[static_cast<unsigned int>(width * 256)];

	const int rows = PIX_CHANNEL * COUNTOF_CHANNEL / LUT_CHANNELS;
	const int cols = 256;

	Mat lut(rows, cols, CV_8UC(LUT_CHANNELS), m_correct_table);
	for (int i = 0; i < rows; i++)
	{
		Mat lut_row = lut(cv::Rect(0, i, cols, 1));
		unsigned char* ptr_buffer = lut_row.data;
		unsigned char* ptr_black = black + i * LUT_CHANNELS;
		unsigned char* ptr_white = white + i * LUT_CHANNELS;
		for (int j = 0; j < cols; j++)
		{
			for (size_t k = 0; k < LUT_CHANNELS; k++)
			{
				//除黑边
				if (ptr_black[k] == 0 && ptr_white[k] == 0)
				{
					ptr_buffer[j * LUT_CHANNELS + k] = 255;
					continue;
				}

				//除白边
				if (ptr_black[k] == 255 && ptr_white[k] == 255)
				{
					ptr_buffer[j * LUT_CHANNELS + k] = 0;
					continue;
				}

				if (ptr_black[k] >= ptr_white[k])
				{
					ptr_buffer[j * LUT_CHANNELS + k] = 0;
					continue;
				}

				if (j <= ptr_black[k])
				{
					ptr_buffer[j * LUT_CHANNELS + k] = 0;
				}
				else if (j >= ptr_white[k])
				{
					ptr_buffer[j * LUT_CHANNELS + k] = 255;
				}
				else
				{
					ptr_buffer[j * LUT_CHANNELS + k] = 255 * (j - ptr_black[k]) / (ptr_white[k] - ptr_black[k]);
				}
			}
		}
	}
}

void ImageProcess::zoom(double scale_x, double scale_y, ImageProcess& newImage)
{
    Mat src(m_src_height, m_src_width, CV_8UC1, bits());
    int width = (static_cast<int>(m_src_width * scale_x) + 3) / 4 * 4;
    int height = static_cast<int>(m_src_height * scale_y);
    Size dSize(width, height);

    newImage.setSize(width, height);
    Mat dst(dSize, CV_8UC1, newImage.bits());
    resize(src, dst, dSize);
    newImage.setWidth(width);
    newImage.setHeight(height);
    newImage.setBiXPelsPerMeter(static_cast<long>(m_biXPelsPerMeter * scale_x));
    newImage.setBiYPelsPerMeter(static_cast<long>(m_biYPelsPerMeter * scale_y));
}

//获取横向DPI
long ImageProcess::getBiXPelsPerMeter()
{
	return m_biXPelsPerMeter;
}

//获取纵向DPI
long ImageProcess::getBiYPelsPerMeter()
{
	return m_biYPelsPerMeter;
}

//设置横向DPI
void ImageProcess::setBiXPelsPerMeter(long pelsPerMeter)
{
	m_biXPelsPerMeter = pelsPerMeter;
}

//设置纵向DPI
void ImageProcess::setBiYPelsPerMeter(long pelsPerMeter)
{
	m_biYPelsPerMeter = pelsPerMeter;
}
