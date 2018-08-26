// cpp.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>
#include <AStar.h>

using namespace cv;
using namespace std;

//dont forget to insert folder with imgs to folder
const string ImageFolder = "../../../imgs/web/";
const int GREEN = 1, RED = 2;

Point color_points_detection(Mat *image, int color)
{
	Mat buf;
	image->copyTo(buf);
	cvtColor(buf, buf, COLOR_BGR2HSV);
	Mat maskHSV;
	Scalar lower, upper;
	if (color == GREEN)
	{
		lower = Scalar(45, 50, 40);
		upper = Scalar(80, 255, 255);
		inRange(buf, lower, upper, maskHSV);

	}
	else if (color == RED)
	{
		lower = Scalar(0, 100, 80);
		upper = Scalar(15, 255, 255);
		inRange(buf, lower, upper, maskHSV);
		lower = Scalar(165, 100, 80);
		upper = Scalar(180, 255, 255);
		Mat maskHSV2;
		inRange(buf, lower, upper, maskHSV2);
		bitwise_or(maskHSV, maskHSV2, maskHSV);

	}
	
	//morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 2);
	//morphologyEx(mask, mask, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 2);

	morphologyEx(maskHSV, maskHSV, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 2);
	morphologyEx(maskHSV, maskHSV, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 1);
	
	vector<vector<Point>> contours;
	findContours(maskHSV, contours, RETR_TREE, CHAIN_APPROX_NONE);
	if (contours.size() > 1)
	{
		throw ("Too many points detected");
	}
	else if (contours.size() == 0)
	{
		throw ("Cant detect any point");
	}
	else return fitEllipse(contours[0]).center;
}

void borderDetection(Mat *image, Mat *threshedImage, Mat *outImage)
{
	//func detect color dots and delete it from threshedImage, because adaptive threshold work pretty good and i think better work with it
	Mat mask;
	Scalar lower, upper;
	Mat buf;
	image->copyTo(buf);
	cvtColor(buf, buf, COLOR_BGR2HSV);
	Mat mask2;
	lower = Scalar(0, 100, 80);
	upper = Scalar(15, 255, 255);
	inRange(buf, lower, upper, mask);
	lower = Scalar(165, 100, 80);
	upper = Scalar(180, 255, 255);
	inRange(buf, lower, upper, mask2);
	bitwise_or(mask, mask2, mask);

	lower = Scalar(45, 50, 40);
	upper = Scalar(80, 255, 255);
	inRange(buf, lower, upper, mask2);
	bitwise_or(mask, mask2, mask);
	
	mask = 255 - mask;

	threshedImage->copyTo(*outImage, mask);
	morphologyEx(*outImage, *outImage, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 1);
	morphologyEx(*outImage, *outImage, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 3);
}

void paperExtractor(Mat *image, Mat *outImage)
{
	Mat maskRGB,maskHSV;
	Scalar lower, upper;
	Mat buf;
	image->copyTo(buf);

	lower = Scalar(110, 110, 100);
	upper = Scalar(255, 255, 255);
	inRange(buf, lower, upper, maskRGB);

	lower = Scalar(0, 0, 155);
	upper = Scalar(180, 155, 255);
	cvtColor(buf, buf, COLOR_BGR2HSV);
	inRange(buf, lower, upper, maskHSV);
	Mat mask;
	bitwise_or(maskHSV, maskRGB,mask);

	morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 1);
	morphologyEx(mask, mask, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3,3)), Point(-1, -1), 3);

	

	vector<vector<Point>> findedCountours;
	findContours(mask, findedCountours, RETR_TREE, CHAIN_APPROX_NONE);

	int maxContourSize = findedCountours[0].size();
	int index = 0;
	mask = (image->size(), CV_8UC1);
	for (int i = 0; i < findedCountours.size(); i++)
	{
		//if (findedCountours[i].size() > (maxContourSize))
		{
			drawContours(mask, findedCountours, i, Scalar(255), -1);
			//maxContourSize = findedCountours[i].size();
			//index = i;
		}
	}

	//Mat result(img.size(), CV_8UC1);
	
	//drawContours(mask, findedCountours, index, Scalar(255), -1);
	Mat result(image->size(), CV_8UC3);
	result = Scalar(255, 255, 255);
	result.copyTo(*outImage);
	image->copyTo(*outImage, mask);


	//cin.get();

}

int main()
{
	Mat img = imread(ImageFolder + "image (3).png");

	Mat blured_image;
	Mat opened_image;
	Mat gray_image;
	Mat thresh_image;
	Mat paperOnly;

	GaussianBlur(img, blured_image, Size(3, 3), 5, 3);
	//bilateralFilter(img, blured_image, 1, 50, 50);
	morphologyEx(blured_image, opened_image, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)), Point(-1, -1), 2);

	paperExtractor(&blured_image,&paperOnly);

	cvtColor(paperOnly, gray_image, CV_BGR2GRAY);
	//threshold(gray_image, thresh_image, 100, 255, THRESH_BINARY_INV);
	adaptiveThreshold(gray_image, thresh_image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 11, 7);
	morphologyEx(thresh_image, thresh_image, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 3);
	//morphologyEx(thresh_image, thresh_image, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 3);




	////Creating mask
	vector<vector<Point>> finded_countours;
	vector<Vec4i> hierarchy;
	findContours(thresh_image, finded_countours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	//drawContours(img, finded_countours, -1, Scalar(255, 0, 0));
	vector<Point> for_convex;

	//filter contours which size less 10% from highest contour size
	int maxContourSize = finded_countours[0].size();

	for (int i = 0; i < finded_countours.size(); i++)
	{
		if (finded_countours[i].size() > (maxContourSize))
			maxContourSize = finded_countours[i].size();
	}
	cout << maxContourSize << endl;
	maxContourSize /= 10;

	for (int i = 0; i < finded_countours.size(); ++i)
	{
		if (finded_countours[i].size() > maxContourSize)
		{
			for (int j = 0; j < finded_countours[i].size(); ++j)
				for_convex.push_back(finded_countours[i][j]);
		}
	}
	vector<Point> hull;
	convexHull(for_convex, hull);
	vector<vector<Point>> closed_maze;
	closed_maze.push_back(hull);
	//drawContours(img, closed_maze, -1, Scalar(0, 0, 0), 4);
	drawContours(thresh_image, closed_maze, -1, Scalar(255, 0, 0), 4);
	Mat mask(img.size(), CV_8UC1);
	drawContours(mask, closed_maze, 0, Scalar(255), -1);
	morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 2);
	////

	//Border detecting 
	Mat BorderOnly;
	borderDetection(&paperOnly, &thresh_image, &BorderOnly);
	try
	{
		vector<Point> path = PathFinder(&BorderOnly, color_points_detection(&paperOnly, GREEN), color_points_detection(&paperOnly, RED));
		drawPathOnImage(&img, &path);
	}
	catch (...) {};

	namedWindow("Result");
	imshow("Result", img);
	waitKey();

}