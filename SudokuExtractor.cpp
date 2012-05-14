#include "StdAfx.h"
#include "SudokuExtractor.h"
#include "ImageUtilities.h"
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using std::vector;
using cv::Point;

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

	cv::imshow("Input image", input_img);
	cv::waitKey(100);
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

	vector<vector<Point>> squares;
	img_utilities::FindSquares(tmp_img.clone(), squares);
	if(squares.size() == 0) throw "Error";

	//find square with biggest area
	int index = 0;
	double max_area = -1;
	for(size_t i = 0; i < squares.size(); ++i) {
		double area = fabs(cv::contourArea(cv::Mat(squares[i])));
		if(area > max_area) {
			index = i;
			max_area = area;
		}
	}

	/*const Point* p = &squares[index][0];
    int n = (int)squares[index].size();
    polylines(input_img, &p, &n, 1, true, cv::Scalar::all(255), 3, CV_AA);
	cv::imshow("bla", input_img);
	cv::waitKey();*/

	cv::Rect rect = cv::boundingRect(squares[index]);
	offset = cv::Point(rect.x, rect.y);
	tmp_img = cv::Mat(tmp_img, rect).clone();

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

	cv::Point2f src[4] = {vertices[0] + offset,   //top_left
		                  vertices[1] + offset,   //top_right
						  vertices[2] + offset,   //down_right
						  vertices[3] + offset};  //down_left

	cv::Point2f dst[4] = {cv::Point2f(0, 0), 
		                  cv::Point2f(width-1.f, 0), 
						  cv::Point2f(width-1.f, length-1.f), 
						  cv::Point2f(0, length-1.f)};

	tmp_img = cv::Mat(cv::Size(width, length), CV_8UC1);
	transformation_matrix = img_utilities::GetPerspectiveTransform(src, dst);
	img_utilities::WarpPerspective(&input_img, &tmp_img, transformation_matrix, cv::Size(width, length));

	output_img = cv::Mat(default_size, CV_8UC1);
	img_utilities::Resize(tmp_img, &output_img, INTER_LINEAR);
	cv::imshow("Extracted SUDOKU", output_img);
	cv::waitKey(100);
	extracted_flag = true;
}