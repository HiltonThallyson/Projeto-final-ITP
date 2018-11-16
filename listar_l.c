#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include <ctype.h>
#include "funcoes.h"
#include "structs.h"

int valida_chave(char *chave);
int valida_float(char *valor);

int valida_tab(char *nome_tab){
	FILE *bd;
	bd = fopen("BD-ITP","r");
	char string[300];
	char temp[300];
	int tem_coluna = 0;

	fgets(string,300,bd);
	while(fgets(string,300,bd)){
		strcpy(temp,nome_tab);
		strcat(temp,"\n\0");
		//printf("|%d| Tabela |%s|",strcmp(string,temp),string);
		if(strcmp(string,temp)==0){
			tem_coluna++;
		}
	}
	fclose(bd);
	return tem_coluna;	
}

void listar_l(){
	FILE *arquivo;//arquivo original a ser lido;
	variaveis *tipo_var = malloc(sizeof(variaveis));
	char string[300];//string que armazena cada linha do arquivo 1 por vez;
	char opc = 's';//variavel que armazena a opcao de criar um nova linha ou nao;

	while(opc == 's'){
		printf("Selecione a tabela: ");
		tipo_var->nome_t = malloc(sizeof(char)*100);
		scanf("%s",tipo_var->nome_t);
		printf("\n");
		while(valida_tab(tipo_var->nome_t)==0){
			printf("Tabela não existe!! Selecione a tabela: ");
			scanf("%s",tipo_var->nome_t);
		}
		arquivo = fopen(tipo_var->nome_t,"r");
		if (arquivo == NULL){
			printf("Erro na abertura do arquivo!");
			exit(1);
		}else{		
			while (fgets(string,300,arquivo)){
				printf("%s",string);
			}	
		}
		printf("Deseja listar outra tabela? (s/n)\n");
		scanf(" %c", &opc);
	}
	fclose(arquivo);
	free(tipo_var->nome_t);
	free(tipo_var);
}
