#define MATRIX_WIDTH 1024
#define MATRIX_HEIGHT 1024

#define KERNEL_WIDTH 3
#define KERNEL_HEIGHT 3

#define FEATURE_WIDTH (MATRIX_WIDTH - KERNEL_WIDTH + 1)
#define	FEATURE_HEIGHT (MATRIX_HEIGHT - KERNEL_HEIGHT + 1)

__kernel void cl_spatial_convolution(
    __global float *input_data, 
    __global float *kernel_data, 
    __global float *output_data) {
	
	int col_idx = get_global_id(0);
	int row_idx = get_global_id(1);
	
	if (col_idx<FEATURE_WIDTH && row_idx<FEATURE_HEIGHT) {
		size_t output_offset = mad24(row_idx, FEATURE_WIDTH, col_idx);

		output_data[output_offset] = input_data[mad24(row_idx, MATRIX_WIDTH, (col_idx))] * kernel_data[0];
		output_data[output_offset] += input_data[mad24(row_idx, MATRIX_WIDTH, (col_idx + 1))] * kernel_data[1];
		output_data[output_offset] += input_data[mad24(row_idx, MATRIX_WIDTH, (col_idx + 2))] * kernel_data[2];

		output_data[output_offset] += input_data[mad24((row_idx+1), MATRIX_WIDTH, (col_idx))] * kernel_data[3];
		output_data[output_offset] += input_data[mad24((row_idx + 1), MATRIX_WIDTH, (col_idx + 1))] * kernel_data[4];
		output_data[output_offset] += input_data[mad24((row_idx + 1), MATRIX_WIDTH, (col_idx + 2))] * kernel_data[5];

		output_data[output_offset] += input_data[mad24((row_idx + 2), MATRIX_WIDTH, (col_idx))] * kernel_data[6];
		output_data[output_offset] += input_data[mad24((row_idx + 2), MATRIX_WIDTH, (col_idx + 1))] * kernel_data[7];
		output_data[output_offset] += input_data[mad24((row_idx + 2), MATRIX_WIDTH, (col_idx + 2))] * kernel_data[8];
	}
}
