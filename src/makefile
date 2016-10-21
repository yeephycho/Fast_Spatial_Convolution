
fastMatrixMultiplication : Main.c Time.o Mem_Alloc.o Spatial_Convolution.o
	gcc -std=c11 -Ofast Main.c Time.o Mem_Alloc.o Spatial_Convolution.o -o fastMatrixMultiplication
#	gcc generate_matrix_data.c -lopenblas -o fastMatrixMultiplication -std=c11 -Ofast


Time.o : Time.h Time.c
	gcc -std=c11 -Ofast -c Time.c


Alloc_Mem.o : Mem_Alloc.h Mem_Alloc.c
	gcc -std=c11 -Ofast -c Mem_Alloc.c


Spatial_Convolution.o : Spatial_Convolution.h Spatial_Convolution.c
	gcc -std=c11 -Ofast -c Spatial_Convolution.c


.PHONY : exec
exec :
	./fastMatrixMultiplication


.PHONY : clean
clean :
	-rm fastMatrixMultiplication Time.o Mem_Alloc.o Spatial_Convolution.o
