#include <stdio.h>
#include <stdlib.h>


typedef struct grupo_var{
	char *nome_t;
	char *nome_c;
	int valor_i;
	float valor_f;
	double valor_d;
	char *valor_c;
	char *chave;
}variaveis;

typedef struct tipos_valores_t{
	int *valores_int;
	float *valores_float;
	double *valores_double;
}tipos_valores;


