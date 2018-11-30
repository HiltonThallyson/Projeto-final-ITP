#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include "funcoes.h"
#include "structs.h"

void listar_t();

void criar_t(){
	FILE *arquivo;//arquivo utilizado para armazenar tanto as colunas quanto o conteudo de cada coluna
  	FILE *bd;//arquivo utilizado para armazenar o numero total de tabelas criadas no banco e os nomes de cada uma
	variaveis *tipo_var = malloc(sizeof(variaveis));
	char opc;//armazena opcao do usuario de adicionar ou não mais uma coluna à tabela
	char *tipo_c;
	int tem_coluna=0;
	char string[50];
	char colunas[300];
	char str[50];
	char *temp;
	char repete = 's';

	printf("-------------Criando nova tabela------------\n");
	while(repete == 's'){
		listar_t();
		printf("\n");
		printf("Digite o nome da tabela:\t");
		tipo_var->nome_t = malloc(sizeof(char)*100);
		scanf("%s",tipo_var->nome_t);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
		printf("\n");
		//é adicionado ao final do arquivo
		bd = fopen("BD-ITP", "r");//abre arquivo nome_arquivo para anexar, caso ainda não exista é criado e se existe, o texto
		//é adicionado ao final do arquivo

		while (fgets(string,50,bd)){
			temp = malloc(sizeof(char)*50);
			for(int i=0; i<strlen(string)-1;i++){
				temp[i] = string[i];
			}
			
			if(strcmp(tipo_var->nome_t, temp)==0){
				printf("Nome da tabela já existe no banco de dados!\n\n");
				repete = 's';
				break;
			}else{
				repete = 'n';
			}
			free(temp);
		}
		fclose(bd);
		
	}

	bd = fopen("BD-ITP", "a");
	fprintf(bd, "%s\n", tipo_var->nome_t);//adiciona esta linha no final do arquivo (bd), nome_t
	fclose(bd);//fecha arquivo bd
	arquivo = fopen(tipo_var->nome_t,"a");//abre arquivo nome_arquivo para anexar, caso ainda não exista é criado e se existe, o texto é adicionado ao final do arquivo
		
	

	if(arquivo == NULL){//caso dê erro na abertura do arquivo, exibe a seguinte mensagem e sai do programa
		printf("Erro na criacao/abertura do arquivo!\n");
		exit(1);
	}else{//caso o arquivo consiga ser aberto com sucesso:
		printf("Digite o nome da coluna para chave primaria(sem espaços): ");
		tipo_var->nome_c = malloc(sizeof(char)*100);
		scanf("%s",tipo_var->nome_c);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
		printf("\n");
		fprintf(arquivo,"|%s<int>|",tipo_var->nome_c);
		printf("Deseja acrescentar uma nova coluna: (s/n)\n");
		scanf(" %c", &opc);//armazena opção do usuario de adicionar ou não mais uma coluna
		free(tipo_var->nome_c);
		fclose(arquivo);
		while(opc == 's'){
			tipo_c = malloc(sizeof(char)*20);
			tipo_var->nome_c = malloc(sizeof(char)*100);
			printf("Digite o nome da coluna(sem espaços): ");
			scanf("%s",tipo_var->nome_c);//armazena o nome da nova tabela, tendo de ser um nome simples sem espaços
			printf("\n");
			
			arquivo = fopen(tipo_var->nome_t,"r");
			if(arquivo == NULL){//caso dê erro na abertura do arquivo, exibe a seguinte mensagem e sai do programa
				printf("Erro na criacao/abertura do arquivo!\n");
				exit(1);
			}
			fgets(colunas,300,arquivo);
			fclose(arquivo);
			strcpy(str," ");
			str[0]='|';
			strcat(str,tipo_var->nome_c);
			strcat(str,"<");
			while(strstr(colunas,str)!= NULL){//repete enquanto existir a coluna digitada dentro do arquivo/tabela 	
				printf("Coluna ja existe!! Digite o nome da coluna(sem espaços): \n");//caso exista, mostra a mensagem e muda o valor de tem_coluna para 1
				scanf("%s",tipo_var->nome_c);
				tem_coluna = 1;
				strcpy(str," ");
				str[0]='|';
				strcat(str,tipo_var->nome_c);
				strcat(str,"<");
				//printf("%s",str);
			}
			tem_coluna = 0;//como saiu do loop, o nome da coluna não existe na tabela, então tem_coluna = 0
			
			arquivo = fopen(tipo_var->nome_t,"a");
	
			printf("Qual o tipo de dado a ser inserido na coluna:\n");
			printf("int\nfloat\ndouble\nchar\n");
			getchar();
			scanf("%s", tipo_c);//usuario insere um dos tipos  indicados acima
			printf("\n");
			fprintf(arquivo,"%s<%s>|", tipo_var->nome_c, tipo_c);	
			free(tipo_c);	
			free(tipo_var->nome_c);
			fclose(arquivo);
			printf("Deseja acrescentar uma nova coluna: (s/n)\n");//pergunta novmente ao usuário se ele deseja adicionar outra coluna
			scanf(" %c", &opc);//se 's' então voltamos ao inicio do while, se 'n' o programa prossegue para o próximo comando
		}
		arquivo = fopen(tipo_var->nome_t,"a");
		fprintf(arquivo,"\n");
		fclose(arquivo);
	}
	free(tipo_var->nome_t);
	free(tipo_var);
	//fclose(arquivo);//fechar arquivo arquivo
}

