/*
 * EpipolarGeometry.cpp
 *
 *  Created on: 11.09.2013
 *      Author: tabuchte
 */

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "EpipolarGeometry.h"

void EpipolarGeometry::computeAndShowEpiLines(cv::Mat image1, cv::Mat image2) {

	std::vector<cv::KeyPoint> keypoints_1, keypoints_2;
	std::vector<cv::DMatch> good_matches;
	getFeatureMatches(image1, image2, &good_matches, &keypoints_1, &keypoints_2);
	// drawFeatureMatching(image1, image2, &good_matches, &keypoints_1, &keypoints_2);

	int vectorSize = good_matches.size();
	cv::vector<cv::Point2f> points1(vectorSize);
	cv::vector<cv::Point2f> points2(vectorSize);
	for( int i = 0; i < vectorSize; i++ ) {
	    points1[i] = keypoints_1[good_matches[i].queryIdx].pt;
	    points2[i] = keypoints_2[good_matches[i].trainIdx].pt;
	}

	cv::vector<uchar> status;
	cv::Mat F = cv::findFundamentalMat(points1, points2, status, CV_FM_RANSAC, 3, 0.99);

	cv::vector<cv::Point2f> selected_points1, selected_points2;
	for (uchar i=0;i<status.size();i++) {
		if(status[i]==1) {
			selected_points1.push_back(points1[i]);
			selected_points2.push_back(points2[i]);
			// draw points
			// cv::ellipse(image1, points1[i], )
		}
	}



	cv::RNG rng(12345);

	cv::vector<cv::Vec3f> lines1;
	cv::computeCorrespondEpilines(cv::Mat(selected_points1), 1, F, lines1);
	for (std::vector<cv::Vec3f>::const_iterator it= lines1.begin(); it!=lines1.end(); ++it) {
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::Point pt1(0,-(*it)[2]/(*it)[1]);
		cv::Point pt2(image2.cols,-((*it)[2]+(*it)[0]*image2.cols)/(*it)[1]);
		cv::line(image2,pt1, pt2, color);
	}

	cv::vector<cv::Vec3f> lines2;
	cv::computeCorrespondEpilines(cv::Mat(selected_points2), 1, F, lines2);
	for (std::vector<cv::Vec3f>::const_iterator it= lines2.begin(); it!=lines2.end(); ++it) {
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::Point pt1(0,-(*it)[2]/(*it)[1]);
		cv::Point pt2(image1.cols,-((*it)[2]+(*it)[0]*image1.cols)/(*it)[1]);
		cv::line(image1,pt1, pt2, color);
	}

	cv::namedWindow("Left Image Epilines (RANSAC)");
	cv::imshow("Left Image Epilines (RANSAC)",image2);
	cv::namedWindow("Right Image Epilines (RANSAC)");
	cv::imshow("Right Image Epilines (RANSAC)",image1);
	cv::waitKey(0);
}

void EpipolarGeometry::drawFeatureMatching(cv::Mat img_1, cv::Mat img_2, std::vector<cv::DMatch>* good_matches, std::vector<cv::KeyPoint>* keypoints_1, std::vector<cv::KeyPoint>* keypoints_2) {
	cv::Mat img_matches;
	cv::drawMatches(img_1, *keypoints_1, img_2, *keypoints_2, *good_matches,
			img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1), cv::vector<char>(),
			cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//-- Show detected matches
	// namedWindow("Good Matches", CV_WINDOW_KEEPRATIO);
	imshow("Good Matches", img_matches);

	for (int i = 0; i < (*good_matches).size(); i++) {
		printf("-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i,
				(*good_matches)[i].queryIdx, (*good_matches)[i].trainIdx);
	}

	cv::waitKey(0);
}

void EpipolarGeometry::getFeatureMatches(cv::Mat img_1, cv::Mat img_2, std::vector<cv::DMatch>* good_matches, std::vector<cv::KeyPoint>* keypoints_1, std::vector<cv::KeyPoint>* keypoints_2) {
	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;

	cv::SurfFeatureDetector detector(minHessian);

	detector.detect(img_1, *keypoints_1);
	detector.detect(img_2, *keypoints_2);

	//-- Step 2: Calculate descriptors (feature vectors)
	cv::SurfDescriptorExtractor extractor;

	cv::Mat descriptors_1, descriptors_2;

	extractor.compute(img_1, *keypoints_1, descriptors_1);
	extractor.compute(img_2, *keypoints_2, descriptors_2);

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	cv::FlannBasedMatcher matcher;
	std::vector<cv::DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	double max_dist = 0;
	double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_1.rows; i++) {
		double dist = matches[i].distance;
		if (dist < min_dist)
			min_dist = dist;
		if (dist > max_dist)
			max_dist = dist;
	}

	//-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
	//-- PS.- radiusMatch can also be used here.

	for (int i = 0; i < descriptors_1.rows; i++) {
		if (matches[i].distance <= 2 * min_dist) {
			(*good_matches).push_back(matches[i]);
		}
	}
}
