/*
 * EpipolarGeometry.h
 *
 *  Created on: 11.09.2013
 *      Author: tabuchte
 */

#ifndef EPIPOLARGEOMETRY_H_
#define EPIPOLARGEOMETRY_H_

#include "opencv2/features2d/features2d.hpp"

class EpipolarGeometry {
public:
	void computeAndShowEpiLines(cv::Mat image1, cv::Mat image2);
	void drawFeatureMatching(cv::Mat img_1, cv::Mat img_2, std::vector<cv::DMatch>* good_matches, std::vector<cv::KeyPoint>* keypoints_1, std::vector<cv::KeyPoint>* keypoints_2);
	void getFeatureMatches(cv::Mat img_1, cv::Mat img_2, std::vector<cv::DMatch>* good_matches, std::vector<cv::KeyPoint>* keypoints_1, std::vector<cv::KeyPoint>* keypoints_2);
	EpipolarGeometry() {};
	virtual ~EpipolarGeometry() {};
};

#endif /* EPIPOLARGEOMETRY_H_ */
