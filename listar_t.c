#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


void listar_t(){
	FILE *bd;
	char *nome_t = malloc(sizeof(char)*100);//aloca espaço para uma string de tamanho 100.
	int ntabelas;//variável para armazenar o n de tabelas.

	bd = fopen("BD-ITP", "r");//abre o arquivo BD-ITP.txt em modo leitura.
	//checa se o arqivo foi aberto corretamente:
	if (bd == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}else{
		rewind(bd);//coloca o cursor na posição inicial do arquivo
		fscanf(bd, "|ntabelas = %d|", &ntabelas);//lê o valor de ntabelas do arquivo bd.
		printf("-----TABELAS do banco BD-----\n");
		//faz um loop para ler o nome das tabelas linha por linha e mostrar na tela.
		for(int i=0; i < ntabelas; i++){
			fscanf(bd, "%s", nome_t);
			printf("%s\n", nome_t);
		}
		free(nome_t);//desaloca nome_t.
	}
	fclose(bd);//fecha o arquivo em bd.
}
