#include "tadArvore.h"//inclue funcoes de arvore
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//inclui bibliotecas necessariaas


//Funcao responsavel por ler do arquivo os dados necessarios
void le_arquivo(char url_entrada[],char url_saida[],Arvore *arvore){
	FILE *arquivo; //ponteiro para abrir arquivo de entrada
	FILE *arquivo_saida; //ponteiro para abrir arquivo de saida
	arquivo=fopen(url_entrada,"r");//abre arquivo em modo de leitura
	char string[999];//vetor de char para receber valores do arquivo
	int valor = 0;//inteiro para receber numeros do arquivos
	if(arquivo == NULL ){//se nao conseguiu abrir o arquivo
		printf("O arquivo não foi aberto corretamente\n");//mostra mensagem de erro ao abir arquivo 
		return;//sai da funcao
	}
	while(!feof(arquivo)){//equanto nao chega no fim do arquivo
		fscanf(arquivo,"%[^ ]s",string);//le a a string ate encontrar o espaco
		getc(arquivo);//pula espaco
		if(feof(arquivo)){//se fim do arquivo
			break;//se chega no fim do arquivo sai do loop
		}
		if(strcmp(string, "INCLUI") == 0){//se encontra palavra para inserir na arvore
			fscanf(arquivo,"%d",&valor);//le o valor a ser inserido
			arvore->raiz = insere_na_arvore(arvore->raiz,valor);//insere o valor na arvore utilizando funcao especifca 
			getc(arquivo);//pula \n
		}else if(strcmp(string, "EXCLUI") == 0){//se encontra palavra para remover valor da arvore
			fscanf(arquivo,"%d",&valor);//le o valor a ser removido
			arvore->raiz = remove_arvore(arvore->raiz,valor);//chama funcao especifica para remover valor da arvore
			getc(arquivo);//pula \n
		}else if(strcmp(string, "IMPRIME") == 0){//se leu palavra Imprime
			arquivo_saida=fopen(url_saida,"a+");//abre arquivo em modo de leitura e escrita
			fscanf(arquivo,"%[^\n]s",string);//le qual tipo de impressao 
			if(strcmp(string, "INORDEM") == 0){//caso INORDEM
				fprintf(arquivo_saida, "<");//printa < no arquivo
				in_ordem_arquivo(arvore->raiz,arquivo_saida);//chama funcao especifica para printar 
				fprintf(arquivo_saida,">\n");//printa > indicando que terminou os valores
			}else if(strcmp(string, "POSORDEM") == 0){//caso imprimir em posordem
				fprintf(arquivo_saida, "<");//printa < indicando que comeca a imprimir
				pos_ordem_arquivo(arvore->raiz,arquivo_saida);//chama funcao para imprimir em pos ordem
				fprintf(arquivo_saida,">\n");//printa > indicando que terminou os numeros
			}else if(strcmp(string, "PREORDEM") == 0){//caso pre ordem
				fprintf(arquivo_saida, "<");//printa > indicando que comeca a imprimir
				pre_ordem_arquivo(arvore->raiz,arquivo_saida);//chama funcao para imprimir em pre ordem
				fprintf(arquivo_saida,">\n");//printa > indicando que terminou os numeros
			}else if(strcmp(string, "BONITO") == 0){//caso modo de printar em formato de arvore
				draw_arvore_hor(arvore->raiz,arquivo_saida);//chama funcao
				fprintf(arquivo_saida, "\n");//printa quebra de linha
			}
			fclose(arquivo_saida);//fecha arquivo de saida
			getc(arquivo);//pula \n
		}
		else if(strcmp(string, "BUSCA") == 0){//caso busca
			arquivo_saida=fopen(url_saida,"a+");//abre arquivo em modo de leitura e escrita
			fscanf(arquivo,"%d",&valor);//le o valor
			No *aux = verifica_se_existe_valor_arvore(arvore->raiz, valor);//declara auxiliar para receber retorno da funcao que verifica se o arquivo esta na arvore
			if(aux!=NULL){//caso auxiliar diferente de NULL indica que achpu o elemento
				fprintf(arquivo_saida,"%d\n",aux->valor);//printa valor no arquivo
			}else{//caso nao achar o elemento 
				fprintf(arquivo_saida,"Elemento %d não encontrado\n",valor);//printa no arquivo que nao encontrou o arquivo
			}
			getc(arquivo);//pula \n
			fclose(arquivo_saida);//fecha o arquivo de saida
		}else if(strcmp(string, "FIM") == 0){//caso encontra palavra FIM
			return;//sai da funcao
		}else{//caso le algo que nao esta previsto
			fscanf(arquivo,"%[^\n]s",string);//le a linha toda ate o \n
			getc(arquivo);//pula \n
		}
	}
	fclose(arquivo);//fecha o arquivo
}