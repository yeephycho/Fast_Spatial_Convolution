
fastMatrixMultiplication : generate_matrix_data.c profiling.o #Alloc_Mem.o
#	gcc generate_matrix_data.c -lopenblas -o fastMatrixMultiplication -std=c11 -Ofast
	gcc -std=c11 -Ofast generate_matrix_data.c profiling.o -o fastMatrixMultiplication

profiling.o : profiling.h profiling.c
	gcc -std=c11 -Ofast -c profiling.c

#Alloc_Mem.o : Alloc_Mem.h Alloc_Mem.c
#	gcc -std=c11 -Ofast -c Alloc_Mem.c

.PHONY : exec
exec :
	./fastMatrixMultiplication

.PHONY : clean
clean :
	-rm fastMatrixMultiplication profiling.o
