#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace cv;
using namespace std;

Mat OurImage, camera, gray, edges, morph;



int main(int, char**)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		
		Mat imgHSV;
		Mat imgThresholded;

		Scalar hsv_l(110, 150, 150);
		Scalar hsv_h(130, 255, 255);
		cvtColor(frame, imgHSV, CV_BGR2HSV);
		inRange(imgHSV, hsv_l, hsv_h, imgThresholded);
		/*
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		*/

		imshow("edges", imgThresholded);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
