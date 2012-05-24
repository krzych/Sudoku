#include "ParameterSetter.h"
#include <opencv2\highgui\highgui.hpp>

ParameterSetter::ParameterSetter(void)
	: image_loaded_flag(false)
{
	
}


ParameterSetter::~ParameterSetter(void)
{

}

void ParameterSetter::ImageLoad(const char* file_name)
{
	sudoku_extractor.ClearAdjustFlags();
	input_img = image_acquirer.AcquireImage(file_name);
	sudoku_extractor.ImageLoad(input_img);
	image_loaded_flag = true;
}

void ParameterSetter::ViewInputImage(void)
{
	if(image_loaded_flag == false) return;

	imshow("input", input_img);
	cvWaitKey();
	destroyWindow("input");
}

void ParameterSetter::ClearAllAdjustFlags(void)
{
	sudoku_extractor.ClearAdjustFlags();
	digit_extractor.ClearAdjustFlags();
}

void ParameterSetter::SetSEKernelSizeGauss(int kernel_size)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetKernelSizeGauss(kernel_size);
	sudoku_extractor.SetGaussFlag();
	sudoku_extractor.GetSudoku();
}

int ParameterSetter::GetSEKernelSizeGauss(void)
{
	return sudoku_extractor.GetKernelSizeGauss();
}

void ParameterSetter::SetSEBlockSize(int block_size)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetBlockSize(block_size);
	sudoku_extractor.SetThresholdFlag();
	sudoku_extractor.GetSudoku();
}

int ParameterSetter::GetSEBlockSize(void)
{
	return sudoku_extractor.GetBlockSize();
}

void ParameterSetter::SetSEC(double c)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetC(c);
	sudoku_extractor.SetThresholdFlag();
	sudoku_extractor.GetSudoku();
}

double ParameterSetter::GetSEC(void)
{
	return sudoku_extractor.GetC();
}

void ParameterSetter::SetSEContourAreaThresh(int thresh)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetContourAreaThresh(thresh);
	sudoku_extractor.SetSquareFlag();
	sudoku_extractor.GetSudoku();
}

int ParameterSetter::GetSEContourAreaThresh(void)
{
	return sudoku_extractor.GetContourAreaThresh();
}

void ParameterSetter::SetSEKernelSizeMorph(int kernel_size)
{
	if(image_loaded_flag == false) return;

	sudoku_extractor.SetKernelSizeMorph(kernel_size);
	sudoku_extractor.SetBlobFlag();
	sudoku_extractor.GetSudoku();
}

int ParameterSetter::GetSEKernelSizeMorph(void)
{
	return sudoku_extractor.GetKernelSizeMorph();
}

void ParameterSetter::SetDEBlockSize(int block_size, unsigned int col, unsigned int row)
{
	if(image_loaded_flag == false) return;
	
	digit_extractor.ImageLoad(sudoku_extractor.GetSudoku());
	digit_extractor.SetBlockSize(block_size);
	digit_extractor.SetAdjustFlag();
	digit_extractor.ExtractDigit(col, row, 50); //!!!
}

int ParameterSetter::GetDEBlockSize(void)
{
	return digit_extractor.GetBlockSize();
}

void ParameterSetter::SetDEC(double c, unsigned int col, unsigned int row)
{
	if(image_loaded_flag == false) return;

	digit_extractor.ImageLoad(sudoku_extractor.GetSudoku());
	digit_extractor.SetC(c);
	digit_extractor.SetAdjustFlag();
	digit_extractor.ExtractDigit(col, row, 50); 
}

double ParameterSetter::GetDEC(void)
{
	return digit_extractor.GetC(); 
}

void ParameterSetter::SetDEPercentage(int percentage, unsigned int col, unsigned int row)
{
	if(image_loaded_flag == false) return;

	digit_extractor.ImageLoad(sudoku_extractor.GetSudoku());
	digit_extractor.SetPercentage(percentage);
	digit_extractor.SetAdjustFlag();
	digit_extractor.ExtractDigit(col, row, 50); 
}

int ParameterSetter::GetDEPercentage(void)
{
	return digit_extractor.GetPercentage();
}

void ParameterSetter::SetDEN(int n, unsigned int col, unsigned int row)
{
	if(image_loaded_flag == false) return;

	digit_extractor.ImageLoad(sudoku_extractor.GetSudoku());
	digit_extractor.SetN(n);
	digit_extractor.SetAdjustFlag();
	digit_extractor.ExtractDigit(col, row, 50);
}

int ParameterSetter::GetDEN(void)
{
	return digit_extractor.GetN();
}

void ParameterSetter::SetDEKernelSizeMorph(int kernel_size, unsigned int col, unsigned int row)
{
	if(image_loaded_flag == false) return;

	digit_extractor.ImageLoad(sudoku_extractor.GetSudoku());
	digit_extractor.SetKernelSizeMorph(kernel_size);
	digit_extractor.SetAdjustFlag();
	digit_extractor.ExtractDigit(col, row, 50);
}

int ParameterSetter::GetDEKernelSizeMorph(void)
{
	return digit_extractor.GetKernelSizeMorph();
}