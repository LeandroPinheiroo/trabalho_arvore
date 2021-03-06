#ifndef _Arvore_ 
#define _Arvore_ 
#include <stdio.h>
#include <stdlib.h>

typedef int boolean;//simula tipo boolean

//estrutura para representar folhas
typedef struct NO{
	int valor;//representa valor
	struct NO *direita;//no a direita
	struct NO *esquerda;//no a esquerda
}No;//typedef de No para facilitar 
//estrutura para representar arvore
typedef struct ARVORE{
	struct NO *raiz;
}Arvore;
//Escopo de funcoes de arvore
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
boolean apaga_arvore(Arvore *arvore);
#endif