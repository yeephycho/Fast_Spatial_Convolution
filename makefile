fastMatrixMultiplication : generate_matrix_data.c
	gcc generate_matrix_data.c -lopenblas -o fastMatrixMultiplication -std=c11 -Ofast

