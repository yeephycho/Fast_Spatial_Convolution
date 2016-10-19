#ifndef ALLOC_MEM_ALIGN_H_
#define ALLOC_MEM_ALIGN_H_
#include <stdlib.h>
#include <stdio.h>

int alloc_aligned_mem(void* data_ptr, unsigned int alignment, size_t mem_size);

#endif // #ifdef ALLOC_MEM_ALIGN_H_