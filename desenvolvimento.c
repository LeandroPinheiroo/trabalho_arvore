#include "tadArvore.h"
void le_arquivo(char url_entrada[],char url_saida[],Arvore *arvore){
	FILE *arquivo; //ponteiro para abrir arquivo de entrada
	FILE *arquivo_saida; //ponteiro para abrir arquivo de saida
	arquivo=fopen(url_entrada,"r");//abre arquivo em modo de leitura
	char string[999];
	int valor = 0;
	if(arquivo == NULL ){
		printf("O arquivo não foi aberto corretamente\n");
		return;
	}
	while(!feof(arquivo)){
		fscanf(arquivo,"%[^ ]s",string);
		getc(arquivo);//pula espaco
		if(feof(arquivo)){//se fim do arquivo
			break;
		}
		if(strcmp(string, "INCLUI") == 0){
			fscanf(arquivo,"%d",&valor);
			arvore->raiz = insere_na_arvore(arvore->raiz,valor);
			getc(arquivo);//pula \n
		}else if(strcmp(string, "EXCLUI") == 0){
			fscanf(arquivo,"%d",&valor);
			arvore->raiz = remove_arvore(arvore->raiz,valor);
			getc(arquivo);//pula \n
		}else if(strcmp(string, "IMPRIME") == 0){
			arquivo_saida=fopen(url_saida,"a+");//abre arquivo em modo de leitura e escrita
			fscanf(arquivo,"%[^\n]s",string);
			if(strcmp(string, "INORDEM") == 0){
				fprintf(arquivo_saida, "<");
				in_ordem_arquivo(arvore->raiz,arquivo_saida);
				fprintf(arquivo_saida,">\n");
			}else if(strcmp(string, "POSORDEM") == 0){
				fprintf(arquivo_saida, "<");
				pos_ordem_arquivo(arvore->raiz,arquivo_saida);
				fprintf(arquivo_saida,">\n");
			}else if(strcmp(string, "PREORDEM") == 0){
				fprintf(arquivo_saida, "<");
				pre_ordem_arquivo(arvore->raiz,arquivo_saida);
				fprintf(arquivo_saida,">\n");
			}else if(strcmp(string, "BONITO") == 0){
				draw_arvore_hor(arvore->raiz,arquivo_saida);
				fprintf(arquivo_saida, "\n");
			}
			fclose(arquivo_saida);
			getc(arquivo);//pula \n
		}
		else if(strcmp(string, "BUSCA") == 0){
			arquivo_saida=fopen(url_saida,"a+");//abre arquivo em modo de leitura e escrita
			fscanf(arquivo,"%d",&valor);
			No *aux = verifica_se_existe_valor_arvore(arvore->raiz, valor);
			if(aux!=NULL){
				fprintf(arquivo_saida,"%d\n",aux->valor);
			}else{
				fprintf(arquivo_saida,"Elemento %d não encontrado\n",valor);
			}
			getc(arquivo);//pula \n
			fclose(arquivo_saida);
		}else if(strcmp(string, "FIM") == 0){
			return;
		}else{
			fscanf(arquivo,"%[^\n]s",string);
			getc(arquivo);//pula \n
		}
	}
	fclose(arquivo);
}