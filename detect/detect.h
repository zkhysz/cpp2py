#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_core341d.lib")
#pragma comment(lib, "opencv_imgcodecs341d.lib")
#pragma comment(lib, "opencv_highgui341d.lib")
#pragma comment(lib, "opencv_imgproc341d.lib")
#else
#pragma comment(lib, "opencv_core341.lib")
#pragma comment(lib, "opencv_imgcodecs341.lib")
#pragma comment(lib, "opencv_highgui341.lib")
#pragma comment(lib, "opencv_imgproc341.lib")
#endif

#define DLLEXPORT __declspec(dllexport)

extern "C"
{
	int g_value;
	DLLEXPORT short* __stdcall py2cpp(int height, int width, uchar* src_data);

	DLLEXPORT int lenght();

	void detect(const cv::Mat img, std::vector<cv::Rect>& rect);
}


