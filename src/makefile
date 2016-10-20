
fastMatrixMultiplication : Main.c Time.o Mem_Alloc.o
#	gcc generate_matrix_data.c -lopenblas -o fastMatrixMultiplication -std=c11 -Ofast
	gcc -std=c11 -Ofast Main.c Time.o Mem_Alloc.o -o fastMatrixMultiplication


Time.o : Time.h Time.c
	gcc -std=c11 -Ofast -c Time.c


Alloc_Mem.o : Mem_Alloc.h Mem_Alloc.c
	gcc -std=c11 -Ofast -c Mem_Alloc.c


.PHONY : exec
exec :
	./fastMatrixMultiplication


.PHONY : clean
clean :
	-rm fastMatrixMultiplication Time.o Mem_Alloc.o
