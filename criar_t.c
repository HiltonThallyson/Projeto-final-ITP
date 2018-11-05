#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>//necessaria por causa da funcao isdigit
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include "funcoes.h"

//funcao para verificar se o conteudo recebido para a coluna ID é mesmo um inteiro, sem caracteres entre os digitos 
int valida_chave(char chave[6]){
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

void criar_t(){
	FILE *arquivo;//arquivo utilizado para armazenar tanto as colunas quanto o conteudo de cada coluna
  	FILE *bd;//arquivo utilizado para armazenar o numero total de tabelas criadas no banco e os nomes de cada uma
	char nome_arq[55];//string utilizada na nomeação do arquivo .txt de cada tabela, recebe o nome_t+".txt"
	char nome_t[50];//string que armazena o nome de uma tabela
	char nome_c[50];//string que armazena o nome de uma tabela
	
  	int tipo_c = 0;//tipo do dado escolhido pelo usuario para ser inserido na nova coluna
	char chave[6];//conteudo da coluna ID, tornou-se string pois fizemos a validação a partir da função isdigit
	char opc;//armazena opcao do usuario de adicionar ou não mais uma coluna à tabela
	int valor_i = 0;//variavel que armazenará o conteudo da coluna caso o usuario escolha a coluna do tipo inteiro
	float valor_f = 0;//variavel que armazenará o conteudo da coluna caso o usuario escolha a coluna do tipo float
	double valor_d = 0;///variavel que armazenará o conteudo da coluna caso o usuario escolha a coluna do tipo double
	char valor_c[50];//variavel que armazenará o conteudo da coluna caso o usuario escolha a coluna do tipo string

	printf("---------Criando nova tabela---------\n");
	printf("Digite o nome da tabela: ");
	scanf("%s",nome_t);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
	printf("\n");
	strcpy(nome_arq,nome_t);//nome_arq recebe o nome da nova tabela
	strcat(nome_arq,".txt");//nome_arq recebe ela mesma + string ".txt"
	arquivo = fopen(nome_arq,"a");//abre arquivo nome_arquivo para anexar, caso ainda não exista é criado e se existe, o texto
	//é adicionado ao final do arquivo
	//arquivo = fopen(nome_t,"a");

	if(arquivo == NULL){//caso dê erro na abertura do arquivo, exibe a seguinte mensagem e sai do programa
		printf("Erro na criacao/abertura do arquivo!\n");
		exit(1);
	}else{//caso o arquivo consiga ser aberto com sucesso:
		fprintf(arquivo, "|Tabela - %s|\n", nome_t);//adiciona esta linha no final do arquivo, nome_t inserido pelo usuario
		printf("Criando a primeira coluna: ID\n");
		printf("Digite o valor da primeira coluna: ");
		getchar();
		scanf("%[^\n]s",chave);//armazena o valor da chave, aceita string com espaços
		if(valida_chave(chave)==0){//caso não seja um inteiro, fica no do while até que o usuario digite um inteiro valido
			do{
				printf("Digite o valor INTEIRO da primeira coluna: ");
				getchar();
				scanf("%[^\n]s",chave);
			}while(valida_chave(chave)==0);
		}
		fprintf(arquivo, "|ID = %s|",chave);//o conteudo de chave é anexado ao arquivo nome_t.txt

		printf("Deseja acrescentar uma nova coluna: (s/n)\n");
		scanf(" %c", &opc);//armazena opção do usuario de adicionar ou não mais uma coluna
		while(opc == 's'){
			printf("Digite o nome da coluna(sem espaços): ");
			scanf("%s",nome_c);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
			printf("\n");
			printf("Qual o tipo de dado a ser inserido na coluna:\n");
			printf("(1) - int\n(2) - float\n(3) - double\n(4) - char\n");
			scanf("%d", &tipo_c);//usuario insere um dos inteiros indicados acima que corresponde a um dos 4 tipos primarios
			printf("\n");
			printf("Digite o valor a ser inserido na coluna: ");
			switch(tipo_c){//usuario insere o conteudo da coluna
				case 1://se o tipo escolhido pelo usuário tiver sido 1-inteiro
					scanf("%d", &valor_i);//atribui o valor inserido pelo usuario a uma variavel do tipo inteiro
					fprintf(arquivo,"%s = %d|", nome_c, valor_i);//o nome da coluna = o conteudo| é anexado ao arquivo nome_t.txt
					break;
				case 2://se o tipo escolhido pelo usuário tiver sido 2-float
					scanf("%f", &valor_f);//atribui o valor inserido pelo usuario a uma variavel do tipo float
					fprintf(arquivo,"%s = %f|", nome_c, valor_f);//o nome da coluna = o conteudo| é anexado ao arquivo nome_t.txt
					break;
				case 3://se o tipo escolhido pelo usuário tiver sido 3-double
					scanf("%lf", &valor_d);//atribui o valor inserido pelo usuario a uma variavel do tipo float
					fprintf(arquivo,"%s = %lf|", nome_c, valor_d);//o nome da coluna = o conteudo| é anexado ao arquivo nome_t.txt
					break;
				case 4://se o tipo escolhido pelo usuário tiver sido 4-char
					getchar();
					scanf("%[^\n]s", valor_c);//armazena o valor da chave, aceita string com espaços
					fprintf(arquivo,"%s = %s|", nome_c, valor_c);//o nome da coluna = o conteudo| é anexado ao arquivo nome_t.txt
					break;
			}
			printf("Deseja acrescentar uma nova coluna: (s/n)\n");//pergunta novmente ao usuário se ele deseja adicionar outra coluna
			scanf(" %c", &opc);//se 's' então voltamos ao inicio do while, se 'n' o programa prossegue para o próximo comando
		}
    		bd = fopen("BD-ITP.txt", "a");//abre arquivo nome_arquivo para anexar, caso ainda não exista é criado e se existe, o texto
	//é adicionado ao final do arquivo
		fprintf(bd, "|%s|\n", nome_t);//adiciona esta linha no final do arquivo (bd), nome_t
	}
  	fclose(bd);//fecha arquivo bd
	fclose(arquivo);//fechar arquivo arquivo
}

