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
		Mat frame,gray,edges,bin;
		cap >> frame; // get a new frame from camera

		Mat imgThresholded;
		
		cvtColor(frame, imgThresholded, CV_BGR2GRAY);
		//threshold(gray, bin, 115, 255, 0);
		Canny(imgThresholded, edges, 100, 200, 3);		// Apply Canny edge detection on the gray image
		imshow("bin", edges);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < contours.size(); i++)
		{
			int area = contourArea(contours[i]);
			if (area > 500) {
				drawContours(frame, contours, i, Scalar(255, 200, 0), 2, 8, hierarchy, 0);
			}
		}

		imshow("edges", frame);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
