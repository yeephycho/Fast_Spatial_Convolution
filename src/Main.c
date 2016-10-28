#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "Time.h"
#include "Mem_Alloc.h"
#include "Spatial_Convolution.h"
#include "Global_Setting.h"


int main(int argc, char** argv){

    size_t matrix_buffer_size = MATRIX_HEIGHT * MATRIX_WIDTH * MATRIX_CHANNEL;
    float* input_data_ptr = alloc_aligned_float32_buffer(64, matrix_buffer_size, 1.0f);

    size_t kernel_buffer_size = KERNEL_HEIGHT * KERNEL_WIDTH * KERNEL_CHANNEL;
    float* kernel_data_ptr = alloc_aligned_float32_buffer(64, kernel_buffer_size, 1.0f);

    size_t feature_buffer_size = FEATURE_HEIGHT * FEATURE_WIDTH * FEATURE_CHANNEL;
    float* feature_data_ptr = alloc_aligned_float32_buffer(64, feature_buffer_size, 0.0f);

    long long int begin = timestamp_in_milliseconds();

    int rt = spatial_convolution_float32(input_data_ptr, kernel_data_ptr, feature_data_ptr);

    long long int end = timestamp_in_milliseconds();


    size_t feature_buffer_size_mm = FEATURE_HEIGHT * FEATURE_WIDTH * FEATURE_CHANNEL;
    float* feature_data_ptr_mm = alloc_aligned_float32_buffer(64, feature_buffer_size_mm, 0.0f);

    long long int begin_mm = timestamp_in_milliseconds();

    rt = spatial_convolution_float32_mm(input_data_ptr, kernel_data_ptr, feature_data_ptr_mm);

    long long int end_mm = timestamp_in_milliseconds();

    printf("Time spend for aligned convolution operation is: %llu milliseconds\n", end - begin);
    printf("Time spend for aligned_mm convolution operation is: %llu milliseconds\n", end_mm - begin_mm);

    free(input_data_ptr);
    free(kernel_data_ptr);
    free(feature_data_ptr);
    free(feature_data_ptr_mm);

    return 0;
}
