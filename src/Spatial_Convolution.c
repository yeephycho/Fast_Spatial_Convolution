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
#define FEATURE_DEPTH 64


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
