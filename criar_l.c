#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include <ctype.h>
#include "funcoes.h"
#include "structs.h"

int valida_chave(char *chave){
	int i,n=0;		
	for(i=0;i<strlen(chave);i++){//percorre cada caractere da string chave até ante do \0
		if(isdigit(chave[i])!=0){//se o char for um digito, o contato recebe ele mesmo + 1
			n++;
		}
	}
	if(n==strlen(chave)){//se todos os caracteres forem digitos, a função retorna 1
		return 1;
	}else{//senão retorna 0
		return 0;
	}	
}

void criar_l(){
	FILE *arquivo;
	char opc = 's';
	int r = 0, i = 0;
	int cont = 0, j=0, k=0, t=0;
	char tipos[100][20];
	char string[300];
	variaveis *tipo_var = malloc(sizeof(variaveis));
	tipo_var->chave = malloc(sizeof(char)*100);
	tipo_var->valor_c = malloc(sizeof(char)*100);
	int n=0;

	printf("Selecione a tabela: ");
	tipo_var->nome_t = malloc(sizeof(char)*100);
	scanf("%s",tipo_var->nome_t);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
	printf("\n");
	arquivo = fopen(tipo_var->nome_t,"r");//abre arquivo nome_arquivo para anexar, caso ainda não exista é criado e se existe, o texto
	if (arquivo == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}
	else{
		fseek(arquivo,0,SEEK_SET);
		fscanf(arquivo, "%[^\n]s", string);
		fclose(arquivo);
		for (i; i<strlen(string);i++){
			if(string[i] == '<'){
				j=i+1;
				while (string[j]!='>'){
					tipos[t][k] = string[j];
					k++;
					j++;
				}
				tipos[t][k] = '\0';
				t++;
				k=0;
			}
		}
		arquivo = fopen(tipo_var->nome_t,"a");
		free(tipo_var->nome_t);
	}
	do{	
		i=0;
		do{
			printf("Digite o valor da chave(inteiro): ");
			scanf("%s",tipo_var->chave);
			r = valida_chave(tipo_var->chave);
		}while (r == 0);

		fprintf(arquivo,"|%s|", tipo_var->chave);
		i=1;
		while (i!=t){
			printf("Digite o valor da coluna(%s):",tipos[i]);
			if (strcmp(tipos[i],"int")==0){
				scanf("%d",&tipo_var->valor_i);
				fprintf(arquivo, "%d|",tipo_var->valor_i);
			}else if(strcmp(tipos[i],"float")==0){
				scanf("%f",&tipo_var->valor_f);
				fprintf(arquivo, "%f|",tipo_var->valor_f);
			}else if(strcmp(tipos[i],"double")==0){
				scanf("%lf",&tipo_var->valor_d);
				fprintf(arquivo, "%f|",tipo_var->valor_f);
			}else if(strcmp(tipos[i],"char")==0){
				scanf("%s",tipo_var->valor_c);
				fprintf(arquivo, "%s|",tipo_var->valor_c);
			}
			i++;
		}
		fprintf(arquivo,"\n");
		printf("Deseja adicionar uma nova linha: s-sim n-nao ");
		scanf(" %c",&opc);
	}while(opc != 'n');
	fclose(arquivo);
	free(tipo_var->valor_c);
	free(tipo_var->chave);
	free(tipo_var);
}