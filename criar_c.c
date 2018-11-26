#include <stdio.h>
#include <stdlib.h>
#include <string.h>//necessaria por causa da funcao strcpy e strcat
#include "funcoes.h"
#include "structs.h"

int valida_tab(char *nome_tab);
void listar_t();

void criar_c(){
	FILE *arquivo;
	FILE *newfile;
	char string[300];//string que armazena cada linha do arquivo 1 por vez;
	char *temp;//string que recebe o valor da chave primaria;
	char *tipo_c;
	char opc = 's';
	char str[300];
	int n_de_colunas = 0, tem_coluna = 0;
	variaveis *tipo_var = malloc(sizeof(variaveis));
	tipo_var->valor_c = malloc(sizeof(char)*100);

	//recebe o nome da tabela e abre o arquivo desejado;
	printf("Selecione a tabela:\n");
	listar_t();
	printf("\n");
	tipo_var->nome_t = malloc(sizeof(char)*100);
	scanf("%s",tipo_var->nome_t);
	printf("\n");
	//Pede ao usuário o nome da tabela até obter um nome de tabela que existe
	while(valida_tab(tipo_var->nome_t)==0){
		printf("Tabela não existe!! Selecione a tabela:\n\n");
		listar_t();
		printf("\n");
		getchar();
		scanf("%s",tipo_var->nome_t);
		printf("\n");	
	}
	//abre o arquivo temporário para escrita
	newfile = fopen("newfile","w+");
	if (newfile == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}
	//abre o arquivo para leitura
	arquivo = fopen(tipo_var->nome_t,"r");
	if (arquivo == NULL){
		printf("Erro na abertura do arquivo!");
		exit(1);
	}else{
		fgets(string,300,arquivo);			//lê cada linha do arquivo
		string[strlen(string)-1] = '\0';    //coloca um \0 ao final da string(que era um \n)
		fputs(string,newfile);//copia a primeira linha do arquivo original no arquivo temporário
		fclose(newfile);
		//enquanto o usuário desejar, acrescente colunas
		while(opc == 's'){
			newfile = fopen("newfile","a+");//abre arquivo temporário para anexar
			if (newfile == NULL){
				printf("Erro na abertura do arquivo!");
				exit(1);
			}
			tipo_var->nome_c = malloc(sizeof(char)*100);
			printf("Digite o nome da coluna(sem espaços): ");
			scanf("%s",tipo_var->nome_c);//armazena o nome da nova coluna que o usuário inseriu
			printf("\n");
			strcpy(str," ");
			str[0]='|';
			strcat(str,tipo_var->nome_c);
			strcat(str,"<");
			while(strstr(string,str)!= NULL){//repete enquanto existir a coluna digitada dentro do arquivo/tabela 	
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
			
			tipo_c = malloc(sizeof(char)*20);
			if(tem_coluna == 0){//caso a coluna digitada não exista na tabela
				printf("Qual o tipo de dado a ser inserido na coluna:\n");//pede o tipo do valor da coluna
				printf("int\nfloat\ndouble\nchar\n");
				getchar();
				scanf("%s", tipo_c);//usuario insere um dos tipos indicados acima
				printf("\n");

				fprintf(newfile,"%s<%s>|", tipo_var->nome_c, tipo_c);//coloca o nome da coluna e o tipo no arquivo temporario
				n_de_colunas++;	//incrementa o numero de colunas adicionadas
				fclose(newfile);//fecha o arquivo temporário para atualizá-lo
				newfile = fopen("newfile", "r");//abre novamente o arquivo temporário, só que para leitura
				if (newfile == NULL){
					printf("Erro na abertura do arquivo!");
					exit(1);
				}
				fgets(string,300,newfile);//pega a primeira linha do arquivo newfile(que será a string com o nome e tipos das colunas)
				fclose(newfile);
				printf("Deseja acrescentar uma nova coluna: (s/n)\n");//pergunta novmente ao usuário se ele deseja adicionar outra coluna
				scanf(" %c", &opc);//se 's' então voltamos ao inicio do while, se 'n' o programa prossegue para o próximo comando	
			}else{//caso tem_coluna = 0 muda automáticamente a opc para sim e repete o loop
				fclose(newfile);
				opc = 's';
			}
			free(tipo_var->nome_c);
			free(tipo_c);
		}
		newfile = fopen("newfile","a+");//abre o arquivo temporário para anexar
		if (newfile == NULL){
			printf("Erro na abertura do arquivo!");
			exit(1);
		}
		fprintf(newfile,"\n");//coloca um \n no final da linha
		fclose(newfile);
		newfile = fopen("newfile","a+");
		while(fgets(string,300,arquivo)){//pega cada linha 
			string[strlen(string)-1] = '\0';//e acrescenta o \0 no lugar do \n na string
			fputs(string,newfile);//coloca a nova string sem o \n no arquivo temporário
			//faz um loop com o numero de iterações igual ao n de coluna adicionados
			for(int i=0; i<n_de_colunas;i++){
				fprintf(newfile,"%s|", "-");//coloca o - para indicar que a coluna tem valor inválido/nulo
			}
			fprintf(newfile,"\n");//coloca um \n no final da linha
		}
		fclose(newfile);
		fclose(arquivo);
		remove(tipo_var->nome_c);
		rename("newfile",tipo_var->nome_t);
		free(tipo_var->nome_t);
		free(tipo_var);
	}

}
