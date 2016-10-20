#ifndef ALLOC_MEM_ALIGN_H_
#define ALLOC_MEM_ALIGN_H_

#include <stdlib.h>
#include <stdio.h>

extern void* alloc_aligned_float32_buffer(unsigned int alignment, size_t mem_size, float val);

#endif	// #ifdef ALLOC_MEM_ALIGN_H_
