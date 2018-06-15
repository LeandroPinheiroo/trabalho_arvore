#include "tadArvore.h"
#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1
#define espaco 5


//função para iniciar a árvore vazia
void seta_vazia(Arvore *t){
	t = NULL;//Aponta arvore para null
}
//função para criar a árvore
Arvore* cria_arvore(){
	Arvore *t = (Arvore*)malloc(sizeof(struct ARVORE));//aloca na memoria
	seta_vazia(t);//aponta para null para evitar erros
	return(t);//retora arvore criada
}
//funcao responsavel por verificar a altura da arvore ou se necessario de algum no
int altura(No *raiz) {//calcula altura da arvore
   if (raiz == NULL){//caso raiz seja null
      return false; // altura da árvore vazia
   }
    int he = altura(raiz->esquerda);//chama recursivo a esquerda
    int hd = altura(raiz->direita);//chama recursivo a direita
    if (he < hd){//se esquerda menor que direita
		return hd + 1;//retorna valor a direita somado 1
	}
    return he + 1;//caso contrario retorna a altura esquerda mais 1 
}
int fator_balanceamento(No *raiz){//funcao responsavel por calcular o fator de balanceamento
	if (raiz == NULL){//caso raiz seja null
      return false; // árvore vazia
	}
   int fator = altura(raiz->esquerda) - altura(raiz->direita);//calcula o valor fo fator de balanceamento(valor da altura a esquerda - altura a direita)
   return fator;//retorna o valor do fator
}
//funcao responsavel por calcular o grau de algum no
int verifica_grau(No *raiz){//Calcula grau de um determinado NO
	if(raiz->direita == NULL && raiz->esquerda == NULL){//se direita e esquerda null
		return 0;//retorna 0
	}
	if(raiz->direita == NULL){//se direita null
		return 1;//retorna 1
	}
	if(raiz->esquerda == NULL){//se esquerda null
		return 1;//retorna 1
	}
	return 2;//caso contrario retorna 2
}
//Funcao responsavel por verificar o nivel de algum valor da arvore
int verifica_nivel_no(No *no, int valor){
	int nivel = 0;//contador de nivel
	while(no != NULL){//repte ate que o no aponte para NULL
		if(valor > no->valor){ //Se o elemento for maior que a raiz percorre para a direita
			no = no->direita;//no recebe a direita
			nivel++;//soma um no contador de nivel
		}else if(valor < no->valor){ //Se o elemento for menor que a raiz vai para a esquerda
			no = no->esquerda;//recebe no da esquerda
			nivel++;//soma no contador
		}else{//caso contrario
			//indica que encontrou o valor
			return nivel;//retorna o nivel do elemento
		}
	}
	return false;//retorna false indicando que o elemento nao esta na arvore
}

No* rotacaoEsquerda(No *no){//Rotacao a esquerda
    No *q = no->direita;//auxiliar 1 recebe o no a direita do passado
    No *temp = q->esquerda;//auxiliar 2 recebe no a esquerda do auxiliar 1 
	q->esquerda = no;//a esquerda do auxiliar 1 passa a ser o no recebido 
	no->direita = temp;//no a direita do passado passa a ser o auxiliar 2
	return q;//retorna o novo no
}

No* rotacaoDireita(No *no){//Rotacao a direita
	No *q = no->esquerda;////auxiliar 1 recebe o no a esquerda do passado
    No *temp = q->direita;//auxiliar 2 recebe no a direita do auxiliar 1 
	q->direita = no;//a direita do auxiliar 1 passa a ser o no recebido 
	no->esquerda = temp;//no a esquerda do passado passa a ser o auxiliar 2
 	return q;//retorna o novo no
}

No* rotacaoDE(No *no){//Rotacao direita depois esquerda
	No *aux;//cria auxiliar para receber retornos da funcao
    aux = rotacaoDireita(no->esquerda);//rotaciona o no da esquerda para a direita
    aux =rotacaoEsquerda(no);//rotaciona o no recebido a esquerda
	return aux;//retorna no
}

No* RotacaoED(No *no){//Rotacao a esquerda depois direita
	No *aux;//cria auxiliar para receber retornos da funcao
    aux = rotacaoEsquerda(no->direita);//rotaciona o no da direita para a esquerda
    aux = rotacaoDireita(no);//rotaciona o no recebido a direita
	return aux;//retorna o no
}


