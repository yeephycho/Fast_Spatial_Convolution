#ifndef _MEM_ALLOC_H_
#define _MEM_ALLOC_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifdef __APPLE__
    #include <sys/malloc.h>
#elif linux
    #include <malloc.h>
#else
    #include <malloc.h>
#endif  // #ifdef __APPLE__

extern void* alloc_aligned_float32_buffer(unsigned int alignment, size_t mem_size, float val);
extern void* alloc_aligned_float64_buffer(unsigned int alignment, size_t mem_size, double val);
extern void* alloc_aligned_int32_buffer(unsigned int alignment, size_t mem_size, int val);

extern void* alloc_float32_buffer(size_t mem_size, float val);
extern void* alloc_float64_buffer(size_t mem_size, double val);
extern void* alloc_int32_buffer(size_t mem_size, int val);

#endif	// #ifndef _MEM_ALLOC_H_
