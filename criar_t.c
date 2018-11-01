#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void criar_t(){
	FILE *arquivo;
	FILE *bd;
	char nome_t[50];
	char nome_c[50];
	int tipo_c = 0;
	int chave;
	char opc;
	int valor_i = 0;
	float valor_f = 0;
	double valor_d = 0;
	char valor_c[50];

	printf("---------Criando nova tabela---------\n");
	printf("Digite o nome da tabela: ");
	scanf("%s",nome_t);
	printf("\n");
	arquivo = fopen(nome_t,"a");

	if(arquivo == NULL){
		printf("Erro na criacao/abertura do arquivo!\n");
		exit(1);
	}else{
		fprintf(arquivo, "|Tabela - %s|\n", nome_t);
		printf("Criando a primeira coluna: ID\n");
		printf("Digite o valor da primeira coluna: ");
		scanf("%d",&chave);
		fprintf(arquivo, "|ID = %d|",chave);

		printf("Deseja acrescentar uma nova coluna: (s/n)\n");
		scanf(" %c", &opc);
		while(opc == 's'){
			printf("Digite o nome da coluna: ");
			scanf("%s",nome_c);
			printf("\n");
			printf("Qual o tipo de dado a ser inserido na coluna:\n");
			printf("(1) - int\n(2) - float\n(3) - double\n(4) - char\n");
			scanf("%d", &tipo_c);
			printf("\n");
			printf("Digite o valor a ser inserido na coluna: ");
			switch(tipo_c){
				case 1:
					scanf("%d", &valor_i);
					fprintf(arquivo,"%s = %d|", nome_c, valor_i);
					break;
				case 2:
					scanf("%f", &valor_f);
					fprintf(arquivo,"%s = %f|", nome_c, valor_f);
					break;
				case 3:
					scanf("%lf", &valor_d);
					fprintf(arquivo,"%s = %lf|", nome_c, valor_d);
					break;
				case 4:
					scanf(" %s", valor_c);
					fprintf(arquivo,"%s = %s|", nome_c, valor_c);
					break;
			}
			printf("Deseja acrescentar uma nova coluna: (s/n)\n");
			scanf(" %c", &opc);
		}
		bd = fopen("BD ITP.txt","a");
		fprintf(bd, "|%s|\n", nome_t);
	}
	fclose(arquivo);
	fclose(bd);
}