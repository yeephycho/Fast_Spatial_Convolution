#include "Alloc_Mem.h"
int alloc_aligned_mem(void* data_ptr, unsigned int alignment, size_t mem_size){
	int rc = posix_memalign(&data_ptr, alignment, mem_size);
    return rc;
};
