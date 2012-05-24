#pragma once

#include "SudokuExtractor.h"
#include "DigitExtractor.h"
#include <opencv2\core\core.hpp>
#include <vector>

struct SudokuCellImg
{
	unsigned int row;
	unsigned int col;
	cv::Mat img;
};

class ImageProcessing
{
public:
	ImageProcessing(void);
	~ImageProcessing(void);

	std::vector<SudokuCellImg> Run(void);
	void ImageLoad(cv::Mat& img);
	cv::Mat GetSudoku(void);

private:
	cv::Mat input_img;
	SudokuExtractor sudoku_extractor;
	DigitExtractor digit_extractor;
	bool ready_flag;
};

