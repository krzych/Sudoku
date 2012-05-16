#include "StdAfx.h"
#include "DigitExtractor.h"
#include "ImageUtilities.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <fstream>
#include <boost\archive\xml_oarchive.hpp>
#include <boost\archive\xml_iarchive.hpp>
#include <vector>

using namespace cv;

DigitExtractor::DigitExtractor(void)
	: ready_flag(false)
	, adjust_flag(false)
	, file_name_("DigitExtractor.xml")
{
	if(Load() == false) SetDefaultParameters();
	ClearAdjustFlags();
}


DigitExtractor::~DigitExtractor(void)
{
	Save();
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

void DigitExtractor::ClearAdjustFlags(void)
{
	/*threshold_flag = false;
	fill_borders_flag = false;
	n_blobs_flag = false;
	blob_flag = false;*/
	adjust_flag = false;
}

void DigitExtractor::Preprocess(cv::Mat* img)
{
	if(adjust_flag) {
		imshow("input", *img);
		cvMoveWindow("input", 0, 0);
	}

	int step = 200;

	img_utilities::AdaptiveThreshold(img, img, 255, ADAPTIVE_THRESHOLD_MEAN_C, cv::THRESH_BINARY_INV, block_size_, c_);
	if(adjust_flag) {
		imshow("thresh", *img);
		cvMoveWindow("thresh", 1*step, 0);
	}

	img_utilities::FloodFillBorders(img, percentage_);
	if(adjust_flag) {
		imshow("filled", *img);
		cvMoveWindow("filled", 2*step, 0);
	}

	img_utilities::FindNBiggestBlobs(img, n_);
	if(adjust_flag) {
		imshow("nblob", *img);
		cvMoveWindow("nblob", 3*step, 0);
	}

	Size kernel_size = Size(kernel_size_morph_, kernel_size_morph_);
	Mat kernel = getStructuringElement(MORPH_RECT, kernel_size);
	img_utilities::Dilate(img, img, kernel);
	img_utilities::FindBiggestBlob(img);
	img_utilities::Erode(img, img, kernel);
	if(adjust_flag) {
		imshow("blob", *img);
		cvMoveWindow("blob", 4*step, 0);
	}


	if(adjust_flag) {
		waitKey();
		destroyWindow("input");
		destroyWindow("thresh");
		destroyWindow("filled");
		destroyWindow("nblob");
		destroyWindow("blob");
	}
}

void DigitExtractor::SetDefaultParameters(void)
{
	block_size_ = 7;
	c_ = 2;
	percentage_ = 20;
	n_ = 2;
	kernel_size_morph_ = 3;
}


bool DigitExtractor::Load(void)
{
	using boost::serialization::make_nvp;
	
	std::ifstream ifs(file_name_);
	if(ifs.is_open() == false) return false;
	boost::archive::xml_iarchive xml(ifs);
	xml >> BOOST_SERIALIZATION_NVP(*this);
	
	return true;
}
	
bool DigitExtractor::Save(void)
{
	using boost::serialization::make_nvp;

	std::ofstream ofs(file_name_);
	if(ofs.is_open() == false) return false;
	boost::archive::xml_oarchive xml(ofs);
	xml << make_nvp("params", *this);

	return true;
}