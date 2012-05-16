#include "stdafx.h"
#include "ParameterSetterCallers.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef LoadImage
#undef LoadImage
#endif

extern "C" SUDOKUDLL_API ParameterSetter* CreateParameterSetter(void)
{
	return new ParameterSetter();
}

extern "C" SUDOKUDLL_API void DisposeParameterSetter(ParameterSetter* p_object)
{
	delete p_object;
}

extern "C" SUDOKUDLL_API void CallLoadImage(ParameterSetter* p_object, const char* file_name)
{
	p_object->LoadImage(file_name);
}

extern "C" SUDOKUDLL_API void CallViewInputImage(ParameterSetter* p_object)
{
	p_object->ViewInputImage();
}

extern "C" SUDOKUDLL_API void CallClearAllAdjustFlags(ParameterSetter* p_object)
{
	p_object->ClearAllAdjustFlags();
}
	
extern "C" SUDOKUDLL_API void CallSetSEKernelSizeGauss(ParameterSetter* p_object, int kernel_size)
{
	p_object->SetSEKernelSizeGauss(kernel_size);
}

extern "C" SUDOKUDLL_API int CallGetSEKernelSizeGauss(ParameterSetter* p_object)
{
	return p_object->GetSEKernelSizeGauss();
}

extern "C" SUDOKUDLL_API void CallSetSEBlockSize(ParameterSetter* p_object, int block_size)
{
	p_object->SetSEBlockSize(block_size);
}

extern "C" SUDOKUDLL_API int CallGetSEBlockSize(ParameterSetter* p_object)
{
	return p_object->GetSEBlockSize();
}

extern "C" SUDOKUDLL_API void CallSetSEC(ParameterSetter* p_object, double c)
{
	p_object->SetSEC(c);
}

extern "C" SUDOKUDLL_API double CallGetSEC(ParameterSetter* p_object)
{
	return p_object->GetSEC();
}

extern "C" SUDOKUDLL_API void CallSetSEContourAreaThresh(ParameterSetter* p_object, int thresh)
{
	p_object->SetSEContourAreaThresh(thresh);
}

extern "C" SUDOKUDLL_API int CallGetSEContourAreaThresh(ParameterSetter* p_object)
{
	return p_object->GetSEContourAreaThresh();
}

extern "C" SUDOKUDLL_API void CallSetSEKernelSizeMorph(ParameterSetter* p_object, int kernel_size)
{
	p_object->SetSEKernelSizeMorph(kernel_size);
}

extern "C" SUDOKUDLL_API int CallGetSEKernelSizeMorph(ParameterSetter* p_object)
{
	return p_object->GetSEKernelSizeMorph();
}

extern "C" SUDOKUDLL_API void CallSetDEBlockSize(ParameterSetter* p_object, int block_size, unsigned int col, unsigned int row)
{
	p_object->SetDEBlockSize(block_size, col, row);
}
	
extern "C" SUDOKUDLL_API int CallGetDEBlockSize(ParameterSetter* p_object)
{
	return p_object->GetDEBlockSize();
}

extern "C" SUDOKUDLL_API void CallSetDEC(ParameterSetter* p_object, double c, unsigned int col, unsigned int row)
{
	p_object->SetDEC(c, col, row);
}

extern "C" SUDOKUDLL_API double CallGetDEC(ParameterSetter* p_object)
{
	return p_object->GetDEC();
}

extern "C" SUDOKUDLL_API void CallSetDEPercentage(ParameterSetter* p_object, int percentage, unsigned int col, unsigned int row)
{
	p_object->SetDEPercentage(percentage, col, row);
}

extern "C" SUDOKUDLL_API int CallGetDEPercentage(ParameterSetter* p_object)
{
	return p_object->GetDEPercentage();
}

extern "C" SUDOKUDLL_API void CallSetDEN(ParameterSetter* p_object, int n, unsigned int col, unsigned int row)
{
	p_object->SetDEN(n, col, row);
}

extern "C" SUDOKUDLL_API int CallGetDEN(ParameterSetter* p_object)
{
	return 	p_object->GetDEN();
}

extern "C" SUDOKUDLL_API void CallSetDEKernelSizeMorph(ParameterSetter* p_object, int kernel_size, unsigned int col, unsigned int row)
{
	p_object->SetDEKernelSizeMorph(kernel_size, col, row);
}

extern "C" SUDOKUDLL_API int CallGetDEKernelSizeMorph(ParameterSetter* p_object)
{
	return p_object->GetDEKernelSizeMorph();
}