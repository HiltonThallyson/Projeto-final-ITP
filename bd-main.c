#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void main(){
	int opr = 0, ntabelas = 0;
	char opc = 's';
	printf("----------------------------------SGBD-ITP----------------------------------\n");
	FILE *bd;
	do{
	printf("Selecione a operacao desejada:\n");
	printf("(1) - Criar nova tabela\n(2) - Acrescentar nova linha\n(3) - Acrescentar nova coluna\n(4)- Listar tabelas\n(5) - Sair\n");
	scanf("%d", &opr);
		switch(opr){
			case 1:
				criar_t();
				ntabelas = ntabelas + 1;
				break;
			case 2:
				printf("indisponivel!\n");
				break;
			case 3:
				printf("indisponivel!\n");
				break;
			case 4:
				printf("indisponivel!\n");
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