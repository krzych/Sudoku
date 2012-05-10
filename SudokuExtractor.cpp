#include "StdAfx.h"
#include "SudokuExtractor.h"
#include "ImageUtilities.h"

cv::Size SudokuExtractor::default_size = cv::Size(540, 540);

SudokuExtractor::SudokuExtractor(void)
	: extracted_flag(false)
	, ready_flag(false)
{
}

SudokuExtractor::~SudokuExtractor(void)
{
}

void SudokuExtractor::LoadImage(cv::Mat& img)
{
	input_img = img.clone();
	tmp_img = cv::Mat(input_img.size(), CV_8UC1);
	ready_flag = true;
}

cv::Mat SudokuExtractor::GetSudoku(void)
{
	assert(ready_flag == true);

	if(extracted_flag == false) {
		Preprocess();
		Extract();
	}
	return output_img.clone();
}
	
cv::Mat SudokuExtractor::GetTransformationMatrix(void)
{
	assert(ready_flag == true);

	if(extracted_flag == false) {
		Preprocess();
		Extract();
	}
	return transformation_matrix.clone();
}

void SudokuExtractor::SetDefaultSize(cv::Size size)
{
	if(size.height > 50 && size.height > 50) default_size = size;
}

void SudokuExtractor::Preprocess(void)
{
	img_utilities::GaussianBlur(&input_img, &tmp_img, cv::Size(11, 11), 0);
	img_utilities::AdaptiveThreshold(&tmp_img, &tmp_img, 255, 
		                              ADAPTIVE_THRESHOLD_MEAN_C, 
									  THRESH_BINARY_INV, 5, 2);

	cv::Mat kernel = (cv::Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
	img_utilities::Dilate(&tmp_img, &tmp_img, kernel);
	img_utilities::FindBiggestBlob(&tmp_img);
	img_utilities::Erode(&tmp_img, &tmp_img, kernel);
}
	
void SudokuExtractor::Extract(void)
{
	cv::Point vertices[4];
	img_utilities::GetOuterBoxVertices(tmp_img, vertices);

	int width  = (int)(sqrt(pow((double)(vertices[0].x - vertices[1].x), 2) + 
		          pow((double)(vertices[0].y - vertices[1].y), 2)));
	int length = (int)(sqrt(pow((double)(vertices[2].x - vertices[1].x), 2) + 
		          pow((double)(vertices[2].y - vertices[1].y), 2)));

	cv::Point2f src[4] = {vertices[0],   //top_left
		                  vertices[1],   //top_right
						  vertices[2],   //down_right
						  vertices[3]};  //down_left

	cv::Point2f dst[4] = {cv::Point2f(0, 0), 
		                  cv::Point2f(width-1.f, 0), 
						  cv::Point2f(width-1.f, length-1.f), 
						  cv::Point2f(0, length-1.f)};

	tmp_img = cv::Mat(cv::Size(width, length), CV_8UC1);
	transformation_matrix = img_utilities::GetPerspectiveTransform(src, dst);
	img_utilities::WarpPerspective(&input_img, &tmp_img, transformation_matrix, cv::Size(width, length));

	output_img = cv::Mat(default_size, CV_8UC1);
	img_utilities::Resize(tmp_img, &output_img, INTER_LINEAR);
	
	extracted_flag = true;
}