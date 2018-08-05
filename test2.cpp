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
	resize(src, src, Size(src.cols / 5, src.rows / 5), 0, 0, 3);
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	//HSV��Χ
	int iLowH = 100 / 2;
	int iHighH = 120 / 2;

	int iLowS = 50 * 255 / 100;
	int iHighS = 70 * 255 / 100;

	int iLowV = 40 * 255 / 100;
	int iHighV = 50 * 255 / 100;

	cvtColor(src, imgHSV, COLOR_BGR2HSV);
	namedWindow("imgHSV", WINDOW_AUTOSIZE);
	imshow("imgHSV", imgHSV);	
	//imwrite("hsv.jpg", imgHSV);

	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
	//������ (ȥ��һЩ���)
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)  
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

	namedWindow("Thresholded Image", WINDOW_AUTOSIZE);
	imshow("Thresholded Image", imgThresholded);

	waitKey(0);
	return 0;
}
