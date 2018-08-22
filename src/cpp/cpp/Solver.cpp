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
const string ImageFolder = "../../../imgs/paper/";
const int GREEN = 1, RED = 2;

Point color_points_detection(Mat *image, int color)
{
	Mat buf;
	image->copyTo(buf);
	cvtColor(buf, buf, COLOR_BGR2HSV);
	Mat mask;
	Scalar lower, upper;
	if (color == GREEN)
	{
		lower = Scalar(45, 100, 40);
		upper = Scalar(75, 255, 255);

	}
	else if (color == RED)
	{
		lower = Scalar(165, 100, 100);
		upper = Scalar(180, 255, 255);
	}
	inRange(buf, lower, upper, mask);
	morphologyEx(mask, mask, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 2);
	vector<vector<Point>> contours;
	findContours(mask, contours, RETR_TREE, CHAIN_APPROX_NONE);
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

Point* find_entry_and_exit(Mat image)
{
	Point* points = new Point[2];
	vector<vector<Point>> finded_countours_1;
	vector<Vec4i> hierarchy_1;
	findContours(image, finded_countours_1, hierarchy_1, RETR_TREE, CHAIN_APPROX_NONE);
	//drawContours(image, finded_countours, -1, Scalar(255, 0, 0));
	points[0] = fitEllipse(finded_countours_1[0]).center;
	points[1] = fitEllipse(finded_countours_1[1]).center;
	return points;
}

int main()
{
	Mat img = imread(ImageFolder + "dark.jpg");

	Mat blured_image;
	Mat opened_image;
	Mat gray_image;
	Mat thresh_image;

	GaussianBlur(img, blured_image, Size(3, 3), 5, 3);
	//bilateralFilter(img, blured_image, 1, 20, 5);
	morphologyEx(blured_image, opened_image, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)), Point(-1, -1), 2);

	cvtColor(opened_image, gray_image, CV_BGR2GRAY);
	//threshold(gray_image, thresh_image, 100, 255, THRESH_BINARY_INV);
	adaptiveThreshold(gray_image, thresh_image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 11, 7);


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


	//Mat thresh;
	//thresh_image.copyTo(thresh, mask);
	//thresh.copyTo(thresh_image);
	////bitwise_and(thresh_image, thresh_image, mask);
	//morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 2);
	//morphologyEx(thresh_image, thresh_image, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 1);





	//Border detecting 
	Mat BorderOnly;
	img.copyTo(BorderOnly, mask);
	cvtColor(BorderOnly, BorderOnly, COLOR_BGR2HSV);
	inRange(BorderOnly, Scalar(0, 0, 0), Scalar(180, 100, 100), BorderOnly);
	morphologyEx(BorderOnly, BorderOnly, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 1);
	morphologyEx(BorderOnly, BorderOnly, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 1);

	//cv::inRange(img_copy, Scalar(127, 127, 127), Scalar(255, 255, 255), BorderOnly);

	//PathFinder(&BorderOnly, color_points_detection(&blured_image, GREEN), color_points_detection(&blured_image, RED)).copyTo(BorderOnly);
	vector<Point> path = PathFinder(&BorderOnly, color_points_detection(&blured_image, GREEN), color_points_detection(&blured_image, RED));
	drawPathOnImage(&img, &path);

	namedWindow("Result");
	imshow("Result", img);
	waitKey();

}