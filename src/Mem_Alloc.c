#include "Mem_Alloc.h"


/****************************************
	These function allocate aligned memory buffer to store input, kernel or output data.
	alignment: Must be 2 to the power of N, N should be an integer.
	mem_size: Number of the element the memory contains.
	val: Initial value of the buffer.
*****************************************/

void* alloc_aligned_float32_buffer(unsigned int alignment, size_t mem_size, float val){
	assert((alignment & (alignment - 1)) == 0);
	void* ptr;
	int check_code = posix_memalign(&ptr, alignment, mem_size * sizeof(float));
	assert(check_code == 0);
	float* data_ptr = ptr;
	for(register int i = 0; i < mem_size; ++i){
    	data_ptr[i] = val;
	}
    return ptr;
};

void* alloc_aligned_float64_buffer(unsigned int alignment, size_t mem_size, double val){
	assert((alignment & (alignment - 1)) == 0);
	void* ptr;
	int check_code = posix_memalign(&ptr, alignment, mem_size * sizeof(double));
	assert(check_code == 0);
	double* data_ptr = ptr;
	for(register int i = 0; i < mem_size; ++i){
		data_ptr[i] = val;
	}
	return ptr;
};

void* alloc_aligned_int32_buffer(unsigned int alignment, size_t mem_size, int val){
	assert((alignment & (alignment - 1)) == 0);
	void* ptr;
	int check_code = posix_memalign(&ptr, alignment, mem_size * sizeof(int));
	assert(check_code == 0);
	int* data_ptr = ptr;
	for(register int i = 0; i < mem_size; ++i){
		data_ptr[i] = val;
	}
	return ptr;
}


/****************************************
	These function allocate memory buffer to store input, kernel or output data, no alignment guaranteed.
	There are saying issue that Mac will guarantee the alignment allocation automatically.
	mem_size: Number of the element the memory contains.
	val: Initial value of the buffer.
*****************************************/

void* alloc_float32_buffer(size_t mem_size, float val){
	void* ptr;
	ptr = malloc(mem_size * sizeof(float));
	assert(ptr != NULL);
	float* data_ptr = ptr;
	for(register int i = 0; i < mem_size; ++i){
    	data_ptr[i] = val;
	}
	return ptr;
};

void* alloc_float64_buffer(size_t mem_size, double val){
	void* ptr;
	ptr = malloc(mem_size * sizeof(double));
	assert(ptr != NULL);
	double* data_ptr = ptr;
	for(register int i = 0; i < mem_size; ++i){
    	data_ptr[i] = val;
	}
	return ptr;
};

void* alloc_int32_buffer(size_t mem_size, int val){
	void* ptr;
	ptr = malloc(mem_size * sizeof(int));
	assert(ptr != NULL);
	int* data_ptr = ptr;
	for(register int i = 0; i < mem_size; ++i){
    	data_ptr[i] = val;
	}
	return ptr;
};
