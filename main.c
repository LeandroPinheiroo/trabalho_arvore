#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadArvore.h"
#include "desenvolvimento.h"

// Criando a enumeração:
enum boolean{
    true = 1, false = 0
};
typedef  enum boolean  bool;

int main(int argc, char const *argv[]){
	char arquivo_entrada[999];//declara url para receber entrada do arquivo
	char arquivo_saida[999];//declara url para receber saida do arquivo
	if(argc < 3){//caso argumentos menor que 3
		if(argc == 1){//caso tenha passado apenas um argumento
			printf("Não foi passado o arquivo contendo os dados de entrada\n");//Mostra erro
			return false;//sai do Main
		}
		printf("Nao foi passado nome do arquivo de saida, sera gerado um nome padrao\n");//mostra alerta
	}
	strcpy(arquivo_entrada,argv[1]);//copia arquivo de entrada para a URL
	if(argc < 3){//caso nao tenha passado o argumento para o nome de saida
		strcpy(arquivo_saida,"Saida.txt");//coloca um nome padrao para evitar erros
	}else{
		strcpy(arquivo_saida,argv[2]);//caso tenha passado o nome do arquivo de de saida utiliza o nome que o usuario passou
	}
	Arvore *arvore;
	arvore = cria_arvore();
	le_arquivo(arquivo_entrada,arquivo_saida,arvore);
	apaga_arvore(arvore);
	return true;
}