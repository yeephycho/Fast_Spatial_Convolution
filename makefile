
fastMatrixMultiplication : generate_matrix_data.c profiling.o
#	gcc generate_matrix_data.c -lopenblas -o fastMatrixMultiplication -std=c11 -Ofast
	gcc generate_matrix_data.c profiling.o -o fastMatrixMultiplication -std=c11 -Ofast

profiling.o: profiling.h profiling.c
	gcc -std=c11 -Ofast -c profiling.c
