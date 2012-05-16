#ifndef PARAMETER_SETTER_CALLERS_H
#define PARAMETER_SETTER_CALLERS_H

#include "ParameterSetter.h"

#ifndef SUDOKUDLL_EXPORTS
	#define SUDOKUDLL_API __declspec(dllexport)
#else
	#define SUDOKUDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
	extern SUDOKUDLL_API ParameterSetter* CreateParameterSetter(void);
	extern SUDOKUDLL_API void   DisposeParameterSetter(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallLoadImage(ParameterSetter* p_object, const char* file_name);
	extern SUDOKUDLL_API void   CallViewInputImage(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallClearAllAdjustFlags(ParameterSetter* p_object);
	
	extern SUDOKUDLL_API void   CallSetSEKernelSizeGauss(ParameterSetter* p_object, int kernel_size);
	extern SUDOKUDLL_API int    CallGetSEKernelSizeGauss(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallSetSEBlockSize(ParameterSetter* p_object, int block_size);
	extern SUDOKUDLL_API int    CallGetSEBlockSize(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallSetSEC(ParameterSetter* p_object, double c);
	extern SUDOKUDLL_API double CallGetSEC(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallSetSEContourAreaThresh(ParameterSetter* p_object, int thresh);
	extern SUDOKUDLL_API int    CallGetSEContourAreaThresh(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallSetSEKernelSizeMorph(ParameterSetter* p_object, int kernel_size);
	extern SUDOKUDLL_API int    CallGetSEKernelSizeMorph(ParameterSetter* p_object);
	
	extern SUDOKUDLL_API void   CallSetDEBlockSize(ParameterSetter* p_object, int block_size, unsigned int col, unsigned int row);
	extern SUDOKUDLL_API int    CallGetDEBlockSize(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallSetDEC(ParameterSetter* p_object, double c, unsigned int col, unsigned int row);
	extern SUDOKUDLL_API double CallGetDEC(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallSetDEPercentage(ParameterSetter* p_object, int percentage, unsigned int col, unsigned int row);
	extern SUDOKUDLL_API int    CallGetDEPercentage(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallSetDEN(ParameterSetter* p_object, int n, unsigned int col, unsigned int row);
	extern SUDOKUDLL_API int    CallGetDEN(ParameterSetter* p_object);
	extern SUDOKUDLL_API void   CallSetDEKernelSizeMorph(ParameterSetter* p_object, int kernel_size, unsigned int col, unsigned int row);
	extern SUDOKUDLL_API int    CallGetDEKernelSizeMorph(ParameterSetter* p_object);

#ifdef __cplusplus
}
#endif

#endif // PARAMETER_SETTER_CALLERS_H