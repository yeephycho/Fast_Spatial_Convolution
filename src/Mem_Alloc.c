#include <assert.h>
#include "Mem_Alloc.h"

void* alloc_aligned_float32_buffer(unsigned int alignment, size_t mem_size, float val){
	void* ptr;
	int check_code = posix_memalign(&ptr, alignment, mem_size * sizeof(float));
	float* data_ptr = ptr;
	for(register int i = 0; i < mem_size; ++i){
    	data_ptr[i] = val;
	}
    assert(check_code == 0);
    return ptr;
};


//	  Candidate methods
//
//    void* mem_ptr = malloc(sizeof(float)*256*256 + 15);
//    float* input_data_ptr = (float*)(((uintptr_t)mem_ptr + 15) & ~ (uintptr_t)0x0F);
//    printf("Matrix started at address: %p, this address divides 16 is: %lu\n", input_data_ptr, (size_t)input_data_ptr / 16);
//    int rc;
//    float* input_data_ptr = valloc(sizeof(float)*256*256);
//    float* ptr = aligned_alloc(64, sizeof(float)*256*256);
//    free(ptr);
//    void* ptr;
//    int rc = alloc_aligned_mem(ptr, 64, sizeof(float)*256*256);
//    printf("Return value of posix_memalign is :%d\n", rc);
//    float* input_data_ptr = ptr;
    
//    void* ptr;
//    int rc = posix_memalign(&ptr, 64, sizeof(float)*256*256);
//    printf("Return value of posix_memalign is :%d\n", rc);
//    free(ptr);
//    float* input_data_ptr = ptr;
    
//    printf("From host begin %p\n", input_dataptr);
