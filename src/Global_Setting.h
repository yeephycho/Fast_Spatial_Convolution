#ifndef _GLOBAL_SETTING_
#define _GLOBAL_SETTING_


#define MATRIX_WIDTH 128 
#define MATRIX_HEIGHT 128
#define MATRIX_CHANNEL 32
#define MATRIX_DEPTH 1
    
#define KERNEL_WIDTH 3
#define KERNEL_HEIGHT 3
#define KERNEL_CHANNEL MATRIX_CHANNEL
#define KERNEL_DEPTH 64

#define FEATURE_WIDTH (MATRIX_WIDTH - KERNEL_WIDTH + 1)
#define FEATURE_HEIGHT (MATRIX_HEIGHT - KERNEL_HEIGHT + 1)
#define FEATURE_CHANNEL 1
#define FEATURE_DEPTH 64


#ifdef CBLAS
    #include <cblas.h>
#endif  // #ifdef CBLAS


#ifdef OMP
	#include <omp.h>
#endif	// #ifdef OMP


#ifdef OPENCL
	#ifdef __APPLE__
		#include <OpenCL/opencl.h>
	#elif linux
		#include <CL/cl.h>
	#elif __WIN32__
		#include <cl.h>
	#else
		#include <CL/cl.h>
	#endif	//	#ifdef __APPLE__
#endif	//	#ifdef OPENCL


#endif	//	_GLOBAL_SETTING_
