#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void main(){
	int opr = 0, ntabelas = 0, desc = 0;
	char opc = 's';
	printf("----------------------------------SGBD-ITP----------------------------------\n");
	FILE *bd;
	FILE *newbd;

	bd = fopen("BD-ITP.txt","a+");
	if (bd == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}

	fseek(bd, 0, SEEK_END); // goto end of file
	if (ftell(bd) == 0){
      	fprintf(bd, "|ntabelas = %d|\n", 0);
 	}
	fseek(bd, 0, SEEK_SET);
		//fprintf(bd, "|ntabelas = %d|\n", 0);
	
	fscanf(bd,"|ntabelas = %d|\n", &ntabelas);
	fclose(bd);
	
	do{
	printf("Selecione a operacao desejada:\n");
	printf("(1) - Criar nova tabela\n(2) - Acrescentar nova linha\n(3) - Acrescentar nova coluna\n(4)- Listar tabelas\n(5) - Sair\n");
	scanf("%d", &opr);
		switch(opr){
			case 1:
				bd = fopen("BD-ITP.txt","a+");
				criar_t(bd);
				ntabelas = ntabelas + 1;
				if (bd == NULL){
					printf("Erro na abertura do arquivo!");
					exit(1);
				}
				newbd = fopen("newbd.txt","w");
				if (newbd == NULL){
					printf("Erro na abertura do arquivo!");
					exit(1);
				}else{
					fprintf(newbd,"|ntabelas = %d|\n", ntabelas);
					char *nome_t = malloc(sizeof(char)*100);
					rewind(bd);
					fscanf(bd, "|ntabelas = %d|", &desc);
					for(int i=0; i < ntabelas; i++){
						fscanf(bd, "%s", nome_t);
						fprintf(newbd, "%s\n", nome_t);
					}
					free(nome_t);
				}
				fclose(newbd);
				fclose(bd);
				remove("BD-ITP.txt");
				rename("newbd.txt","BD-ITP.txt");
				break;
			case 2:
				printf("indisponivel!\n");
				break;
			case 3:
				printf("indisponivel!\n");
				break;
			case 4:
				listar_t();
				break;
			case 5:
				printf("Programa finalizado!\n");
				exit(1);
			default:
				printf("Operacao invalida!\n");
		}
		printf("----------------------------------SGBD-ITP----------------------------------\n");
		printf("Deseja executar outra operacao? (s/n)\n");
		scanf(" %c",&opc);
	}while(opc == 's');
	printf("Programa finalizado!\n");
	exit(1);
}
