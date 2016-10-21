#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


#include "Time.h"
#include "Mem_Alloc.h"
#include "Spatial_Convolution.h"


#ifdef CBLAS
    #include <cblas.h>
#endif  // #ifdef CBLAS


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

//    for(register int i = 0; i < FEATURE_HEIGHT*FEATURE_HEIGHT; ++i){
//        if(feature_data_ptr[i] != 288.0f){
//          printf("%d: %f\n", i, feature_data_ptr[i]);
//        }
//    }

    printf("Time spend for aligned convolution operation is: %llu milliseconds\n", end - begin);
    free(input_data_ptr);
    free(kernel_data_ptr);
    free(feature_data_ptr);

/*
    input_data_ptr = alloc_float32_buffer(mem_size, 1.0f);
    begin = timestamp_in_milliseconds();
    for(int i = 0; i < FEATURE_HEIGHT; i++){
        for(int j = 0; j < FEATURE_HEIGHT; j++){
           output_data_ptr[i*FEATURE_HEIGHT + j] = input_data_ptr[i*MATRIX_HEIGHT + j] * conv_kernel[0];
           output_data_ptr[i*FEATURE_HEIGHT + j] += input_data_ptr[i*MATRIX_HEIGHT + j + 1] * conv_kernel[1];
           output_data_ptr[i*FEATURE_HEIGHT + j] += input_data_ptr[i*MATRIX_HEIGHT + j + 2] * conv_kernel[2];
           output_data_ptr[i*FEATURE_HEIGHT + j] += input_data_ptr[(i+1)*MATRIX_HEIGHT + j] * conv_kernel[3];
           output_data_ptr[i*FEATURE_HEIGHT + j] += input_data_ptr[(i+1)*MATRIX_HEIGHT + j + 1] * conv_kernel[4];
           output_data_ptr[i*FEATURE_HEIGHT + j] += input_data_ptr[(i+1)*MATRIX_HEIGHT + j + 2] * conv_kernel[5];
           output_data_ptr[i*FEATURE_HEIGHT + j] += input_data_ptr[(i+2)*MATRIX_HEIGHT + j] * conv_kernel[6];
           output_data_ptr[i*FEATURE_HEIGHT + j] += input_data_ptr[(i+2)*MATRIX_HEIGHT + j + 1] * conv_kernel[7];
           output_data_ptr[i*FEATURE_HEIGHT + j] += input_data_ptr[(i+2)*MATRIX_HEIGHT + j + 2] * conv_kernel[8];
        }
    }
    end = timestamp_in_milliseconds();

    printf("Time spend for unaligned convolution operation is: %llu milliseconds\n", end - begin);

    
//    for(register int i = 0; i < FEATURE_HEIGHT*FEATURE_HEIGHT; ++i){
//        printf("%d: %f\n", i, output_data_ptr[i]);
//    }

    for(register int i = 0; i < FEATURE_HEIGHT*FEATURE_HEIGHT; i++){
      output_data_ptr[i] = 0.0f;
    }

    float* inter_data_ptr = alloc_aligned_float32_buffer(16, FEATURE_HEIGHT*FEATURE_HEIGHT*9, 2.0f);;

    begin = timestamp_in_milliseconds();
    for(int i = 0; i < FEATURE_HEIGHT; i++){
      for(int j = 0; j < FEATURE_HEIGHT; j++){
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9] = input_data_ptr[i*MATRIX_HEIGHT + j];
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9 + 1] = input_data_ptr[i*MATRIX_HEIGHT + j + 1];
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9 + 2] = input_data_ptr[i*MATRIX_HEIGHT + j + 2];
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9 + 3] = input_data_ptr[(i+1)*MATRIX_HEIGHT + j];
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9 + 4] = input_data_ptr[(i+1)*MATRIX_HEIGHT + j + 1];
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9 + 5] = input_data_ptr[(i+1)*MATRIX_HEIGHT + j + 2];
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9 + 6] = input_data_ptr[(i+2)*MATRIX_HEIGHT + j];
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9 + 7] = input_data_ptr[(i+2)*MATRIX_HEIGHT + j + 1];
        inter_data_ptr[i*FEATURE_HEIGHT*9 + j*9 + 8] = input_data_ptr[(i+2)*MATRIX_HEIGHT + j + 2];        
      }
    }

    long long int middle = timestamp_in_milliseconds();

    for(register int i = 0; i < FEATURE_HEIGHT*FEATURE_HEIGHT; i++){
      output_data_ptr[i] = inter_data_ptr[i*9] * conv_kernel[0];
      output_data_ptr[i] += inter_data_ptr[i*9 + 1] * conv_kernel[1];
      output_data_ptr[i] += inter_data_ptr[i*9 + 2] * conv_kernel[2];
      output_data_ptr[i] += inter_data_ptr[i*9 + 3] * conv_kernel[3];
      output_data_ptr[i] += inter_data_ptr[i*9 + 4] * conv_kernel[4];
      output_data_ptr[i] += inter_data_ptr[i*9 + 5] * conv_kernel[5];
      output_data_ptr[i] += inter_data_ptr[i*9 + 6] * conv_kernel[6];
      output_data_ptr[i] += inter_data_ptr[i*9 + 7] * conv_kernel[7];
      output_data_ptr[i] += inter_data_ptr[i*9 + 8] * conv_kernel[8];
    }
    end = timestamp_in_milliseconds();
    printf("Time spend for im2col operation is: %llu microseconds\n", middle - begin);
    printf("Time spend for gemm convolution operation is: %llu microseconds\n", end - middle);
    printf("Total time is: %llu microseconds\n", end - begin);


//    for(register int i = 0; i < FEATURE_HEIGHT*FEATURE_HEIGHT; ++i){
//        printf("%d: %f\n", i, output_data_ptr[i]);
//    }

    free(input_data_ptr);
    input_data_ptr = NULL;
    free(inter_data_ptr);
    inter_data_ptr = NULL;
*/
    return 0;
}

/*
    // OpenBLAS implementation
    //const enum CBLAS_ORDER Order=CblasRowMajor;
    //const enum CBLAS_TRANSPORSE TransA=CblasNoTrans;
    //const enum CBLAS_TRANSPOSE TransB=CblasNoTrans;
    const int M = 4;
    const int N = 2;
    const int K = 3;
    const float alpha = 1;
    const float beta = 0;
    const int lda = K;
    const int ldb = N;
    const int ldc = N;
    static float A[3 * 4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6};
    static float B[3 * 2] = {5, 4, 3, 2, 1, 0};
    float C[4 * 2];

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            printf("%f ",C[i * N + j]);
        }
        printf("\n");
    }
    */