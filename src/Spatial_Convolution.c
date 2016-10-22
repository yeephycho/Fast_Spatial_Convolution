#include "Spatial_Convolution.h"


#define MATRIX_WIDTH 256
#define MATRIX_HEIGHT 256
#define MATRIX_CHANNEL 32
#define MATRIX_DEPTH 1

#define KERNEL_WIDTH 3
#define KERNEL_HEIGHT 3
#define KERNEL_CHANNEL MATRIX_CHANNEL
#define KERNEL_DEPTH 64

#define FEATURE_WIDTH (MATRIX_WIDTH - KERNEL_WIDTH + 1)
#define FEATURE_HEIGHT (MATRIX_HEIGHT - KERNEL_HEIGHT + 1)
#define FEATURE_CHANNEL 1
#define FEATURE_DEPTH KERNEL_DEPTH


int spatial_convolution_float32(float* input_ptr, float* kernel_ptr, float* output_ptr){
	for(int h = 0; h < FEATURE_HEIGHT; h++){
		for(int w = 0; w < FEATURE_WIDTH; w++){
			for(int c = 0; c < MATRIX_CHANNEL; c++){
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 0) * MATRIX_WIDTH + w + 0] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 0];
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 0) * MATRIX_WIDTH + w + 1] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 1];
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 0) * MATRIX_WIDTH + w + 2] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 2];
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 1) * MATRIX_WIDTH + w + 0] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 3];
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 1) * MATRIX_WIDTH + w + 1] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 4];
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 1) * MATRIX_WIDTH + w + 2] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 5];
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 2) * MATRIX_WIDTH + w + 0] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 6];
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 2) * MATRIX_WIDTH + w + 1] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 7];
				output_ptr[h * FEATURE_WIDTH + w] += input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 2) * MATRIX_WIDTH + w + 2] * kernel_ptr[c * KERNEL_WIDTH * KERNEL_HEIGHT + 8];
			}
		}
	}
	return 0;
};

int spatial_convolution_float32_mm(float* input_ptr, float* kernel_ptr, float* output_ptr){
//	long long int t1 = timestamp_in_milliseconds();

	size_t cache_buffer_size = FEATURE_WIDTH * FEATURE_HEIGHT * FEATURE_CHANNEL * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL;
    float* cache_data_ptr = alloc_aligned_float32_buffer(64, cache_buffer_size, 0.0f);

//    long long int t2 = timestamp_in_milliseconds();

    int count = 0;
	for(int h = 0; h < FEATURE_HEIGHT; h++){
		for(int w = 0; w < FEATURE_WIDTH; w++){
			for(int c = 0; c < MATRIX_CHANNEL; c++){
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 0) * MATRIX_WIDTH + w + 0];
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 0) * MATRIX_WIDTH + w + 1];
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 0) * MATRIX_WIDTH + w + 2];
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 1) * MATRIX_WIDTH + w + 0];
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 1) * MATRIX_WIDTH + w + 1];
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 1) * MATRIX_WIDTH + w + 2];
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 2) * MATRIX_WIDTH + w + 0];
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 2) * MATRIX_WIDTH + w + 1];
				cache_data_ptr[count++] = input_ptr[c * MATRIX_WIDTH * MATRIX_HEIGHT + (h + 2) * MATRIX_WIDTH + w + 2];
			}
		}
	}

//	long long int t3 = timestamp_in_milliseconds();

	for(register int i = 0; i < FEATURE_WIDTH * FEATURE_HEIGHT; i++){
		for(register int c = 0; c < KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL; c+=9){
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 0] * kernel_ptr[c + 0];
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 1] * kernel_ptr[c + 1];
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 2] * kernel_ptr[c + 2];
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 3] * kernel_ptr[c + 3];
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 4] * kernel_ptr[c + 4];
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 5] * kernel_ptr[c + 5];
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 6] * kernel_ptr[c + 6];
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 7] * kernel_ptr[c + 7];
			output_ptr[i] += cache_data_ptr[i * KERNEL_WIDTH * KERNEL_HEIGHT * KERNEL_CHANNEL + c + 8] * kernel_ptr[c + 8];
		}
	}

//	long long int t4 = timestamp_in_milliseconds();

//	printf("Memory Allocation takes: %llu\n", t2 - t1);
//	printf("Memory Arrange takes: %llu\n", t3 - t2);
//	printf("Multiplication takes: %llu\n", t4 - t3);

	free(cache_data_ptr);
	cache_data_ptr = NULL;
	return 0;
};
