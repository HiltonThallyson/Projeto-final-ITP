
#include <ctype.h>//necessaria por causa da funcao isdigit
//funcao para verificar se o conteudo recebido para a coluna ID é mesmo um inteiro, sem caracteres entre os digitos 
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
	for(i=0;i<strlen(valor);i++){//percorre cada caractere da string chave até ante do \0
		if(isdigit(valor[i])!=0){//se o char for um digito, o contato recebe ele mesmo + 1
			n++;
		}else if(valor[i]=='.'){
			ponto++;
		}
	}
	if(n==strlen(valor) || (n==strlen(valor)-1&&ponto==1)){
		return 1;
	}else{
		return 0;
	}	
}


//leitura de valores
int valor_i = 0;//variavel que armazenará o conteudo da coluna caso o usuario escolha a coluna do tipo inteiro
	float valor_f = 0;//variavel que armazenará o conteudo da coluna caso o usuario escolha a coluna do tipo float
	double valor_d = 0;///variavel que armazenará o conteudo da coluna caso o usuario escolha a coluna do tipo double
	char valor_c[50];//variavel que armazenará o conteudo da coluna caso o usuario escolha a coluna do tipo string
	char nome_arq[55];//string utilizada na nomeação do arquivo .txt de cada tabela, recebe o nome_t+".txt"
	char nome_t[50];//string que armazena o nome de uma tabela
	char nome_c[50];//string que armazena o nome de uma tabela