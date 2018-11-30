#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include <ctype.h>
#include "funcoes.h"
#include "structs.h"

int valida_tab(char *nome_tab);
void listar_t();

void apagar_t(){
	FILE *bd;//arquivo original a ser lido;
	FILE *newbd;//arquivo que recebe a nova versao do original;
	variaveis *tipo_var = malloc(sizeof(variaveis));
	int ntabelas;
	int tem_tab = 0; //variavel para verificar se a chave inserida ja existe no arquivo;
	char string[300];//string que armazena cada linha do arquivo 1 por vez;
	char *temp;//string que recebe o valor da chave primaria;
	char opc = 's';//variavel que armazena a opcao de criar um nova linha ou nao;
	char certeza;

	bd = fopen("BD-ITP","r");
	if (bd == NULL){
			printf("Erro na abertura do arquivo!");
			exit(1);
		}else{
			fscanf(bd,"|ntabelas = %d|\n", &ntabelas);
	}
	if(ntabelas==0){
		printf("Banco não tem tabelas!!\n");	
	}
	fclose(bd);
	//enquanto o usuario quiser apagar tabelas ou enquanto existir tabelas no banco;
	while (opc == 's'&&ntabelas>0){
		//recebe o nome da tabela e abre o arquivo desejado;
		printf("Selecione a tabela:\n");
		listar_t();
		tipo_var->nome_t = malloc(sizeof(char)*100);
		scanf("%s",tipo_var->nome_t);
		printf("\n");
		while(valida_tab(tipo_var->nome_t)==0){
			printf("Tabela não existe!! Selecione a tabela: ");
			scanf("%s",tipo_var->nome_t);
		}
		bd = fopen("BD-ITP","r");
		if (bd == NULL){
			printf("Erro na abertura do arquivo!");
			exit(1);
		}else{
			fscanf(bd,"|ntabelas = %d|\n", &ntabelas);//le a primeira linha do arquivo com os nomes das colunas e tipos de valores;		
			printf("Tem certeza de que seja apagar a tabela %s do banco? (s)SIM (n)NÃO\n",tipo_var->nome_t);

			getchar();
			scanf("%c",&certeza);
		}
		fclose(bd);
		//se quiser mesmo apagar
		if (certeza == 's'){
			tem_tab=0;
			bd = fopen("BD-ITP","r");//abre arquivo original para leitura;
			newbd = fopen("newfile","w");//abre arquivo novo para escrita;
			fgets(string,300,bd);
			ntabelas--;
			fprintf(newbd,"|ntabelas = %d|\n", ntabelas);
			while (fgets(string,300,bd)){
				temp = malloc(sizeof(char)*50);
				strcpy(temp," ");
				strcpy(temp,tipo_var->nome_t);
				strcat(temp,"\n\0");			 
				if(strcmp(string,temp)!=0){
					fputs(string,newbd);
				}else{
					tem_tab++;			
				}
				free(temp);
			}
			fclose(bd);//fecha arquivo original;
			fclose(newbd);//fecha novo arquivo;
			remove("BD-ITP");//remove o arquivo original;
			rename("newfile","BD-ITP");//renomeia o novo arquivo com o nome do original;
			}
			if(tem_tab==0||certeza=='n'){
				//caso n tenha encontrado a tabela no arquivo, ou desistiu de apagar a tabela anterior;
				printf("Deseja apagar outra tabela: s-sim n-nao\n");
				scanf(" %c",&opc);
			}else if(tem_tab == 1&&certeza=='s'){
				remove(tipo_var->nome_t);
				printf("Tabela apagada!\n");
				//caso tenha apagado a tabela com sucesso, pergunta se o usuario deseja apagar outra tabela;
				//rewind(arquivo);
			
				printf("Deseja apagar outra tabela: s-sim n-nao\n");
				scanf(" %c",&opc);
				tem_tab == 0;
			}
		free(tipo_var->nome_t);
				
		}
	//desaloca todas as variaveis alocadas;
	free(tipo_var);
}
