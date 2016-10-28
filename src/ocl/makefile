CFLAGS = -std=c11 -Ofast

oclFastSpatialConvolution : cl_main.c Time.o Mem_Alloc.o Global_Setting.h
	gcc $(CFLAGS) -framework OpenCL cl_main.c Mem_Alloc.c Time.c -o oclFastSpatialConvolution
#	gcc generate_matrix_data.c -lopenblas -o fastMatrixMultiplication -std=c11 -Ofast


Time.o : Time.h Time.c
	gcc $(CFLAGS) -c Time.c


Alloc_Mem.o : Mem_Alloc.h Mem_Alloc.c
	gcc $(CFLAGS) -c Mem_Alloc.c


.PHONY : exec
exec :
	./oclFastSpatialConvolution


.PHONY : clean
clean :
	-rm oclFastSpatialConvolution Time.o Mem_Alloc.o
