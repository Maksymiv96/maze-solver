// cpp.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
//dont forget to insert folder with imgs to folder
const std::string ImageFolder = "./imgs/";

int main()
{
	auto img = cv::imread(ImageFolder + "sample1.jpg");

	
	cv::namedWindow("Result");
	cv::imshow("Result", img);
	cv::waitKey();

}