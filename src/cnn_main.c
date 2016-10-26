#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "Time.h"
#include "Mem_Alloc.h"
#include "Spatial_Convolution.h"
#include "Global_Setting.h"

int main(int argc, char** argv){
	
	float input_image[28 * 28] = [0.1f,];
	float conv_kernel_layer1[32][3 * 3] = [0.0f,];
	float bias_layer1[32] = [0.0f, ];
	float feature_map_layer1[32][26 * 26] = [0.0f,];
	float output_layer1[32][13 * 13] = [0.0f,];

	int rt = spatial_convolution_float32(input_image, conv_kernel_layer1, feature_map_layer1);
	int rt = add_bias(feature_map_layer1, bias_layer1);
	int rt = relu(feature_map_layer1);
	int rt = max_pool(feature_map_layer1, output_layer1);

	float conv_kernel_layer2[64][3 * 3 * 32] = [0.0f,];
	float bias_layer2[64] = [0.0f,];
	float feature_map_layer2[64][11 * 11] = [0.0f,];
	float output_layer2[64][6 * 6] = [0.0f,];

	int rt = spatial_convolution_float32(output_layer1, conv_kernel_layer2, feature_map_layer2);
	int rt = add_bias(feature_map_layer2, bias_layer2);
	int rt = relu(feature_map_layer2);
	int rt = max_pool(feature_map_layer2, output_layer2);

	float conv_kernel_layer3[32][3 * 3 * 64] = [0.0f, ];
	float bias_layer3[32] = [0.0f, ];
	float feature_map_layer3[32][4 * 4] = [0.0f, ];
	float output_layer3[32][2 * 2] = [0.0f, ];

	int rt = spatial_convolution_float32(output_layer2, conv_kernel_layer3, feature_map_layer3);
	int rt = add_bias(feature_map_layer3, bias_layer3);
	int rt = relu(feature_map_layer3);
	int rt = max_pool(feature_map_layer3, output_layer3);

	float output[10] = [0.0f, ];
	int rt = fully_connected_layer(output_layer3, output);

	for(int i = 0; i < 10; i++){
		printf("Predicted result is: %d: %f\n", i, output[i]);
	}

	return 0;
}