#include <stdio.h>
#include <stdlib.h>

#include "Mem_Alloc.h"
#include "Global_Setting.h"
#include "Time.h"

#include <OpenCL/opencl.h>


#define FILENAME "./Spatial_Convolution.cl"


int main(int argc, char** argv){   
    int err;


    cl_device_id device_id;
    int gpu = 0;
    err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, 
    	&device_id, NULL);
    if(err != CL_SUCCESS){
    	printf("Cannot get device ID!\n");
    }


    cl_context context;
    context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
    if(err != CL_SUCCESS){
    	printf("Cannot create context!\n");
    }


    cl_command_queue queue;
    queue = clCreateCommandQueue(context, device_id, 0, &err);
    if(err != CL_SUCCESS){
    	printf("Cannot create command queue!\n");
    }


    cl_program program;
    FILE *program_handle;
    size_t program_size;
    char* program_buffer, *program_log;
    program_handle = fopen(FILENAME, "r");
    if(program_handle == NULL){
    	printf("Cannot find the program file!\n");
    }
    fseek(program_handle, 0, SEEK_END);
    program_size = ftell(program_handle);
    rewind(program_handle);
    program_buffer = (char*)malloc(program_size + 1);
    program_buffer[program_size] = '\0';
    fread(program_buffer, sizeof(char), program_size, program_handle);
    fclose(program_handle);
    program = clCreateProgramWithSource(context, 1, (const char **) &program_buffer, NULL, &err);
    if(err != CL_SUCCESS){
    	printf("Cannot create program!\n");
    }
    free(program_buffer);


    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
   	size_t log_size;
    if(err != CL_SUCCESS){
		/* Find size of log and print to std output */
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
			0, NULL, &log_size);
		program_log = (char*)malloc(log_size + 1);
		program_log[log_size] = '\0';
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
			log_size + 1, program_log, NULL);
		printf("%s\n", program_log);
		free(program_log);
    }


    cl_kernel kernel;
    kernel = clCreateKernel(program, "cl_spatial_convolution", &err);
    if(err != CL_SUCCESS){
    	printf("Cannot create kernel with err code %d!\n", err);
    }


    size_t matrix_buffer_size = MATRIX_HEIGHT * MATRIX_WIDTH * MATRIX_CHANNEL;
    float* input_data_ptr = alloc_aligned_float32_buffer(64, matrix_buffer_size, 1.0f);

    size_t kernel_buffer_size = KERNEL_HEIGHT * KERNEL_WIDTH * KERNEL_CHANNEL;
    float* kernel_data_ptr = alloc_aligned_float32_buffer(64, kernel_buffer_size, 1.0f);

    size_t feature_buffer_size = FEATURE_HEIGHT * FEATURE_WIDTH * FEATURE_CHANNEL;
    float* feature_data_ptr = alloc_aligned_float32_buffer(64, feature_buffer_size, 0.0f);


    long long int begin = timestamp_in_milliseconds();


    cl_mem input, conv_kernel, output;
    input = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(float) * matrix_buffer_size, input_data_ptr, &err);
    conv_kernel = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(float) * kernel_buffer_size, kernel_data_ptr, &err);
    output = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(float) * feature_buffer_size, feature_data_ptr, &err);
    if(err != CL_SUCCESS){
    	printf("Cannot create buffer!\n");
    }


    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &conv_kernel);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &output);
    if(err != CL_SUCCESS){
    	printf("Cannot set kernel arguments with error code %d!\n", err);
    }


    size_t global_size[] = {MATRIX_WIDTH, MATRIX_HEIGHT};
    err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, NULL, 0, NULL, NULL);
    if(err != CL_SUCCESS){
    	printf("Cannot enqueue kernel with error code %d!\n", err);
    }


    err = clEnqueueReadBuffer(queue, output, CL_TRUE, 0, feature_buffer_size * sizeof(float), feature_data_ptr, 0 ,NULL, NULL);
    if(err != CL_SUCCESS){
    	printf("Cannot read output buffer with error code %d!\n", err);
    }


    long long int end = timestamp_in_milliseconds();
    printf("Time spend for aligned opencl convolution operation is: %llu milliseconds\n", end - begin);


    for(int i = 0; i < FEATURE_WIDTH * FEATURE_HEIGHT; ++i){
    	if(feature_data_ptr[i] != 9.0f){
    		printf("%f\n", feature_data_ptr[i]);
    	}
    }


	clReleaseMemObject(input);
	clReleaseMemObject(conv_kernel);
	clReleaseMemObject(output);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);


    free(input_data_ptr);
    free(kernel_data_ptr);
    free(feature_data_ptr);


    return 0;
}
