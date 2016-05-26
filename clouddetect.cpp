#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace cv;
using namespace std;

Mat OurImage, camera, gray, edges, morph;




int main()
{
	//string Destination = "C:\\Users\\Olka\\Documents\\STUDIA 3\\MD\\template2.jpg";
	//OurImage = imread(Destination, CV_LOAD_IMAGE_COLOR);
	string Dest = "C:\\Users\\Olka\\Documents\\STUDIA 3\\MD\\example2.jpg";
	OurImage = imread(Dest, CV_LOAD_IMAGE_COLOR);

	if (!OurImage.data)
	{
		printf("No image!");
		getchar();
		return -1;
	}

	Mat imgHSV;
	Mat imgThresholded;

	Scalar hsv_l(110, 150, 150);
	Scalar hsv_h(130, 255, 255);
	cvtColor(OurImage, imgHSV, CV_BGR2HSV);
	inRange(imgHSV, hsv_l, hsv_h, imgThresholded);

	imshow("Thresholded Image", imgThresholded); //show the thresholded image
	imshow("Original", OurImage); //show the original image
							  //imshow("WINDOW", morph);
	imshow("Thresholded Image", imgThresholded); //show the thresholded image
	imshow("Original", imgHSV); //show the original image
	waitKey(0);
}
