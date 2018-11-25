#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include <ctype.h>
#include "funcoes.h"
#include "structs.h"

int valida_tab(char *nome_tab);
void listar_t();

int valida_chave(char *chave){
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

int valida_float(char *valor){
	int i,n=0,ponto=0;		
	for(i=0;i<strlen(valor);i++){//percorre cada caractere da string chave até antes do \0
		if(isdigit(valor[i])!=0){//se o char for um digito, o contador recebe ele mesmo + 1
			n++;
		}else if(valor[i]=='.'){
			ponto++;
		}
	}
	if(n == strlen(valor) || (n==strlen(valor)-1 && ponto==1)){
		return 1;
	}else{
		return 0;
	}	
}

void criar_l(){
	FILE *arquivo;
	char opc = 's';//variavel que armazena a opcao de criar um nova linha ou nao;
	int i = 0, j = 0, k = 0, t = 0, g = 0, h = 0, u = 0; // contadores;
	int r = 0; // variavel que recebe o resultado dos testes de tipo;
	char tipos[100][20];//vetor de strings que armazena os tipos de valores das colunas;
	char nome_colunas[100][50];//vetor de strings que armazena os nomes de valores das colunas;
	char string[300];//string que armazena cada linha do arquivo 1 por vez;
	char *temp;//string que recebe o valor da chave primaria;
	variaveis *tipo_var = malloc(sizeof(variaveis));
	tipo_var->chave = malloc(sizeof(char)*100);
	tipo_var->valor_c = malloc(sizeof(char)*100);
	
	//recebe o nome da tabela e abre o arquivo desejado;
	printf("Selecione a tabela\n");
	listar_t();
	printf("\n");
	getchar();
	tipo_var->nome_t = malloc(sizeof(char)*100);
	scanf("%s",tipo_var->nome_t);
	printf("\n");
	
	while(valida_tab(tipo_var->nome_t)==0){
		printf("Tabela não existe!! Selecione a tabela:\n\n");
		listar_t();
		printf("\n");
		getchar();
		scanf("%s",tipo_var->nome_t);	
	}
	
	arquivo = fopen(tipo_var->nome_t,"r");
	if (arquivo == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}
	else{
		fscanf(arquivo, "%[^\n]s", string);//le a primeira linha do arquivo com os nomes das colunas e tipos de valores;
		//armazena nos devidoes vetores os tipos e nomes das colunas
		for (i; i<strlen(string);i++){
			if(string[i] == '<'){
				j=i+1;
				while (string[j]!='>'){
					tipos[t][k] = string[j];//armazena tipos;
					k++;
					j++;
				}
				tipos[t][k] = '\0';
				t++;
				k=0;
			}else if(string[i]=='|'){
				j=i+1;
				while(string[j]!='<' && string[j]!='\n'){
					nome_colunas[h][u] = string[j];//armazena nomes das colunas;
					u++;
					j++;
				}
				nome_colunas[h][u] = '\0';
				h++;
				u=0;
			}
		}
	}
	//loop para adicionar linha enquanto o usuario desejar;
	do{	
		i=0;
		do{
			printf("Digite o valor da chave(%s):",nome_colunas[0]);
			scanf("%s",tipo_var->chave);
			r = valida_chave(tipo_var->chave);//testa se chave e inteiro;
		}while (r == 0);
		fclose(arquivo);//fecha o arquivo para salvar as informacoes editadas de cada loop
		arquivo = fopen(tipo_var->nome_t,"r");//abre novamente o arquivo para leitura;
		//loop que le linha por linha ate ler a ultima linha;
		while (fgets(string,300,arquivo)){
			g=0;
			temp = malloc(sizeof(char)*50);
			//le a string a partir do char | enquanto nao achar outro |;
			while(string[g+1]!='|'){
				temp[g] = string[g+1];//armazena characteres da chave no temp;
				g++;
			}				 
			if(strcmp(temp,tipo_var->chave)==0){//testa se existe a chave no arquivo;
				do{
					//caso exista, pede outra chave e testa se ela e int;
					printf("Chave já existe!! Digite o valor da chave(%s):",nome_colunas[0]);
					scanf("%s",tipo_var->chave);
					r = valida_chave(tipo_var->chave);
				}while (r == 0);
				rewind(arquivo);
			}
			free(temp);
		}
		fclose(arquivo);
		//depois de verificado se a chave inserida nao existe no arquivo, comeca a leitura dos dados das colunas;
		arquivo = fopen(tipo_var->nome_t,"a");

		if (arquivo == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
		}
		fprintf(arquivo,"|%s|", tipo_var->chave);
		i=1;
		while (i!=h-1){//varia i da primeira coluna a ultima;
			printf("Digite o valor da coluna(%s):",nome_colunas[i]);
			//testa se o usuario inseriu o valor da coluna com o tipo correto da mesma;
			if (strcmp(tipos[i],"int")==0){
				do{
					scanf("%s",tipo_var->valor_c);
					r = valida_chave(tipo_var->valor_c);
					if(r==0){
						printf("tipo invalido! Digite o valor da coluna(%s):",nome_colunas[i]);
					}
				}while(r==0);
					fprintf(arquivo, "%s|",tipo_var->valor_c);
			}else if(strcmp(tipos[i],"float")==0){
				do{
					scanf("%s",tipo_var->valor_c);
					r = valida_float(tipo_var->valor_c);
					if(r==0){
						printf("tipo invalido! Digite o valor da coluna(%s):",nome_colunas[i]);
					}
				}while(r==0);
					fprintf(arquivo, "%s|",tipo_var->valor_c);
			}else if(strcmp(tipos[i],"double")==0){
				do{
					scanf("%s",tipo_var->valor_c);
					r = valida_float(tipo_var->valor_c);
					if(r==0){
						printf("tipo invalido! Digite o valor da coluna(%s):",nome_colunas[i]);
					}
				}while(r==0);
					fprintf(arquivo, "%s|",tipo_var->valor_c);
			}else if(strcmp(tipos[i],"char")==0){
				getchar();
				scanf("%[^\n]s",tipo_var->valor_c);
				fprintf(arquivo, "%s|",tipo_var->valor_c);
			}
			i++;
		}
		fprintf(arquivo,"\n");
		printf("Deseja adicionar uma nova linha: s-sim n-nao ");
		scanf(" %c",&opc);
	}while(opc != 'n');
	fclose(arquivo);
	free(tipo_var->valor_c);
	free(tipo_var->chave);
	free(tipo_var->nome_t);
	free(tipo_var);
}
