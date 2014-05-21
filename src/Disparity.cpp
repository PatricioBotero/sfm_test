/*
 * Disparity.cpp
 *
 *  Created on: 12.09.2013
 *      Author: tabuchte
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "Disparity.h"

void Disparity::computeDenseDisparityImageBM(cv::Mat left, cv::Mat right, cv::Mat* disparity) {

	cv::StereoBM sbm;
	sbm.state->SADWindowSize = 9;
	sbm.state->numberOfDisparities = 112;
	sbm.state->preFilterSize = 5;
	sbm.state->preFilterCap = 61;
	sbm.state->minDisparity = -39;
	sbm.state->textureThreshold = 507;
	sbm.state->uniquenessRatio = 0;
	sbm.state->speckleWindowSize = 0;
	sbm.state->speckleRange = 8;
	sbm.state->disp12MaxDiff = 1;
	sbm(left, right, *disparity);
	cv::normalize(*disparity, *disparity, 0, 255, CV_MINMAX, CV_8U);
}

void Disparity::computeDenseDisparityImageSGBM_default(cv::Mat left,
		cv::Mat right, cv::Mat* disparity) {
	cv::StereoSGBM sgbm;
	sgbm.preFilterCap = 63;
	sgbm.SADWindowSize = 3;
	sgbm.P1 = sgbm.SADWindowSize*sgbm.SADWindowSize*4;
	sgbm.P2 = sgbm.SADWindowSize*sgbm.SADWindowSize*32;
	sgbm.minDisparity = 0;
	sgbm.numberOfDisparities = 128;
	sgbm.uniquenessRatio = 10;
	sgbm.speckleWindowSize = 100;
	sgbm.speckleRange = 32;
	sgbm.disp12MaxDiff = 1;
	sgbm.fullDP = true;
	sgbm(left, right, *disparity);
	cv::normalize(*disparity, *disparity, 0, 255, CV_MINMAX, CV_8U);
}

void Disparity::computeDenseDisparityImageSGBM(cv::Mat left, cv::Mat right, int windowSize, int numberOfDisparities, int preFilterCap, int minDisparity, int uniquenessRatio,
		int speckleWindowSize, int speckleRange, int disp12MaxDiff, bool fullDP, int p1, int p2, cv::Mat* disparity) {
	// source: http://jayrambhia.com/blog/disparity-maps/
	cv::StereoSGBM sgbm;
	sgbm.SADWindowSize = windowSize; // 5
	sgbm.numberOfDisparities = numberOfDisparities; // 192;
	sgbm.preFilterCap = preFilterCap; //4;
	sgbm.minDisparity = minDisparity; //-64;
	sgbm.uniquenessRatio = uniquenessRatio; // 1;
	sgbm.speckleWindowSize = speckleWindowSize; //150;
	sgbm.speckleRange = speckleRange; //32;	// 2
	sgbm.disp12MaxDiff = disp12MaxDiff; //10;
	sgbm.fullDP = fullDP; //true;
	sgbm.P1 = p1; //600;
	sgbm.P2 = p2; //2400;
	sgbm(left, right, *disparity);
	cv::normalize(*disparity, *disparity, 0, 255, CV_MINMAX, CV_8U);
}

void Disparity::computeDenseDisparityImageBM2(cv::Mat left, cv::Mat right, cv::Mat* disparity) {
	cv::StereoBM sbm;
	//sbm.state->SADWindowSize = 21;
	//sbm.state->numberOfDisparities = 112;
	sbm(left, right, *disparity);
	cv::normalize(*disparity, *disparity, 0, 255, CV_MINMAX, CV_8U);
}
