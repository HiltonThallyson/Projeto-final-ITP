#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include <ctype.h>
#include "funcoes.h"
#include "structs.h"

int valida_chave(char *chave);
int valida_float(char *valor);
int valida_tab(char *nome_tab);
void listar_t();

void editar_t(){
	FILE *arquivo;//arquivo original a ser lido;
	FILE *newfile;//arquivo que recebe a nova versao do original;
	variaveis *tipo_var = malloc(sizeof(variaveis));
	int i = 0, j=0, k=0, t=0, g=0, h=0, u=0;// contadores;
	int r = 0;// variavel que recebe o resultado dos testes de tipo;
	int tem_chave = 0; //variavel para verificar se a chave inserida ja existe no arquivo;
	char tipos[100][20];//vetor de strings que armazena os tipos de valores das colunas;
	char nome_colunas[100][50];//vetor de strings que armazena os nomes de valores das colunas;
	char string[300];//string que armazena cada linha do arquivo 1 por vez;
	char *temp;//string que recebe o valor da chave primaria;
	char opc = 's';//variavel que armazena a opcao de criar um nova linha ou nao;
	tipo_var->chave = malloc(sizeof(char)*100);
	tipo_var->valor_c = malloc(sizeof(char)*100);

	//recebe o nome da tabela e abre o arquivo desejado;
	printf("Selecione a tabela:\n");
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
	}else{
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
	fclose(arquivo);
	//enquanto o usuario quiser editar linhas ou enquanto o usuario nao digitar uma chave que existe no arquivo;
	while (opc == 's'){
		do{
			printf("Digite o valor da chave(%s):",nome_colunas[0]);
			scanf("%s",tipo_var->chave);
			r = valida_chave(tipo_var->chave);//verifica se a chave e int;
		}while (r == 0);

		arquivo = fopen(tipo_var->nome_t,"r");//abre arquivo original para leitura;
		newfile = fopen("newfile","w");//abre arquivo novo para escrita;
		while (fgets(string,300,arquivo)){
			g=0;
			temp = malloc(sizeof(char)*50);
			//armazena o valor da chave de cada linha em temp;
			while(string[g+1]!='|'){
				temp[g] = string[g+1];
				g++;
			}
			i=1;
			//testa se a chave existe no arquivo;				 
			if(strcmp(temp,tipo_var->chave)==0){
				tem_chave = 1;//caso exista a chave no arquivo, salva na variavel a informacao que existe a chave;
				fprintf(newfile,"|%s|",temp);//insere a linha de titulos no arquivo novo;
				//loop que recebe o valor de cada coluna;
				do{
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
						fprintf(newfile, "%s|",tipo_var->valor_c);
					}else if(strcmp(tipos[i],"float")==0){
						do{
							scanf("%s",tipo_var->valor_c);
							r = valida_float(tipo_var->valor_c);
							if(r==0){
								printf("tipo invalido! Digite o valor da coluna(%s):",nome_colunas[i]);
							}
						}while(r==0);
						fprintf(newfile, "%s|",tipo_var->valor_c);
					}else if(strcmp(tipos[i],"double")==0){
						do{
							scanf("%s",tipo_var->valor_c);
							r = valida_float(tipo_var->valor_c);
							if(r==0){
								printf("tipo invalido! Digite o valor da coluna(%s):",nome_colunas[i]);
							}
						}while(r==0);
						fprintf(newfile, "%s|",tipo_var->valor_c);
					}else if(strcmp(tipos[i],"char")==0){
						getchar();
						scanf("%[^\n]s",tipo_var->valor_c);
						while(strcmp(tipo_var->valor_c,"-")==0){
							printf("Valor NULO! Digite outro valor!\n");
							getchar();
							scanf("%[^\n]s",tipo_var->valor_c);
						}
						fprintf(newfile, "%s|",tipo_var->valor_c);
					}
					i++;
				}while (i!=h-1);
				fprintf(newfile,"\n");//insere uma mudanca de linha ao final da linha;
			}else{//caso a chave nao esteja na linha, salva a linha original no arquivo novo;
				fputs(string,newfile);
			}
			free(temp);
		}
		//testa se a chave foi encontrada no arquivo original;
		if(tem_chave==0){
			//caso n tenha encontrado a chave no arquivo, pede para o usuario digitar outra chave;
			printf("Chave nao econtrada! Digite uma nova chave:\n");
			opc = 's';
		}else if(tem_chave == 1){
			//caso tenha editado o arquivo com sucesso, pergunta se o usuario deseja editar outra linha;
			printf("Deseja editar outra linha: s-sim n-nao\n");
			scanf(" %c",&opc);
		}

		fclose(arquivo);//fecha arquivo original;
		fclose(newfile);//fecha novo arquivo;
		remove(tipo_var->nome_t);//remove o arquivo original;
		rename("newfile",tipo_var->nome_t);//renomeia o novo arquivo com o nome do original;

		
	}
	//desaloca todas as variaveis alocadas;
	free(tipo_var->nome_t);
	free(tipo_var->valor_c);
	free(tipo_var->chave);
	free(tipo_var);
}
