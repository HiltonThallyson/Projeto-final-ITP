#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

void listar_t(FILE *bd){
	int ntabelas = 0;
	char nome_t[50];
	printf("-------------------Lista de tabelas------------------------\n");
	fscanf(bd, "|ntabelas = %d|\n", &ntabelas);
	printf("ntabelas = %d\n", ntabelas);
	for(int i = 0; i < ntabelas; i++){
		fscanf(bd, "%s\n", nome_t);
		printf("%s\n", nome_t);
	}
}

