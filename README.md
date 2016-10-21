# Fast_Spatial_Convolution

## Description
This project serves as a test bench for fast spatial convolution operation. Spatial convolution is at the heart of convolutional neural network, and there's a lot of technics can be used to accelerate the neural network.
So, here I want to compare different implementations' performance for this simple operation.

Currently, the following technics will be introduced in the project:

- Plain old implementation
- BLAS implementation
- With SSE support
- With NEON support on ARM
- With OpenMP support
- With OpenCL support
- With memory alignment


Data type will mainly focus on the 32-bit float number or 16-bit float number, cause these two kinds of data type, as far as I know, are most import to the convolutional neural network.

There are a lot of factors will affect the profiling, this project will only take the calculation time into account, time spend on other necessary part will not be included such as OpenCL create platform or command queue, but memory copy from CPU to GPU will be included when showing the result.

## How To
Open your terminal.
``` bash
cd /to/your/workspace
git clone https://github.com/yeephycho/Fast_Spatial_Convolution.git
cd Fast_Spatial_Convolution/src
make
make exec
make clean
```
