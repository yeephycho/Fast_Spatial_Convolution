#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#ifdef __APPLE__
  #include <sys/malloc.h>
#elif linux
  #include <malloc.h>
#else
  #include <malloc.h>
#endif // #ifdef macintosh

#include "profiling.h"
#include "Alloc_Mem.h"

#define MATRIX_WIDTH 256
#define MATRIX_HEIGHT 256

#ifdef CBLAS
#include <cblas.h>
#endif

int main(){
// Allocate aligned memory here.
//    void* mem_ptr = malloc(sizeof(float)*256*256 + 15);
//    float* input_data_ptr = (float*)(((uintptr_t)mem_ptr + 15) & ~ (uintptr_t)0x0F);
//    printf("Matrix started at address: %p, this address divides 16 is: %lu\n", input_data_ptr, (size_t)input_data_ptr / 16);
    
//    void* ptr;
//    int rc = posix_memalign(&ptr, 64, sizeof(float)*256*256);
//    printf("Return value of posix_memalign is :%d\n", rc);
//    float* input_data_ptr = ptr;
    int rc;
    float* input_data_ptr = valloc(sizeof(float)*256*256);
//    float* ptr = aligned_alloc(64, sizeof(float)*256*256);
//    free(ptr);
//    void* ptr;
//    int rc = alloc_aligned_mem(ptr, 64, sizeof(float)*256*256);
//    printf("Return value of posix_memalign is :%d\n", rc);
//    float* input_data_ptr = ptr;
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

    // Data initialization here,
    for(register int i = 0; i < 256*256; ++i){
        input_data_ptr[i] = 1.0f;
//        printf("%d: %f\n", i, input_data_ptr[i]);
    }

    float conv_kernel[9] = {3.0f, 3.0f, 3.0f,
                            3.0f, 3.0f, 3.0f,
                            3.0f, 3.0f, 3.0f};

    float output_data_ptr[254*254];

    long long int begin = timestamp_in_nanoseconds();
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
    long long int end = timestamp_in_nanoseconds();

    printf("Time spend for convolution operation is: %llu nanoseconds\n", end - begin);
    
//    for(register int i = 0; i < 254*254; ++i){
//        printf("%d: %f\n", i, output_data_ptr[i]);
//    }
    for(register int i = 0; i < 254*254; i++){
      output_data_ptr[i] = 0.0f;
    }

//    void* mem_inter_ptr = malloc(sizeof(float)*254*254*9 + 15);
//    float* inter_data_ptr = (float*)(((uintptr_t)mem_inter_ptr + 15) & ~ (uintptr_t)0x0F);
//    printf("Matrix started at address: %p, this address divides 16 is: %lu\n", inter_data_ptr, (size_t)inter_data_ptr / 16);    
    
    void* mem_inter_ptr;
    rc = posix_memalign(&mem_inter_ptr, 64, sizeof(float)*254*254*9);
    float* inter_data_ptr = mem_inter_ptr;
    printf("Matrix started at address: %p, this address divides 16 is: %lu\n", inter_data_ptr, (size_t)inter_data_ptr % 16);

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
    printf("Time spend for gemm convolution operation is: %llu microseconds\n", end - begin);

//    for(register int i = 0; i < 254*254; ++i){
//        printf("%d: %f\n", i, output_data_ptr[i]);
//    }

    // Free allocated memory here.
    free(input_data_ptr);
    input_data_ptr = NULL;
//    ptr = NULL;
    free(mem_inter_ptr);
    mem_inter_ptr = NULL;
    inter_data_ptr = NULL;

    return 0;
}
