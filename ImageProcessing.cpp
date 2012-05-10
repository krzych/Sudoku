#include "StdAfx.h"
#include "ImageProcessing.h"
#include <boost\optional.hpp>


ImageProcessing::ImageProcessing(void)
	: ready_flag(false)
{
}


ImageProcessing::~ImageProcessing(void)
{
}

std::vector<SudokuCellImg> ImageProcessing::Run(void)
{
	assert(ready_flag == true);

	sudoku_extractor.LoadImage(input_img);
	digit_extractor.LoadImage(sudoku_extractor.GetSudoku());

	std::vector<SudokuCellImg> v;
	for(int row = 0; row < 9; ++row) {
		for(int col = 0; col < 9; ++col) {
			boost::optional<cv::Mat> digit = 
				digit_extractor.ExtractDigit(col, row, 50); //!!threshold
			if(digit) {
				SudokuCellImg cell;
				cell.row = row;
				cell.col = col;
				cell.img = (*digit).clone();
				v.push_back(cell);
			}
		}
	}
	return v;
}
	
void ImageProcessing::LoadImage(cv::Mat& img)
{
	input_img = img.clone();
	ready_flag = true;
}

cv::Mat ImageProcessing::GetSudoku(void)
{
	return sudoku_extractor.GetSudoku();
}