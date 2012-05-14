#pragma once

#include <opencv2\core\core.hpp>

class SudokuExtractor
{
public:
	SudokuExtractor(void);
	~SudokuExtractor(void);

	void LoadImage(cv::Mat& img);
	cv::Mat GetSudoku(void);
	cv::Mat GetTransformationMatrix(void);
	static void SetDefaultSize(cv::Size size);

private:
	void Preprocess(void);
	void Extract(void);

	cv::Mat input_img;
	cv::Mat tmp_img;
	cv::Mat output_img;
	cv::Mat transformation_matrix;
	cv::Point offset;
	static cv::Size default_size;
	bool extracted_flag;
	bool ready_flag;
};

