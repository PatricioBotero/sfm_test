//============================================================================
// Name        : SfM.cpp
// Author      : Patrick Buchter
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ImageHandler.h"
#include "EpipolarGeometry.h"
#include "Disparity.h"

std::vector<cv::Mat> images;

std::string getImagePathString(std::string path, std::string name, int number, std::string ending);

int main() {
	// ImageHandler imageHandler;
	// images = imageHandler.openImages("c:/Users/tabuchte/Documents/3dRekonstruktion/illinois.edu/hw3/prob4/images/", "hotel.seq", 0, 50, "png");

//	cv::Mat image1_raw = cv::imread("c:/OpenCV/stereo_testimages/P1180319.JPG");
//	cv::Mat image2_raw = cv::imread("c:/OpenCV/stereo_testimages/P1180326.JPG");
//	cv::Mat image1, image2;
//	cv::resize(image1_raw, image1, cv::Size(0, 0), 0.4, 0.4, cv::INTER_CUBIC);
//	cv::resize(image2_raw, image2, cv::Size(0, 0), 0.4, 0.4, cv::INTER_CUBIC);
//	EpipolarGeometry epipolarGeometry;
//	epipolarGeometry.computeAndShowEpiLines(image1, image2);

	Disparity disparity;
	cv::Mat map1, map2;

	cv::Mat left = cv::imread("c:/OpenCV/stereo_testimages/tsukuba_l.png", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat right = cv::imread("c:/OpenCV/stereo_testimages/tsukuba_r.png", CV_LOAD_IMAGE_GRAYSCALE);

	//disparity.computeDenseDisparityImageBM(left, right, &map1);
	disparity.computeDenseDisparityImageSGBM_default(left, right, &map1);
	disparity.computeDenseDisparityImageBM2(left, right, &map2);
	//disparity.computeDenseDisparityImageSGBM(left, right, 9, 16*3, 4, 0, 1, 150, 32, 10, true, 600, 2400, &map1);
	//disparity.computeDenseDisparityImageSGBM(left, right, 9, 16*12, 4, 0, 1, 150, 32, 10, false, 600, 2400, &map2);
	cv::imshow("left", left);
	cv::imshow("right", right);
	cv::imshow("disparity1", map1);
	cv::imshow("disparity2", map2);
	cv::waitKey( 0);



//	for (uchar i=1;i<300;i++) {
//		std::string path_left = getImagePathString("c:/OpenCV/Left/", "Left", i, "bmp");
//		cv::Mat left = cv::imread(path_left, CV_LOAD_IMAGE_GRAYSCALE);
//		std::string path_right = getImagePathString("c:/OpenCV/Right/", "Right", i, "bmp");
//		cv::Mat right = cv::imread(path_right, CV_LOAD_IMAGE_GRAYSCALE);
//
//		map1.empty();
//		map2.empty();
//		disparity.computeDenseDisparityImageSGBM(left, right, 5, 192, 4, -64, 1, 150, 2, 10, true, 600, 2400, &map1);
//		disparity.computeDenseDisparityImageSGBM(left, right, 9, 192, 4, -64, 1, 150, 32, 10, true, 600, 2400, &map2);
//		cv::imshow("left", left);
//		cv::imshow("right", right);
//		cv::imshow("disparity1", map1);
//		cv::imshow("disparity2", map2);
//		cv::waitKey( 0);
//	}


//
//
//
//
//	cv::imshow("left", left);
//	cv::imshow("right", right);
//	cv::imshow("disparity2", map2);
//	cv::waitKey(0);
}

std::string getImagePathString(std::string path, std::string name,
		int number, std::string ending) {
	std::string imagePath = path;
	imagePath += "/";
	imagePath += name;
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << number;
	std::string s(ss.str());
	imagePath += s;
	imagePath += ".";
	imagePath += ending;
	return imagePath;
}
