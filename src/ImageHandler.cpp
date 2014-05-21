/*
 * ImageHandler.cpp
 *
 *  Created on: 11.09.2013
 *      Author: tabuchte
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "ImageHandler.h"

std::vector<cv::Mat> ImageHandler::openImages(std::string path, std::string imageName, int rangeStart, int rangeEnd, std::string type) {
	std::vector<cv::Mat> images;
	for (int i=rangeStart; i<=rangeEnd;i++) {
		std::string imagePath = concatenateImageString(path, imageName, i, type);
		cv::Mat image = cv::imread(imagePath);
		images.push_back(image);
	}
	return images;
}

std::string ImageHandler::concatenateImageString(std::string path, std::string imageName, int number, std::string type) {
	std::string imageString = path;
	imageString += imageName;
	std::stringstream ss;
	ss << number;
	std::string s(ss.str());
	imageString += ".";
	imageString += type;
	return imageString;
}

void ImageHandler::checkImages(std::vector<cv::Mat> images) {
	for(std::vector<int>::size_type i = 0; i != images.size(); i++) {
		std::cout<< i << " -- OK" << std::endl;
	}
}
