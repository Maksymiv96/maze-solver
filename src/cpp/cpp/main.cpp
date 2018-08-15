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
	Mat img = imread(ImageFolder + "smoothed.jpg");
	Size new_size;
	Mat blured_image;
	Mat opened_image;
	Mat gray_image;
	Mat thresh_image;
	Mat edges;
	Mat binary_mask_dots;
	if (img.rows > img.cols)
	{
		new_size =  Size(480, 640);
	}
	else
	{
		new_size = Size(640, 480);
	}
	
	resize(img, img,new_size);
	
	

	GaussianBlur(img, blured_image, Size(7,7) , 0, 0);
	morphologyEx(blured_image, opened_image, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 2);
	Mat bgr[3];
	split(blured_image, bgr);

	threshold(bgr[0], bgr[0], 0, 255, THRESH_BINARY);
	threshold(bgr[1], bgr[1], 40, 255, THRESH_BINARY);
	threshold(bgr[2], bgr[2], 40, 255, THRESH_BINARY);
	vector<Mat> channels;
	channels.push_back(bgr[0]);
	channels.push_back(bgr[1]);
	channels.push_back(bgr[2]);
	merge(channels,binary_mask_dots);
	morphologyEx(binary_mask_dots,binary_mask_dots, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 5);
	cvtColor(binary_mask_dots, binary_mask_dots, COLOR_BGR2GRAY);
	threshold(binary_mask_dots, binary_mask_dots, 250, 255, THRESH_BINARY_INV);
	
	cvtColor(opened_image, gray_image, CV_BGR2GRAY);
	threshold(gray_image, thresh_image, 120, 255, THRESH_BINARY_INV);
	Canny(thresh_image, edges, 0, 255);

	vector<vector<Point>> finded_countours;
	vector<Vec4i> hierarchy;
	findContours(thresh_image,finded_countours,hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	drawContours(img, finded_countours, -1, Scalar(255, 0, 0));
	vector<Point> for_convex;
	for (int i = 0; i < finded_countours.size(); ++i)
	{
		for(int j=0;j<finded_countours[i].size();++j)
		for_convex.push_back(finded_countours[i][j]);
	}
	vector<Point> hull;
	convexHull(for_convex, hull);
	vector<vector<Point>> closed_maze;
	closed_maze.push_back(hull);
	drawContours(img, closed_maze, -1, Scalar(0, 0, 0),4);
	drawContours(thresh_image, closed_maze, -1, Scalar(255, 0, 0), 4);
	morphologyEx(thresh_image, thresh_image , MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 1);
	Mat dots;
	
	img.copyTo(dots, binary_mask_dots);
	
	
	Mat img_copy;
	thresh_image.copyTo(img_copy);
	
	cvtColor(img_copy, img_copy, COLOR_GRAY2BGR);
	
	dots.copyTo(img_copy, binary_mask_dots);

	img.copyTo(img_copy, binary_mask_dots);
	morphologyEx(img_copy, img_copy, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 2);
	drawContours(img_copy, closed_maze, -1, Scalar(255, 255, 255), 8);
	
	Mat bgr_2[3];
	split(img_copy, bgr_2);

	threshold(bgr_2[0], bgr_2[0], 200, 255, THRESH_BINARY);
	threshold(bgr_2[1], bgr_2[1], 40, 255, THRESH_BINARY);
	threshold(bgr_2[2], bgr_2[2], 40, 255, THRESH_BINARY);
	vector<Mat> channels_2;
	channels_2.push_back(bgr_2[0]);
	channels_2.push_back(bgr_2[1]);
	channels_2.push_back(bgr_2[2]);
	merge(channels_2, img_copy);

	namedWindow("Result");
	imshow("Result", img);
	namedWindow("Result1");
	imshow("Result1", thresh_image);
	waitKey();

}