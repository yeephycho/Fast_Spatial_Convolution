#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <sys/time.h>

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    unsigned long time_in_micros = 1000000 * te.tv_sec + te.tv_usec; // caculate microseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return time_in_micros;
}

int main(){
    // Allocate aligned memory here.
    void* mem_ptr = malloc(sizeof(float)*256*256 + 15);
    float* input_data_ptr = ((uintptr_t)mem_ptr + 15) & ~ (uintptr_t)0x0F;
    printf("Matrix started at address: %p, this address divides 16 is: %lu\n", input_data_ptr, (size_t)input_data_ptr / 16);

    // Data initialization here,
    for(register int i = 0; i < 256*256; ++i){
        input_data_ptr[i] = 1.0f;
    //    printf("%d: %f\n", i, input_data_ptr[i]);
    }

    float conv_kernel[9] = {3.0f, 3.0f, 3.0f,
                            3.0f, 3.0f, 3.0f,
                            3.0f, 3.0f, 3.0f};

    float output_data_ptr[254*254];


    long long int begin = current_timestamp();
    // f_mm_c(input_data_ptr, conv_kernel, output_data_ptr);
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
    long long int end = current_timestamp();

    printf("Time spend for convolution operation is: %llu microseconds\n", end - begin);
    
//    for(register int i = 0; i < 254*254; ++i){
//        printf("%d: %f\n", i, output_data_ptr[i]);
//    }


    // Free allocated memory here.
    free(mem_ptr);
    mem_ptr = NULL;

    return 0;
}
