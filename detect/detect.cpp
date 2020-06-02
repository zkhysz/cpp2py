#include "detect.h"

void detect(const cv::Mat img, std::vector<cv::Rect>& rect)
{
	cv::Mat dst;
	if (3 == img.channels()) { cv::cvtColor(img, dst, cv::COLOR_RGB2GRAY); }
	else { img.copyTo(dst); }
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::Rect tmp;
	if (CV_8U != dst.type()) { dst.convertTo(dst, CV_8U); }
	cv::findContours(dst, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	for (int index = 0; index >= 0; index = hierarchy[index][0])
	{
		tmp = cv::boundingRect(contours[index]);
		rect.push_back(tmp);
	}
}

short* py2cpp(int height, int width, uchar* src_data)
{
	cv::Mat src(height, width, CV_8UC3, (void*)src_data);
	std::vector<cv::Rect> list;
	detect(src, list);
	cv::Mat tres((int)list.size(), 4, CV_16SC1);
	g_value = (int)list.size();
	for (int i = 0; i < tres.rows; i++)
	{
		tres.at<short>(i, 0) = list[i].x;
		tres.at<short>(i, 1) = list[i].y;
		tres.at<short>(i, 2) = list[i].width;
		tres.at<short>(i, 3) = list[i].height;

		std::cout << "[" << list[i].x << ", " << list[i].y << ", " << list[i].width << ", " << list[i].height << "]" << std::endl;
	}	
	short *bb = (short *)(tres.data);
	std::cout << bb << std::endl;

	return bb;
}

int lenght()
{
	std::cout << g_value << std::endl;
	return g_value;
}