#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;

	cap.open("DJI_0002.mp4");
	if (!cap.isOpened())
	{
		cout << "ERROR: Cannot open file." << endl;
		return -1;
	}

	Mat frame;
	char ret;

	while (true)
	{
		cap >> frame;
		if (frame.empty())
			break;

		resize(frame, frame, Size(), 0.5, 0.5);

		/* Histogram Equalization */

		Mat imageRGB[3];
		split(frame, imageRGB);
		for (int i = 0; i < 3; i++)
		{
			equalizeHist(imageRGB[i], imageRGB[i]);       // lighter
		}
		merge(imageRGB, 3, frame);

		/* Gamma Transform using Pointer */

		/*Mat imageGamma(frame.size(), CV_32FC3);
		int nrow = frame.rows;
		int ncol = frame.cols*frame.channels();
		for (int i = 0; i < nrow; i++)
		{
			uchar* inData = frame.ptr<uchar>(i);
			float* outData = imageGamma.ptr<float>(i);
			for (int j = 0; j < ncol; j++)
			{
				outData[j] = inData[j]*inData[j];        // gamma = 2, darker
			}
		}
		normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
		convertScaleAbs(imageGamma, frame);*/

		imshow("image_augmentation", frame);

		if ((ret = (char)waitKey(20)) > 0)
			break;
	}

	return 0;
}
