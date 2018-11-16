#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include "funcoes.h"
#include "structs.h"

int valida_tab(char *nome_tab);

void criar_c(){
	FILE *arquivo;
	FILE *newfile;
	char string[300];//string que armazena cada linha do arquivo 1 por vez;
	char *temp;//string que recebe o valor da chave primaria;
	char *tipo_c;
	char opc = 's';
	int n_de_colunas = 0, tem_coluna = 0;
	variaveis *tipo_var = malloc(sizeof(variaveis));
	tipo_var->valor_c = malloc(sizeof(char)*100);

	//recebe o nome da tabela e abre o arquivo desejado;
	printf("Selecione a tabela: ");
	tipo_var->nome_t = malloc(sizeof(char)*100);
	scanf("%s",tipo_var->nome_t);
	printf("\n");
	
	while(valida_tab(tipo_var->nome_t)==0){
		printf("Tabela não existe!! Selecione a tabela: ");
		scanf("%s",tipo_var->nome_t);	
	}
	
	newfile = fopen("newfile","a+");
	if (newfile == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}

	arquivo = fopen(tipo_var->nome_t,"r");
	if (arquivo == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}else{
		fgets(string,300,arquivo);
		string[strlen(string)-1] = '\0';
		fputs(string,newfile);
		fclose(newfile);
		while(opc == 's'){
			newfile = fopen("newfile","a+");
			if (newfile == NULL){
				printf("Erro na abertura do arquivo!");
				exit(1);
			}
			tipo_var->nome_c = malloc(sizeof(char)*100);
			printf("Digite o nome da coluna(sem espaços): ");
			scanf("%s",tipo_var->nome_c);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
			printf("\n");
			if(strstr(string,tipo_var->nome_c)!= NULL){
				printf("Coluna ja existe!!\n");
				tem_coluna = 1;
			}else{
				tem_coluna = 0;
			}
			tipo_c = malloc(sizeof(char)*20);
			if(tem_coluna == 0){
				printf("Qual o tipo de dado a ser inserido na coluna:\n");
				printf("int\nfloat\ndouble\nchar\n");
				getchar();
				scanf("%s", tipo_c);//usuario insere um dos inteiros indicados acima que corresponde a um dos 4 tipos primarios
				printf("\n");
				fprintf(newfile,"%s<%s>|", tipo_var->nome_c, tipo_c);	
				n_de_colunas++;	
				fclose(newfile);
				newfile = fopen("newfile", "r");
				if (newfile == NULL){
					printf("Erro na abertura do arquivo!");
					exit(1);
				}
				fgets(string,300,newfile);
				fclose(newfile);
				printf("Deseja acrescentar uma nova coluna: (s/n)\n");//pergunta novmente ao usuário se ele deseja adicionar outra coluna
				scanf(" %c", &opc);//se 's' então voltamos ao inicio do while, se 'n' o programa prossegue para o próximo comando	
			}else{
				opc = 's';
			}
			free(tipo_var->nome_c);
			free(tipo_c);
		}
		newfile = fopen("newfile","a+");
		if (newfile == NULL){
			printf("Erro na abertura do arquivo!");
			exit(1);
		}
		fprintf(newfile,"\n");
		fclose(newfile);
		newfile = fopen("newfile","a+");
		while(fgets(string,300,arquivo)){
			string[strlen(string)-1] = '\0';
			fputs(string,newfile);
			for(int i=0; i<n_de_colunas;i++){
				fprintf(newfile,"%s|", "-");
			}
			fprintf(newfile,"\n");
		}
		fclose(newfile);
		fclose(arquivo);
		remove(tipo_var->nome_c);
		rename("newfile",tipo_var->nome_t);
		free(tipo_var->nome_t);
		free(tipo_var);
	}

}
