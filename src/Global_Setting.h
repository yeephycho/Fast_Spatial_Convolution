#ifndef _GLOBAL_SETTING_
#define _GLOBAL_SETTING_


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