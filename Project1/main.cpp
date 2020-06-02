#include <iostream>
#include <opencv2/opencv.hpp>
#include "../detect/detect.h"

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

int main()
{
	//cv::Mat img(500, 500, CV_8UC1, cv::Scalar(0));
	//cv::circle(img, cv::Point(100, 100), 50, cv::Scalar(255), -1, 8);
	//cv::circle(img, cv::Point(300, 300), 100, cv::Scalar(255), -1, 8);
	//cv::imshow("", img);
	//cv::waitKey(0);
	//cv::destroyAllWindows();
	//cv::imwrite("..//circle.png", img);

	cv::Mat img = cv::imread(R"(../circle.png)");
	std::vector<cv::Rect> rect;
	detect(img, rect);
	if (img.channels() != 3) { cv::cvtColor(img, img, cv::COLOR_GRAY2BGR); }
	for (int i = 0; i < rect.size(); i++)
	{
		cv::rectangle(img, rect[i], cv::Scalar(0, 0, 255), 1, 8, 0);
	}
	cv::imshow("", img);
	cv::waitKey(0);
	cv::destroyAllWindows();


	return 0;
}