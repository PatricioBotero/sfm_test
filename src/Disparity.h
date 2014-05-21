/*
 * Disparity.h
 *
 *  Created on: 12.09.2013
 *      Author: tabuchte
 */

#ifndef DISPARITY_H_
#define DISPARITY_H_

class Disparity {
public:
	void computeDenseDisparityImageBM(cv::Mat left, cv::Mat right, cv::Mat* disparity);
	void computeDenseDisparityImageBM2(cv::Mat left, cv::Mat right, cv::Mat* disparity);
	void computeDenseDisparityImageSGBM_default(cv::Mat left, cv::Mat right, cv::Mat* disparity);
	void computeDenseDisparityImageSGBM(cv::Mat left, cv::Mat right, int windowSize, int numberOfDisparities, int preFilterCap, int minDisparity, int uniquenessRatio,
			int speckleWindowSize, int speckleRange, int disp12MaxDiff, bool fullDP, int p1, int p2, cv::Mat* disparity);
	Disparity() {};
	virtual ~Disparity() {};
};

#endif /* DISPARITY_H_ */
