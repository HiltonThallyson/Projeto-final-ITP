#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"
#include "structs.h"

int valida_tab(char *nome_tab);
int valida_chave(char *chave);
int valida_float(char *valor);
void listar_t();

void recebe_valor(char **valores_colunas, FILE *arquivo, int i, int n_de_linhas){
	char *temp = malloc(sizeof(char)*300);
	int cont, qtd_delim = 0, linha_atual = 0, cont_char = 0;
	
	while(fgets(temp,300,arquivo)){
		temp[strlen(temp)-1] = '\0';
		cont = 0;
		for (cont; cont < strlen(temp); cont++){
			if (temp[cont] == '|'){
				qtd_delim++;
			}
			if(qtd_delim == i+1){
				if(temp[cont+1]!='|'){
					valores_colunas[linha_atual][cont_char] = temp[cont+1];
					cont_char++;	
				}
			}
		}
		linha_atual++;
		cont_char = 0;
		qtd_delim = 0;
	}
}

void pesquisar_t(){
	FILE *arquivo;
	char string[300];//string que armazena cada linha do arquivo 1 por vez;
	char *temp;//string que recebe o valor da chave primaria;
	char *tipo_c;
	char opc = 's';
	char existe_c;
	char valor_inv = 'n';
	char str[300];
	char tipos[100][20];//vetor de strings que armazena os tipos de valores das colunas;
	char nome_colunas[100][50];//vetor de strings que armazena os nomes de valores das colunas;
	char **valores_colunas;//vetor que recebe os valores da coluna escolhida;
	char *tipo_valor;
	char *valor_p;
	int i = 0, j = 0, k = 0, t = 0, g = 0, h = 0, u = 0; // contadores;
	int r = 0; // variavel que recebe o resultado dos testes de tipo;
	int n_de_linhas = 0;
	int opcao = 0;

	tipos_valores *valores_tipos = malloc(sizeof(tipos_valores));
	variaveis *tipo_var = malloc(sizeof(variaveis));
	tipo_var->valor_c = malloc(sizeof(char)*100);
	
	//recebe o nome da tabela e abre o arquivo desejado;
	printf("Selecione a tabela:\n");
	listar_t();
	printf("\n");
	getchar();
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

	arquivo = fopen(tipo_var->nome_t, "r");
	free(tipo_var->nome_t);
	fgets(string,300,arquivo);
	
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
	i=0;
	j=0;
	h--;

	while (fgets(string,300,arquivo)){
		n_de_linhas++;
	}

	rewind(arquivo);
	while(opc == 's'){//enquanto usuario quiser pesquisar novas colunas na tabela
		valor_inv = 'n';
		rewind(arquivo);
		fgets(string,300,arquivo);
		tipo_var->nome_c = malloc(sizeof(char)*100);
		do{
			i=0;
			j=0;
			printf("Colunas existentes:\t%s\n", string);//mostra opcoes de colunas
			printf("Digite o nome da coluna a ser pesquisada:\t");
			scanf("%s",tipo_var->nome_c);//recebe nome da coluna a ser pesquisada
			while(i!=h){
				if(strcmp(tipo_var->nome_c, nome_colunas[i]) == 0){
					existe_c = 's';//se o nome digitado existir na coluna, muda opcao para sair do loop
					break;//finaliza o teste de existencia
				}else{
					existe_c = 'n';//caso nao exista a coluna, muda a opcao para continuar no teste
				}
				i++;
			}
			if(existe_c == 'n'){//caso n tenha achado a coluna imprime:
				printf("Coluna invalida!!\n");
			}
		}while(existe_c == 'n');
		printf("\n");
		free(tipo_var->nome_c);
		//achado a coluna:
		valores_colunas = malloc(sizeof(char *)*n_de_linhas);
		for(j ; j< n_de_linhas; j++){
			valores_colunas[j] = malloc(sizeof(char)*100);
		}

		recebe_valor(valores_colunas, arquivo, i, n_de_linhas);
		rewind(arquivo);
		j=0;
		printf("Qual valor deseja procurar?\t");
		valor_p = malloc(sizeof(char)*100);
		getchar();
		scanf("%[^\n]s", valor_p);//le o valor a ser pesquisado
		tipo_valor = malloc(sizeof(char)*10);
		printf("\n");
		//testa os tipos do valor_p
		if(valida_chave(valor_p) == 1 && strcmp(tipos[i],"int")==0){
			strcpy(tipo_valor, "int");//se for int, muda o valor do tipo_valor para int
			valores_tipos->valores_int = malloc(sizeof(int)*n_de_linhas);
			sscanf(valor_p, "%d", &tipo_var->valor_i);
			for(j; j < n_de_linhas; j++){
				sscanf(valores_colunas[j], "%d", &valores_tipos->valores_int[j]);
			}
		}else if(valida_float(valor_p) == 1){
			//caso o valor seja float/double, testa qual o tipo da coluna;
			if(strcmp(tipos[i],"float")==0){
				strcpy(tipo_valor, "float");//se for float, muda o valor do tipo_valor para float
				valores_tipos->valores_float = malloc(sizeof(float)* n_de_linhas);
				sscanf(valor_p, "%f", &tipo_var->valor_f);
				for(j; j < n_de_linhas; j++){
					sscanf(valores_colunas[j], "%f", &valores_tipos->valores_float[j]);
				}
			}else if(strcmp(tipos[i],"double") == 0){
				strcpy(tipo_valor, "double");//se for double, muda o valor do tipo_valor para double
				valores_tipos->valores_double = malloc(sizeof(double)* n_de_linhas);
				sscanf(valor_p, "%lf", &tipo_var->valor_d);
				for(j; j < n_de_linhas; j++){
					sscanf(valores_colunas[j], "%lf", &valores_tipos->valores_double[j]);
				}
			}
		}else{
			strcpy(tipo_valor, "char");//se for char/string , muda o valor do tipo_valor para char
		}
		if(strcmp(tipos[i], tipo_valor)==0){//se o tipo_valor for o mesmo do tipo da coluna:
			printf("Escolha uma das opcoes:\n(1) - Valores maiores que o informado\n(2) - Valores maiores ou iguais ao informado\n(3) - Valores iguais ao informado\n(4) - Valores menores que o valor informado\n(5) - Valores menores ou iguais ao informado\n\n");
			scanf("%d", &opcao);
			printf("\n");
			k = 0;
			switch(opcao){//verifica qual opcao o usuario digitou e executa a operacao;
				case 1:
					printf("Valores maiores que %s:\t", valor_p);
					if(strcmp(tipo_valor,"int") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_int[k] > tipo_var->valor_i){
								printf("%d\t", valores_tipos->valores_int[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_int);
					}else if(strcmp(tipo_valor,"float") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_float[k] > tipo_var->valor_f){
								printf("%f\t", valores_tipos->valores_float[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_float);	
					}else if(strcmp(tipo_valor,"double") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_double[k] > tipo_var->valor_d){
								printf("%lf\t", valores_tipos->valores_double[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_double);	
					}else{
						for(k; k < n_de_linhas; k++){
							if(strcmp(valores_colunas[k],valor_p)>0){
								printf("%s\t", valores_colunas[k]);
							}
						}
						printf("\n\n");
					}
					break;
				case 2:
				printf("Valores maiores ou iguais a %s:\t", valor_p);
					if(strcmp(tipo_valor,"int") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_int[k] >= tipo_var->valor_i){
								printf("%d\t", valores_tipos->valores_int[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_int);
					}else if(strcmp(tipo_valor,"float") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_float[k] >= tipo_var->valor_f){
								printf("%f\t", valores_tipos->valores_float[k]);
							}
						}
						printf("\n\n");
						k=0;
						free(valores_tipos->valores_float);
					}else if(strcmp(tipo_valor,"double") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_double[k] >= tipo_var->valor_d){
								printf("%lf\t", valores_tipos->valores_double[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_double);
					}else{
						for(k; k < n_de_linhas; k++){
							if(strcmp(valores_colunas[k],valor_p)>=0){
								printf("%s\t", valores_colunas[k]);
							}
						}
						printf("\n\n");
					}
					break;
				case 3:
				printf("Valores iguais a %s:\t", valor_p);
					if(strcmp(tipo_valor,"int") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_int[k] == tipo_var->valor_i){
								printf("%d\t", valores_tipos->valores_int[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_int);
					}else if(strcmp(tipo_valor,"float") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_float[k] == tipo_var->valor_f){
								printf("%f\t", valores_tipos->valores_float[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_float);
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_float[k] >= tipo_var->valor_f){
								printf("%f\t", valores_tipos->valores_float[k]);
							}
						}
					}else if(strcmp(tipo_valor,"double") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_double[k] == tipo_var->valor_d){
								printf("%lf\t", valores_tipos->valores_double[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_double);
					}else{
						for(k; k < n_de_linhas; k++){
							if(strcmp(valores_colunas[k], valor_p) == 0){
								printf("%s\t", valores_colunas[k]);
							}
						}
						printf("\n\n");
					}
					break;
				case 4:
					printf("Valores menores que %s:\t", valor_p);
					if(strcmp(tipo_valor,"int") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_int[k] < tipo_var->valor_i){
								printf("%d\t", valores_tipos->valores_int[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_int);
					}else if(strcmp(tipo_valor,"float") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_float[k] < tipo_var->valor_f){
								printf("%f\t", valores_tipos->valores_float[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_float);
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_float[k] >= tipo_var->valor_f){
								printf("%f\t", valores_tipos->valores_float[k]);
							}
						}
					}else if(strcmp(tipo_valor,"double") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_double[k] < tipo_var->valor_d){
								printf("%lf\t", valores_tipos->valores_double[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_double);
					}else{
						for(k; k < n_de_linhas; k++){
							if(strcmp(valores_colunas[k],valor_p) < 0){
								printf("%s\t", valores_colunas[k]);
							}
						}
						printf("\n\n");
					}
					break;
				case 5:
					printf("Valores menores ou iguais a %s:\t", valor_p);
					if(strcmp(tipo_valor,"int") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_int[k] <= tipo_var->valor_i){
								printf("%d\t", valores_tipos->valores_int[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_int);
					}else if(strcmp(tipo_valor,"float") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_float[k] <= tipo_var->valor_f){
								printf("%f\t", valores_tipos->valores_float[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_float);
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_float[k] >= tipo_var->valor_f){
								printf("%f\t", valores_tipos->valores_float[k]);
							}
						}
					}else if(strcmp(tipo_valor,"double") == 0){
						for(k ; k<n_de_linhas; k++){
							if(valores_tipos->valores_double[k] <= tipo_var->valor_d){
								printf("%lf\t", valores_tipos->valores_double[k]);
							}
						}
						printf("\n\n");
						free(valores_tipos->valores_double);
					}else{
						for(k; k < n_de_linhas; k++){
							if(strcmp(valores_colunas[k],valor_p) <= 0){
								printf("%s\t", valores_colunas[k]);
							}
						}
						printf("\n\n");
					}
					break;
				default:
					printf("Opcao invalida!!\n");			
			}	
		}else{
				printf("Valor invalido para o tipo da coluna!!\n");
				valor_inv = 's';//checa se o valor e invalido
		}
		if(valor_inv == 's'){
			opc = 's';
		}else{
			printf("Deseja realizar nova pesquisa? s-sim n-nao\n");
			scanf(" %c", &opc);
		}
		k=0;
		for(k ; k<n_de_linhas; k++){
			free(valores_colunas[k]);	
		}
		free(valores_colunas);
		free(valores_tipos);
		free(tipo_valor);
		free(valor_p);
	}	
	fclose(arquivo);	
}	