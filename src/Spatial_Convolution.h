#ifndef _SPATIAL_CONVOLUTION_
#define _SPATIAL_CONVOLUTION_

#include "Mem_Alloc.h"
#include "Time.h"
#include "Global_Setting.h"
//#include <cblas.h>

extern int spatial_convolution_float32(float* input_ptr, float* kernel_ptr, float* output_ptr);
extern int spatial_convolution_float32_mm(float* input_ptr, float* kernel_ptr, float* output_ptr);
extern int spatial_convolution_float32_mm_blas(float* input_ptr, float* kernel_ptr, float* output_ptr);

#endif	//	_SPATIAL_CONVOLUTION_
