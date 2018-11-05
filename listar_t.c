#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


void listar_t(){
	FILE *bd;
	char *nome_t = malloc(sizeof(char)*100);
	int ntabelas;

	bd = fopen("BD-ITP.txt", "r");
	if (bd == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}else{
		rewind(bd);
		fscanf(bd, "|ntabelas = %d|", &ntabelas);
		printf("-----TABELAS do banco BD-----\n");
		for(int i=0; i < ntabelas; i++){
			fscanf(bd, "%s", nome_t);
			printf("%s\n", nome_t);
		}
		free(nome_t);
	}
	fclose(bd);
}