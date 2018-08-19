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


Point* find_entry_and_exit(Mat image)
{
	//maybe better split it on 2 func, one color space for one dot. if in one color space there'll be two dots throw error 
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
	Mat img = imread(ImageFolder + "shaped.jpg");
	Size new_size;
	Mat blured_image;
	Mat opened_image;
	Mat gray_image;
	Mat thresh_image;
	Mat edges;
	Mat binary_mask_dots;

	//medianBlur(img, blured_image, 5);
	GaussianBlur(img, blured_image, Size(3, 3), 0, 0);
	//bilateralFilter(img, blured_image, 1, 20, 5);
	morphologyEx(blured_image, opened_image, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)), Point(-1, -1), 2);
	cvtColor(blured_image, blured_image, COLOR_BGR2HSV);



	Mat bgr[3];
	split(blured_image, bgr);
	cvtColor(blured_image, blured_image, COLOR_HSV2BGR);
	/*Mat hsv, mred, mgreen, m1, m2;
	cvtColor(img, hsv, COLOR_BGR2HSV);

	inRange(hsv, Scalar(0, 40, 50), Scalar(10, 255, 255), m1);
	inRange(hsv, Scalar(150, 70, 50), Scalar(120, 255, 255), m2);
	mred = m1 | m2;
	*/
	threshold(bgr[0], bgr[0], 0, 255, THRESH_BINARY);
	threshold(bgr[1], bgr[1], 160, 255, THRESH_BINARY);
	threshold(bgr[2], bgr[2], 0, 255, THRESH_BINARY);

	vector<Mat> channels;
	channels.push_back(bgr[0]);
	channels.push_back(bgr[1]);
	channels.push_back(bgr[2]);
	merge(channels, binary_mask_dots);
	cvtColor(binary_mask_dots, binary_mask_dots, COLOR_HSV2BGR);
	//morphologyEx(binary_mask_dots,binary_mask_dots, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 5);
	cvtColor(binary_mask_dots, binary_mask_dots, COLOR_BGR2GRAY);
	threshold(binary_mask_dots, binary_mask_dots, 250, 255, THRESH_BINARY_INV);

	cvtColor(opened_image, gray_image, CV_BGR2GRAY);
	threshold(gray_image, thresh_image, 100, 255, THRESH_BINARY_INV);
	Canny(thresh_image, edges, 0, 255);

	vector<vector<Point>> finded_countours;
	vector<Vec4i> hierarchy;
	findContours(thresh_image, finded_countours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	drawContours(img, finded_countours, -1, Scalar(255, 0, 0));
	vector<Point> for_convex;

	//filter contours which size less 10% from highest contour size
	int maxContourSize = finded_countours[0].size();

	for (int i = 0; i < finded_countours.size(); i++)
	{
		if (finded_countours[i].size() >(maxContourSize))
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
	drawContours(img, closed_maze, -1, Scalar(0, 0, 0), 4);
	drawContours(thresh_image, closed_maze, -1, Scalar(255, 0, 0), 4);
	Mat mask(img.size(), CV_8UC1);
	drawContours(mask, closed_maze, 0, Scalar(255), -1);
	Mat thresh;
	thresh_image.copyTo(thresh, mask);
	thresh.copyTo(thresh_image);
	//bitwise_and(thresh_image, thresh_image, mask);
	morphologyEx(thresh_image, thresh_image, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 1);
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
	Point* ex_en = new Point[2];
	ex_en = find_entry_and_exit(binary_mask_dots);
	drawMarker(binary_mask_dots, ex_en[0], Scalar(0, 0, 0));
	drawMarker(binary_mask_dots, ex_en[1], Scalar(0, 0, 0));


	Mat BorderOnly;
	cv::inRange(img_copy, Scalar(127, 127, 127), Scalar(255, 255, 255), BorderOnly);
	//drawMarker(BorderOnly, ex_en[0], Scalar(255, 255, 255));
	//drawMarker(BorderOnly, ex_en[1], Scalar(255, 255, 255));

	//cout << ex_en[1];
	//cin.get();
	//resize(BorderOnly, BorderOnly, Size(320,240));
	PathFinder(&BorderOnly, ex_en[0], ex_en[1]).copyTo(BorderOnly);// .copyTo(BorderOnly);

	namedWindow("Result");
	imshow("Result", img);
	namedWindow("Result1");
	imshow("Result1", BorderOnly);
	waitKey();

}