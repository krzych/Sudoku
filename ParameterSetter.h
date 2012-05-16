#pragma once

#include "ImageProcessing.h"
#include "SudokuExtractor.h"
#include "DigitExtractor.h"
#include "ImageAcquirer.h"
#include <opencv2\core\core.hpp>
#include <boost\serialization\nvp.hpp>

using namespace cv;

class ParameterSetter
{
public:
	ParameterSetter(void);
	~ParameterSetter(void);

	void LoadImage(const char* file_name);
	void ViewInputImage(void);
	void ClearAllAdjustFlags(void);

	//sudoku extractor(SE) param setting funcs
	void   SetSEKernelSizeGauss(int kernel_size);
	int    GetSEKernelSizeGauss(void);
	void   SetSEBlockSize(int block_size);
	int    GetSEBlockSize(void);
	void   SetSEC(double c);
	double GetSEC(void);
	void   SetSEContourAreaThresh(int thresh);
	int    GetSEContourAreaThresh(void);
	void   SetSEKernelSizeMorph(int kernel_size);
	int    GetSEKernelSizeMorph(void);

	//digit extractor(DE) param setting funcs
	void   SetDEBlockSize(int block_size, unsigned int col, unsigned int row);
	int    GetDEBlockSize(void);
	void   SetDEC(double c, unsigned int col, unsigned int row);
	double GetDEC(void);
	void   SetDEPercentage(int percentage, unsigned int col, unsigned int row);
	int    GetDEPercentage(void);
	void   SetDEN(int n, unsigned int col, unsigned int row);
	int    GetDEN(void);
	void   SetDEKernelSizeMorph(int kernel_size, unsigned int col, unsigned int row);
	int    GetDEKernelSizeMorph(void);

private:
	SudokuExtractor sudoku_extractor;
	DigitExtractor digit_extractor;
	ImageAcquirer image_acquirer;
	Mat input_img;
	bool image_loaded_flag;

};

