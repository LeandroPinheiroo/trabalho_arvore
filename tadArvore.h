#ifndef _Arvore_ 
#define _Arvore_ 
#include <stdio.h>
#include <stdlib.h>

typedef int boolean;

//estrutura para representar folhas
typedef struct NO{
	int valor;
	struct NO *direita;
	struct NO *esquerda;
}No;
//estrutura para representar arvore
typedef struct ARVORE{
	struct NO *raiz;
}Arvore;

void seta_vazia(Arvore *t);
Arvore* cria_arvore();
int altura(No *raiz);
int fator_balanceamento(No *raiz);
int verifica_grau(No *raiz);
int verifica_nivel_no(No *no, int valor);
No* rotacaoEsquerda(No *no);
No* rotacaoDireita(No *no);
No* rotacaoDE(No *no);
No* RotacaoED(No *no);
No* insere_na_arvore(No *no,int valor);
void in_ordem_arquivo(No *no, FILE *arquivo);
void pre_ordem_arquivo(No *no,FILE *arquivo);
void pos_ordem_arquivo(No *no,FILE *arquivo);
boolean verifica_vazia(Arvore *t);
No* verifica_se_existe_valor_arvore(No *no, int valor);
No* remove_arvore(No* no,int valor);
void desenha_arvore_horiz(No *arvore, FILE *arq ,int depth, char *path, int direita);
void draw_arvore_hor(No *arvore,FILE *arq);

#endif