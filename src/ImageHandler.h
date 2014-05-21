/*
 * ImageHandler.h
 *
 *  Created on: 11.09.2013
 *      Author: tabuchte
 */

#ifndef IMAGEHANDLER_H_
#define IMAGEHANDLER_H_

#include "opencv2/core/core.hpp"

class ImageHandler {
public:
	std::vector<cv::Mat> openImages(std::string path, std::string imageName, int rangeStart, int rangeEnd, std::string type);
	void checkImages(std::vector<cv::Mat> images);
	ImageHandler() {};
	virtual ~ImageHandler() {};
private:
	std::string concatenateImageString(std::string path, std::string imageName, int number, std::string type);

};

#endif /* IMAGEHANDLER_H_ */
