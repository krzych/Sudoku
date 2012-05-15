#include "StdAfx.h"
#include "ParameterSetter.h"
#include <opencv2\highgui\highgui.hpp>

ParameterSetter::ParameterSetter(void)
	: image_loaded_flag(false)
{
	
}


ParameterSetter::~ParameterSetter(void)
{

}

void ParameterSetter::LoadImage(const char* file_name)
{
	sudoku_extractor.ClearAdjustFlags();
	input_img = image_acquirer.AcquireImage(file_name);
	sudoku_extractor.LoadImage(input_img);
	digit_extractor.LoadImage(sudoku_extractor.GetSudoku());
	image_loaded_flag = true;
}

void ParameterSetter::ViewInputImage(void)
{
	if(image_loaded_flag == false) return;

	imshow("input", input_img);
	cvWaitKey();
	destroyWindow("input");
}

void ParameterSetter::SetSEKernelSizeGauss(int kernel_size)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetKernelSizeGauss(kernel_size);
	sudoku_extractor.SetBlurFlag();
	sudoku_extractor.GetSudoku();
}

void ParameterSetter::SetSEBlockSize(int block_size)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetBlockSize(block_size);
	sudoku_extractor.SetThresholdFlag();
	sudoku_extractor.GetSudoku();
}

void ParameterSetter::SetSEC(double c)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetC(c);
	sudoku_extractor.SetThresholdFlag();
	sudoku_extractor.GetSudoku();
}

void ParameterSetter::SetSEContourAreaThresh(int thresh)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetContourAreaThresh(thresh);
	sudoku_extractor.SetFindSquareFlag();
	sudoku_extractor.GetSudoku();
}

void ParameterSetter::SetSEKernelSizeMorph(int kernel_size)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetKernelSizeMorph(kernel_size);
	sudoku_extractor.SetBlobFlag();
	sudoku_extractor.GetSudoku();
}
