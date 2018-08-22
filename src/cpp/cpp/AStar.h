#pragma once
std::vector<cv::Point> PathFinder(cv::Mat *maze, cv::Point currentPossition, cv::Point destinationPossition);
//cv::Mat PathFinder(cv::Mat *maze, cv::Point currentPossition, cv::Point destinationPossition);
void drawPathOnImage(cv::Mat *image, std::vector<cv::Point>* path);