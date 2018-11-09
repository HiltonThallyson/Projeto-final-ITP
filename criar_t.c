#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include "funcoes.h"
#include "structs.h"

void criar_t(){
	FILE *arquivo;//arquivo utilizado para armazenar tanto as colunas quanto o conteudo de cada coluna
  	FILE *bd;//arquivo utilizado para armazenar o numero total de tabelas criadas no banco e os nomes de cada uma
	variaveis *tipo_var = malloc(sizeof(variaveis));
	char opc;//armazena opcao do usuario de adicionar ou não mais uma coluna à tabela
	char *tipo_c;

	printf("---------Criando nova tabela---------\n");
	printf("Digite o nome da tabela: ");
	tipo_var->nome_t = malloc(sizeof(char)*100);
	scanf("%s",tipo_var->nome_t);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
	printf("\n");
	arquivo = fopen(tipo_var->nome_t,"a");//abre arquivo nome_arquivo para anexar, caso ainda não exista é criado e se existe, o texto
	//é adicionado ao final do arquivo
	bd = fopen("BD-ITP", "a");//abre arquivo nome_arquivo para anexar, caso ainda não exista é criado e se existe, o texto
	//é adicionado ao final do arquivo
	fprintf(bd, "|%s|\n", tipo_var->nome_t);//adiciona esta linha no final do arquivo (bd), nome_t
	fclose(bd);//fecha arquivo bd
	free(tipo_var->nome_t);

	if(arquivo == NULL){//caso dê erro na abertura do arquivo, exibe a seguinte mensagem e sai do programa
		printf("Erro na criacao/abertura do arquivo!\n");
		exit(1);
	}else{//caso o arquivo consiga ser aberto com sucesso:
		printf("Digite o nome da coluna para chave primaria(sem espaços): ");
		tipo_var->nome_c = malloc(sizeof(char)*100);
		scanf("%s",tipo_var->nome_c);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
		printf("\n");
		fprintf(arquivo,"|%s <unsigned int>|",tipo_var->nome_c);
		printf("Deseja acrescentar uma nova coluna: (s/n)\n");
		scanf(" %c", &opc);//armazena opção do usuario de adicionar ou não mais uma coluna
		while(opc == 's'){
			tipo_c = malloc(sizeof(char)*20);
			printf("Digite o nome da coluna(sem espaços): ");
			scanf("%s",tipo_var->nome_c);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
			printf("\n");
			printf("Qual o tipo de dado a ser inserido na coluna:\n");
			printf("int\nfloat\ndouble\nchar\n");
			getchar();
			scanf("%s", tipo_c);//usuario insere um dos inteiros indicados acima que corresponde a um dos 4 tipos primarios
			printf("\n");
			fprintf(arquivo,"%s <%s>|", tipo_var->nome_c, tipo_c);	
			free(tipo_c);	
			printf("Deseja acrescentar uma nova coluna: (s/n)\n");//pergunta novmente ao usuário se ele deseja adicionar outra coluna
			scanf(" %c", &opc);//se 's' então voltamos ao inicio do while, se 'n' o programa prossegue para o próximo comando
		}
		fprintf(arquivo,"\n");
	}
	free(tipo_var->nome_c);
	free(tipo_var);
	fclose(arquivo);//fechar arquivo arquivo
}

