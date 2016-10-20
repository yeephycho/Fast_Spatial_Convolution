#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


#include "Time.h"
#include "Mem_Alloc.h"


#ifdef __APPLE__
    #include <sys/malloc.h>
#elif linux
    #include <malloc.h>
#else
    #include <malloc.h>
#endif  // #ifdef __APPLE__ 


#ifdef CBLAS
    #include <cblas.h>
#endif  // #ifdef CBLAS


#define MATRIX_WIDTH 256
#define MATRIX_HEIGHT 256


int main(int argc, char** argv){

    size_t mem_size = MATRIX_HEIGHT * MATRIX_WIDTH;

//  Allocate aligned 32-bit float memory here.
    float* input_data_ptr = alloc_aligned_float32_buffer(64, mem_size, 2.0f);

    float conv_kernel[9] = {3.0f, 3.0f, 3.0f,
                            3.0f, 3.0f, 3.0f,
                            3.0f, 3.0f, 3.0f};

    float output_data_ptr[254*254];

    long long int begin = timestamp_in_milliseconds();
    for(int i = 0; i < 254; i++){
        for(int j = 0; j < 254; j++){
           output_data_ptr[i*254 + j] = input_data_ptr[i*256 + j] * conv_kernel[0];
           output_data_ptr[i*254 + j] += input_data_ptr[i*256 + j + 1] * conv_kernel[1];
           output_data_ptr[i*254 + j] += input_data_ptr[i*256 + j + 2] * conv_kernel[2];
           output_data_ptr[i*254 + j] += input_data_ptr[(i+1)*256 + j] * conv_kernel[3];
           output_data_ptr[i*254 + j] += input_data_ptr[(i+1)*256 + j + 1] * conv_kernel[4];
           output_data_ptr[i*254 + j] += input_data_ptr[(i+1)*256 + j + 2] * conv_kernel[5];
           output_data_ptr[i*254 + j] += input_data_ptr[(i+2)*256 + j] * conv_kernel[6];
           output_data_ptr[i*254 + j] += input_data_ptr[(i+2)*256 + j + 1] * conv_kernel[7];
           output_data_ptr[i*254 + j] += input_data_ptr[(i+2)*256 + j + 2] * conv_kernel[8];
        }
    }
    long long int end = timestamp_in_milliseconds();

    printf("Time spend for convolution operation is: %llu milliseconds\n", end - begin);
    
//    for(register int i = 0; i < 254*254; ++i){
//        printf("%d: %f\n", i, output_data_ptr[i]);
//    }
    for(register int i = 0; i < 254*254; i++){
      output_data_ptr[i] = 0.0f;
    }

//  void* mem_inter_ptr;
//  int rc = posix_memalign(&mem_inter_ptr, 64, sizeof(float)*254*254*9);
    float* inter_data_ptr = alloc_aligned_float32_buffer(64, 254*254*9, 2.0f);;
//  printf("Matrix started at address: %p, this address divides 16 is: %lu\n", inter_data_ptr, (size_t)inter_data_ptr % 16);

    begin = timestamp_in_milliseconds();
    for(int i = 0; i < 254; i++){
      for(int j = 0; j < 254; j++){
        inter_data_ptr[i*254*9 + j*9] = input_data_ptr[i*256 + j];
        inter_data_ptr[i*254*9 + j*9 + 1] = input_data_ptr[i*256 + j + 1];
        inter_data_ptr[i*254*9 + j*9 + 2] = input_data_ptr[i*256 + j + 2];
        inter_data_ptr[i*254*9 + j*9 + 3] = input_data_ptr[(i+1)*256 + j];
        inter_data_ptr[i*254*9 + j*9 + 4] = input_data_ptr[(i+1)*256 + j + 1];
        inter_data_ptr[i*254*9 + j*9 + 5] = input_data_ptr[(i+1)*256 + j + 2];
        inter_data_ptr[i*254*9 + j*9 + 6] = input_data_ptr[(i+2)*256 + j];
        inter_data_ptr[i*254*9 + j*9 + 7] = input_data_ptr[(i+2)*256 + j + 1];
        inter_data_ptr[i*254*9 + j*9 + 8] = input_data_ptr[(i+2)*256 + j + 2];        
      }
    }

    long long int middle = timestamp_in_milliseconds();

    for(register int i = 0; i < 254*254; i++){
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


//    for(register int i = 0; i < 254*254; ++i){
//        printf("%d: %f\n", i, output_data_ptr[i]);
//    }

//  Free allocated memory here.
    free(input_data_ptr);
    input_data_ptr = NULL;
    free(inter_data_ptr);
    inter_data_ptr = NULL;

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
