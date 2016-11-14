SET(SRC_LIST Main.c Time.c Spatial_Convolution.c Mem_Alloc.c)
SET(GCC_COVERAGE_COMPILE_FLAGS "-fexceptions -std=c11 -Ofast -Wall" )
ADD_DEFINITIONS(${GCC_COVERAGE_COMPILE_FLAGS})
ADD_EXECUTABLE(fastSpatialConvolution ${SRC_LIST})
