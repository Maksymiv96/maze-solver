// cpp.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
//dont forget to insert folder with imgs to folder
const string ImageFolder = "../../../imgs/";

int main()
{
	Mat img = imread(ImageFolder + "difficult.jpg");
	Size new_size;
	if (img.rows > img.cols)
	{
		new_size =  Size(480, 640);
	}
	else
	{
		new_size = Size(640, 480);
	}
	
	resize(img, img,new_size);
	
	Mat blured_image;
	Mat opened_image;
	Mat gray_image;
	Mat thresh_image;
	GaussianBlur(img, blured_image, Size(7,7) , 0, 0);
	morphologyEx(blured_image, opened_image, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 2);
	cvtColor(opened_image, gray_image, CV_BGR2GRAY);
	threshold(gray_image, thresh_image, 125, 255, THRESH_BINARY);
	namedWindow("Result");
	imshow("Result", img);
	waitKey();

}