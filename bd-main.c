#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void main(){
	int opr = 0, ntabelas = 0, desc = 0;// opr = operação a ser realizada, desc = variável temporária para pular linha no bd
	char opc = 's';//opc - opção de continuar executando novos comandos ou não.
	printf("----------------------------------SGBD-ITP----------------------------------\n");
	FILE *bd;
	FILE *newbd; // arquivo que vai receber a atualização de bd.
	//abertura do arquivo que recebe todas as tabelas.
	bd = fopen("BD-ITP.txt","a+");
	if (bd == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}
	
	//verifica se o arquivo bd está vazio ou não.
  	fseek(bd, 0, SEEK_END); //coloca o cursor no final do arquivo.
	//se a posição do final for igual a posição inicial, cria a primeira linha do bd.
	if (ftell(bd) == 0){
      		fprintf(bd, "|ntabelas = %d|\n", 0);// cria a primeira linha do bd com valor do n de tabelas = 0;
 	}
	
	fseek(bd, 0, SEEK_SET);	//coloca o cursor na posição inicial do arquivo bd.	
	
	fscanf(bd,"|ntabelas = %d|\n", &ntabelas);//lê o numero de tabelas existentes.
	fclose(bd);
	//faz um loop enquanto o usuário quiser executar operações.
	do{
		printf("Selecione a operacao desejada:\n");
		printf("(1) - Criar nova tabela\n(2) - Acrescentar nova linha\n(3) - Acrescentar nova coluna\n(4)- Listar tabelas\n(5) - Sair\n");
		scanf("%d", &opr);
			switch(opr){//checa qual operação foi escolhida.
				case 1:
					criar_t();//chama a função de criar tabela.
					ntabelas = ntabelas + 1;//incrementa o número de tabelas.
					newbd = fopen("newbd.txt","w");//abre newbd como escrita
					bd = fopen("BD-ITP.txt", "r");//abre bd como leitura
					//checa se o arquivo de newbd foi aberto corretamente.
					if (newbd == NULL){
						printf("Erro na abertura do arquivo!");
						exit(1);
					}else{
						fprintf(newbd,"|ntabelas = %d|\n", ntabelas);//acrescenta a primeira linha de bd = n de tabelas atualizado.
						char *nome_t = malloc(sizeof(char)*100);//aloca espaço para uma string de tamanho 100 para receber o nome da tabela criada.
						rewind(bd);//coloca o cursos na posição inicial do arquivo bd.
						fscanf(bd, "|ntabelas = %d|", &desc);//lê o ntabelas, para pular uma linha.
						//loop para ler as tabelas dentro do arquivo bd e copiar no arquivo newbd.
						for(int i=0; i < ntabelas; i++){
							fscanf(bd, "%s", nome_t);
							fprintf(newbd, "%s\n", nome_t);
						}
						free(nome_t);//desaloca espaço da variável nome_t.
					}
					fclose(newbd);//fecha newbd
					fclose(bd);//fecha bd
					remove("BD-ITP.txt");//remove o arquivo em bd.
					rename("newbd.txt","BD-ITP.txt");//muda o nome de newbd.txt para BD-ITP, tomando o lugar do arquivo bd original.
					break;
				case 2:
					printf("indisponivel!\n");
					break;
				case 3:
					printf("indisponivel!\n");
					break;
				case 4:
					listar_t();// chama a função de listar as tabelas do banco de dados.
					break;
				case 5:
					printf("Programa finalizado!\n");//sai do programa com exit(1).
					exit(1);
				default:
					printf("Operacao invalida!\n");
			}
		printf("----------------------------------SGBD-ITP----------------------------------\n");
		//checa se o usuário quer continuar com as operações.
		printf("Deseja executar outra operacao? (s/n)\n");
		scanf(" %c",&opc);
	}while(opc == 's');
	
	printf("Programa finalizado!\n");
	exit(1);
}
