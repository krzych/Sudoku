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
	void SetSEKernelSizeGauss(int kernel_size);
	void SetSEBlockSize(int block_size);
	void SetSEC(double c);
	void SetSEContourAreaThresh(int thresh);
	void SetSEKernelSizeMorph(int kernel_size);



private:
	SudokuExtractor sudoku_extractor;
	DigitExtractor digit_extractor;
	ImageAcquirer image_acquirer;
	Mat input_img;
	bool image_loaded_flag;

};

