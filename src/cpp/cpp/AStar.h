#pragma once

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"

std::vector<cv::Point> PathFinder(cv::Mat *maze, cv::Point currentPossition, cv::Point destinationPossition);
//cv::Mat PathFinder(cv::Mat *maze, cv::Point currentPossition, cv::Point destinationPossition);
void drawPathOnImage(cv::Mat *image, std::vector<cv::Point>* path);