#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include <ctype.h>
#include "funcoes.h"
#include "structs.h"

int valida_chave(char *chave);
int valida_float(char *valor);

void editar_t(){
	FILE *arquivo;
	FILE *newfile;
	variaveis *tipo_var = malloc(sizeof(variaveis));
	int r = 0, i = 0, tem_chave = 0;
	int cont = 0, j=0, k=0, t=0, g=0, h=0, u=0;
	char tipos[100][20];
	char nome_colunas[100][50];
	char string[300];
	char *temp;
	char opc = 's';
	tipo_var->chave = malloc(sizeof(char)*100);
	tipo_var->valor_c = malloc(sizeof(char)*100);

	printf("Selecione a tabela: ");
	tipo_var->nome_t = malloc(sizeof(char)*100);
	scanf("%s",tipo_var->nome_t);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
	printf("\n");
	arquivo = fopen(tipo_var->nome_t,"r");//abre arquivo nome_arquivo para anexar, caso ainda não exista é criado e se existe, o texto
	if (arquivo == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}else{
		fscanf(arquivo, "%[^\n]s", string);
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
			}else if(string[i]=='|'){
				j=i+1;
				while(string[j]!='<' && string[j]!='\n'){
					nome_colunas[h][u] = string[j];
					u++;
					j++;
				}
				nome_colunas[h][u] = '\0';
				h++;
				u=0;
			}
		}
	}
	fclose(arquivo);
	while (opc == 's'){
		do{
			printf("Digite o valor da chave(%s):",nome_colunas[0]);
			scanf("%s",tipo_var->chave);
			r = valida_chave(tipo_var->chave);
		}while (r == 0);

		arquivo = fopen(tipo_var->nome_t,"r");
		newfile = fopen("newfile","w");
		while (fgets(string,300,arquivo)){
			g=0;
			temp = malloc(sizeof(char)*50);
			while(string[g+1]!='|'){
				temp[g] = string[g+1];
				g++;
			}
			i=1;				 
			if(strcmp(temp,tipo_var->chave)==0){
				tem_chave = 1;
				fprintf(newfile,"|%s|",temp);
				do{
					printf("Digite o valor da coluna(%s):",nome_colunas[i]);
					if (strcmp(tipos[i],"int")==0){
						do{
							scanf("%s",tipo_var->valor_c);
							r = valida_chave(tipo_var->valor_c);
							if(r==0){
								printf("tipo invalido! Digite o valor da coluna(%s):",nome_colunas[i]);
							}
						}while(r==0);
						fprintf(newfile, "%s|",tipo_var->valor_c);
					}else if(strcmp(tipos[i],"float")==0){
						do{
							scanf("%s",tipo_var->valor_c);
							r = valida_float(tipo_var->valor_c);
							if(r==0){
								printf("tipo invalido! Digite o valor da coluna(%s):",nome_colunas[i]);
							}
						}while(r==0);
						fprintf(newfile, "%s|",tipo_var->valor_c);
					}else if(strcmp(tipos[i],"double")==0){
						do{
							scanf("%s",tipo_var->valor_c);
							r = valida_float(tipo_var->valor_c);
							if(r==0){
								printf("tipo invalido! Digite o valor da coluna(%s):",nome_colunas[i]);
							}
						}while(r==0);
						fprintf(newfile, "%s|",tipo_var->valor_c);
					}else if(strcmp(tipos[i],"char")==0){
						scanf("%s",tipo_var->valor_c);
						fprintf(newfile, "%s|",tipo_var->valor_c);
					}
					i++;
				}while (i!=h-1);
				fprintf(newfile,"\n");
			}else{
				fputs(string,newfile);
			}
			free(temp);
		}
		if(tem_chave==0){
			printf("Chave nao econtrada!\n");
		}
		
		fclose(arquivo);
		fclose(newfile);
		remove(tipo_var->nome_t);
		rename("newfile",tipo_var->nome_t);
		printf("Deseja editar outra linha: s-sim n-nao\n");
		scanf(" %c",&opc);
	}
	free(tipo_var->nome_t);
	free(tipo_var->valor_c);
	free(tipo_var->chave);
	free(tipo_var);
}