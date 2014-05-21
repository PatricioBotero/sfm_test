/*
 * Webcam.h
 *
 *  Created on: 11.09.2013
 *      Author: tabuchte
 */

#ifndef WEBCAM_H_
#define WEBCAM_H_

#include "opencv2/core/core.hpp"

class Webcam {
public:
	cv::vector<cv::Mat> readContinuousImages(int number, int skipFrames);
	std::string getOutputImageName(int number);
	Webcam() {};
	virtual ~Webcam() {};
};

#endif /* WEBCAM_H_ */
