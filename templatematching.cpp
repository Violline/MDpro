#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace cv;
using namespace std;

Mat camera, gray, edges, morph;

Mat dataOpen() {

	string Destination = "C:\\Users\\Olka\\Documents\\Studia 3\\MD\\generatedd.jpg";
	Mat OurImage = imread(Destination, CV_LOAD_IMAGE_COLOR);
	if (!OurImage.data)
	{
		printf("No image!");
		getchar();
		//return -1;
	}

	return OurImage;
}

int match(int k) {
	vector<int> match_method = { CV_TM_SQDIFF, CV_TM_SQDIFF_NORMED, CV_TM_SQDIFF_NORMED, CV_TM_CCORR_NORMED, CV_TM_CCOEFF, CV_TM_CCOEFF_NORMED };
	return match_method.at(k);
}

int main(int, char**)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;


	Mat templ = dataOpen();

	
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame, result;
		cap >> frame; // get a new frame from camera

		int match_method = match(0);
		matchTemplate(frame, templ, result, match_method);
		normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal; double maxVal; Point minLoc; Point maxLoc;
		Point matchLoc;

		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

		if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}

		Scalar colour = Scalar(230, 0, 230);
		rectangle(frame, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), colour, 0.5, 8, 0);
		rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), colour, 0.5, 8, 0); //last param additional: shift – Number of fractional bits in the point coordinates.

		imshow("OurImage", frame);
		imshow("result", result);



		//imshow("edges", frame);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
