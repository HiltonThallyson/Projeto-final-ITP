#include <stdio.h>
#include <stdlib.h>

void main(){
	int opr = 0;
	char opc = 's';
	printf("----------------------------------SGBD-ITP----------------------------------\n");
	do{
	printf("Selecione a operacao desejada:\n");
	printf("(1) - Criar nova tabela\n(2) - Acrescentar nova linha\n(3) - Acrescentar nova coluna\n(4)- Listar tabelas\n(5) - Sair\n");
	scanf("%d", &opr);
		switch(opr){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				printf("Programa finalizado!\n");
				exit(1);
			default:
				printf("Operacao invalida!\n");
		}	
		printf("Deseja executar outra operacao? (s/n)\n");
		scanf(" %c",&opc);
	}while(opc == 's');
	printf("Programa finalizado!\n");
	exit(1);
}