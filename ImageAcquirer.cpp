#include "StdAfx.h"
#include "ImageAcquirer.h"

#include <opencv2\highgui\highgui.hpp>
#include <string>
#include <iostream>

ImageAcquirer::ImageAcquirer(void)
{
}


ImageAcquirer::~ImageAcquirer(void)
{
}

cv::Mat ImageAcquirer::AcquireImage(void)
{
	std::string filename;
	std::cout << "Filename: ";
	std::cin >> filename;
	return cv::imread(filename.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
}