# Fast_Spatial_Convolution

## Description
This project serves as a test bench for fast spatial convolution operation. Spatial convolution is at the heart of convolutional neural network, and there's a lot of technics can be used to accelerate the neural network.
So, here I want to compare different implementations' performance for this simple operation.

Currently, the following technics will be introduced in the project:

- Plain old implementation
- BLAS implementation
- With SSE support
- With OpenMP support
- With OpenCL support
- With memory alignment
