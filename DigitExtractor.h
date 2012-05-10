#pragma once

#include <opencv2\core\core.hpp>
#include <boost\optional.hpp>

class DigitExtractor
{
public:
	DigitExtractor(void);
	~DigitExtractor(void);

	boost::optional<cv::Mat> ExtractDigit(unsigned int col, unsigned int row,
										  unsigned int thresh);
	void LoadImage(cv::Mat& img);

private:
	void Preprocess(cv::Mat* img);
	cv::Mat input_img;
	cv::Mat cell_img;
	cv::Mat tmp_img;
	int cell_width;
	int cell_height;
	int cell_area;
	bool ready_flag;
};

