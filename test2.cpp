#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("2.jpg", 1);
	Mat imgHSV;

	if (!src.data)
	{
		return -1;
	}
	//resize(src, src, Size(src.cols / 5, src.rows / 5), 0, 0, 3);
	//namedWindow("src", WINDOW_AUTOSIZE);
	//imshow("src", src);

	//HSV范围
	int iLowH = 210 / 2;
	int iHighH = 220 / 2;

	int iLowS = 20 * 255 / 100;
	int iHighS = 40 * 255 / 100;

	int iLowV = 30 * 255 / 100;
	int iHighV = 50 * 255 / 100;

	cvtColor(src, imgHSV, COLOR_BGR2HSV);
	namedWindow("imgHSV", WINDOW_NORMAL);
	imshow("imgHSV", imgHSV);	
	//imwrite("hsv.jpg", imgHSV);

	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
	//开操作 (去除一些噪点)
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)  
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

	namedWindow("Thresholded Image", WINDOW_NORMAL);
	imshow("Thresholded Image", imgThresholded);

	waitKey(0);
	return 0;
}
