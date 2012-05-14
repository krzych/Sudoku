#include "StdAfx.h"
#include "DigitExtractor.h"
#include "ImageUtilities.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <vector>

using namespace cv;

DigitExtractor::DigitExtractor(void)
	: ready_flag(false)
{
}


DigitExtractor::~DigitExtractor(void)
{
}

boost::optional<cv::Mat> DigitExtractor::ExtractDigit(unsigned int col, 
													  unsigned int row, 
													  unsigned int thresh)
{
	assert(ready_flag == true);

	cell_img = cv::Mat(input_img, cv::Rect(col*cell_width, row*cell_height, cell_width, cell_height));
	Preprocess(&cell_img);

	cv::Moments m = cv::moments(cell_img, true);
	if(m.m00  > cell_area/thresh) {
		static std::vector<std::vector<cv::Point>> v;
		tmp_img = cell_img.clone();
		cv::findContours(tmp_img, v, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		int area = 0;
		int index;
		for(int i = 0; i < (int)v.size(); ++i) {
			if(area < (int)v[i].size()) index = i;
		}
		cv::Rect rect = cv::boundingRect(v[index]);
		return boost::optional<cv::Mat>(cv::Mat(cell_img, rect).clone());
	} else {
		return boost::optional<cv::Mat>();
	}
}
	
void DigitExtractor::LoadImage(cv::Mat& img)
{
	input_img = img.clone();
	cell_width  = (int)floor(input_img.size().width /9.0);
	cell_height = (int)floor(input_img.size().height/9.0);
	cell_area = cell_width * cell_height; 
	ready_flag = true;
}

void DigitExtractor::Preprocess(cv::Mat* img)
{
	bool adjust = false;

	if(adjust) {
		imshow("input", *img);
		cvMoveWindow("input", 0, 100);
	}

	img_utilities::AdaptiveThreshold(img, img, 255, ADAPTIVE_THRESHOLD_MEAN_C, cv::THRESH_BINARY_INV, 7, 2);
	if(adjust) {
		imshow("thresh", *img);
		cvMoveWindow("thresh", 250, 100);
	}

	img_utilities::FloodFillBorders(img, 20);
	if(adjust) {
		imshow("filled", *img);
		cvMoveWindow("filled", 500, 100);
	}

	img_utilities::FindBiggestBlob(img);
	if(adjust) {
		imshow("blob", *img);
		cvMoveWindow("blob", 750, 100);
	}
	
	if(adjust) {
		waitKey();
	}
	destroyWindow("input");
	destroyWindow("thresh");
	destroyWindow("filled");
	destroyWindow("blob");
}