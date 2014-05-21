/*
 * Webcam.cpp
 *
 *  Created on: 11.09.2013
 *      Author: tabuchte
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "Webcam.h"

cv::vector<cv::Mat> readContinuousImages(int number, int skipFrames) {
	cv::vector<cv::Mat> imageVector;
	cv::VideoCapture cap(0);
	bool started = false;
	int counter = 0;
	for (;;) {
		cv::Mat frame;
		cap >> frame;
		if (!started) {
			cv::putText(frame, "Press any key to start!", cvPoint(30, 30),
					cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 250), 1,
					CV_AA);
			imshow("getImage()", frame);
			if (cv::waitKey(30) >= 0) {
				started = true;
			} else {
				continue;
			}
		}
		imshow("getImage()", frame);
		counter++;
		if (counter % skipFrames == 0) {
			imageVector.push_back(frame.clone());
			std::cout << counter / skipFrames << std::endl;
		}
		if (cv::waitKey(30) >= 0 || counter / skipFrames == number) {
			break;
		}
	}
	return imageVector;
}

std::string getOutputImageName(int number) {
	std::stringstream ss;
	ss << number;
	std::string s(ss.str());
	std::string text = "imgs/image_";
	text += s;
	text += ".jpg";
	return text;
}