//função para inserir na árvore
No* insere_na_arvore(No *no,int valor){
	//se o ramo estiver vazio
	if(no == NULL){
		//aloca memória para ele
		no = (No*)malloc(sizeof(struct NO));
		//o ramo recebe o valor passado por parâmetro
		no->valor = valor;
		//coloca os apontadores do ramo como null
		no->direita = NULL;//aponta direita para null
		no->esquerda = NULL;//aponta esquerda para null
	}
	//se o ramo não estiver vazio, verifica o valor que está nele
	//se o valor do parâmetro for menor que o valor no ramo, vai para esquerda
	else if(valor < no->valor){
		no->esquerda = insere_na_arvore(no->esquerda,valor);
	}
	//se não for menor, vai para a direita
	else if(valor > no->valor){
		no->direita = insere_na_arvore(no->direita,valor);
	}else{//caso contrario indica que eh um elemento existente e nao insere o mesmo
        return no;//apenas retorna o no
    }
	if(fator_balanceamento(no) > 1){//caso fator balancemaneto maior que 1
        return rotacaoDireita(no);//rotaciona a direita e retorna o no
    }
	else if(fator_balanceamento(no) < -1 ){//caso fator de balanceamento menor q -1
        return rotacaoEsquerda(no);//rotaciona a esquerda e retorna o no
    }
	//else if(fator_balanceamento(no) > 1 ){
	//	return RotacaoED(no);
    //}else if(fator_balanceamento(no) < -1 ){
	//	return rotacaoDE(no);
    //}
	return no;//retorna no que foi inserido
}
//função para mostrar a árvore
void in_ordem_arquivo(No *no, FILE *arquivo){
	//verifica se o ramo não está vazio
	if(no != NULL){
		in_ordem_arquivo(no->esquerda,arquivo);
		fprintf(arquivo, "(%d)",no->valor);
		in_ordem_arquivo(no->direita,arquivo);
	}
}
void pre_ordem_arquivo(No *no,FILE *arquivo){
	//verifica se o ramo não está vazio
	if(no != NULL){
		fprintf(arquivo, "(%d)",no->valor);
		pre_ordem_arquivo(no->esquerda,arquivo);
		pre_ordem_arquivo(no->direita,arquivo);
	}
}
void pos_ordem_arquivo(No *no,FILE *arquivo){
	//verifica se o ramo não está vazio
	if(no != NULL){
		pos_ordem_arquivo(no->esquerda,arquivo);
		pos_ordem_arquivo(no->direita,arquivo);
		fprintf(arquivo, "(%d)",no->valor);
	}
}
//função para verificar se a árvore está vazia
boolean verifica_vazia(Arvore *t){
	//verifica se o raiz está apontada para NULL
	if(t->raiz == NULL){
		return(true);//retorna true indicando vazia
	}
	return(false);//retorna false indicando nao vazia
	
}
//função para verificar a existência de uma valor na árvore
No* verifica_se_existe_valor_arvore(No *no, int valor){
	//se o a raiz já estiver em NULL, já retorna null direto
	if(no == NULL){
		return NULL;	
	}
	//se o valor da raiz for maior que o valor passado por parâmetro
	else if(no->valor > valor){
		//vai para a esquerda da árvore
		return verifica_se_existe_valor_arvore(no->esquerda,valor);
	}
	//já se o valor for menor que o valor passado por parâmetro
	else if(no->valor < valor){
		//vai para o lado direito da árvore
		return verifica_se_existe_valor_arvore(no->direita,valor);
	}
	else{
		return no;
	}
}
//função para remover um valor especifíco da árvore
No* remove_arvore(No* no,int valor){
	//se o ramo estiver vazio
	if(no == NULL){
		//retorna vazio
		return NULL;
	}
	//se o valor no ramo for maior que o valor passado por parâmetro
	else if(no->valor > valor){
		//vai para a parte esquerda da árvore 
		no->esquerda = remove_arvore(no->esquerda,valor);
	}
	//se o valor no ramo for menor que o valor passado por parâmetro
	else if(no->valor < valor){
		//vai para a direita do ramo
		no->direita = remove_arvore(no->direita,valor);
	}
	//senão verifica os valores
	else{
		if(no->direita == NULL && no->esquerda == NULL){//se for no folha
			free(no);//libera o ponteiro do no
			no = NULL;//aponta para null
		}
		else if(no->esquerda == NULL){//caso a esquerda null
			No *aux1 = no;//cria auxiliar
			no = no->direita;//aponta para a direita
			free(aux1);//libera o auxiliar
		}
		else if(no->direita == NULL){//caso direita NULL
			No *aux1 = no;//cria auxiliar
			no = no->esquerda;//aponta para a esquerda
			free(aux1);//libera auxiliar
		}
		else{//caso contrario
			No *aux2 = no->esquerda;//gera auxiliar e aponta para a esquerda
			while(aux2->direita != NULL){//enquanto direita for diferente de NULL
				aux2 = aux2->direita;//auxiliar 2 vai para a direita ao maiximo
			}
			no->valor = aux2->valor;//troca os valores
			aux2->valor = valor;
			no->esquerda = remove_arvore(no->esquerda,valor);//chama funcao rescursiva para remover
		}
	}
	if(fator_balanceamento(no) > 1){
        return rotacaoDireita(no);
    }
	else if(fator_balanceamento(no) < -1 ){
        return rotacaoEsquerda(no);
    }
	//else if(fator_balanceamento(no) > 1 ){
	//	return RotacaoED(no);
   // }else if(fator_balanceamento(no) < -1 ){
		//return rotacaoDE(no);
   // }
	return(no);//retorna no 
}

void desenha_arvore_horiz(No *arvore, FILE *arq ,int depth, char *path, int direita)
{
    // stopping condition
    if (arvore== NULL)
        return;

    // increase spacing
    depth++;

    // start with direita no
    desenha_arvore_horiz(arvore->direita,arq, depth, path, 1);

    // set | draw map
    path[depth-2] = 0;

    if(direita)
        path[depth-2] = 1;

    if(arvore->esquerda)
        path[depth-1] = 1;

    // print root after spacing
    fprintf(arq,"\n");

    for(int i=0; i<depth-1; i++)
    {
      if(i == depth-2)
          fprintf(arq,"╬");
      else if(path[i])
          fprintf(arq,"║");
      else
          fprintf(arq," ");

      for(int j=1; j<espaco; j++)
      if(i < depth-2)
          fprintf(arq," ");
      else
          fprintf(arq,"═");
    }

    fprintf(arq,"%d\n", arvore->valor);

    // vertical espacors below
    for(int i=0; i<depth; i++)
    {
      if(path[i])
         fprintf(arq,"║");
      else
          fprintf(arq," ");

      for(int j=1; j<espaco; j++)
          fprintf(arq," ");
    }

    // go to esquerda no
    desenha_arvore_horiz(arvore->esquerda, arq,depth, path, 0);
}

//primary fuction
void draw_arvore_hor(No *arvore,FILE *arq)
{
    // should check if we don't exceed this somehow..
    char path[255] = {};

    //initial depth is 0
    desenha_arvore_horiz(arvore,arq, 0, path, 0);
}