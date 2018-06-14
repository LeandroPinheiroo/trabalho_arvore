#include <stdio.h>
#include <stdlib.h>

// Criando a enumeração:
enum boolean {
    true = 1, false = 0
};
typedef  enum boolean  bool;


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
   int fator = altura(raiz->esquerda) - altura(raiz->direita);//calcula o valor fo fator de balanceamento
   return fator;//retorna o valor do fator
}

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

int verifica_nivel_no(No *no, int valor){
	int nivel = 0;
	while(no != NULL){
		if(valor > no->valor){ //Se o elemento for maior que a raiz vai para a direita
			no = no->direita;
			nivel++;
		}else{
			if(valor < no->valor){ //Se o elemento for menor que a raiz vai para a esquerda
				no = no->esquerda;
				nivel++;
			}else{ 	
				//Achou o valor
				return nivel;
			}
		}
	}
}

No* rotacaoEsquerda(No *no){//LL
    No *q = no->direita;
    No *temp = q->esquerda;
	q->esquerda = no;
	no->direita = temp;
	return q;
}

No* rotacaoDireita(No *no){//RR
	No *q = no->esquerda;
    No *temp = q->direita;
	q->direita = no;
	no->esquerda = temp;
 	return q;
}

No* rotacaoDE(No *no){//LR
	No *aux;
    aux = rotacaoDireita(no->esquerda);
    aux =rotacaoEsquerda(no);
	return aux;
}

No* RotacaoED(No *no){//RL
	No *aux;
    aux = rotacaoEsquerda(no->direita);
    aux = rotacaoDireita(no);
	return aux;
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
	}else{
        return no;
    }
	if(fator_balanceamento(no) > 1){
        return rotacaoDireita(no);
    }
	else if(fator_balanceamento(no) < -1 ){
        return rotacaoEsquerda(no);
    }
	else if(fator_balanceamento(no) > 1 ){
        //no->esquerda = rotacaoEsquerda(no->esquerda);
        //return rotacaoDireita(no);
		return RotacaoED(no);
    }else if(fator_balanceamento(no) < -1 ){
		return rotacaoDE(no);
        //no->direita = rotacaoDireita(no->direita);
        //return rotacaoEsquerda(no);
    }
	return no;//retorna no que foi inserido
}
//função para mostrar a árvore
void mostra_arvore(No *no){
	//verifica se o ramo não está vazio
	if(no != NULL){
		mostra_arvore(no->esquerda);
		printf("%i\n",no->valor);
		mostra_arvore(no->direita);
	}
}
//função para verificar se a árvore está vazia
bool verifica_vazia(Arvore *t){
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
	return(no);//retorna no 
}


int main(){
	Arvore *arvore = cria_arvore();
	arvore->raiz = insere_na_arvore(arvore->raiz,4);
	arvore->raiz = insere_na_arvore(arvore->raiz,2);
	arvore->raiz = insere_na_arvore(arvore->raiz,6);
	arvore->raiz = insere_na_arvore(arvore->raiz,1);
	arvore->raiz = insere_na_arvore(arvore->raiz,3);
	arvore->raiz = insere_na_arvore(arvore->raiz,5);
	arvore->raiz = insere_na_arvore(arvore->raiz,14);
	arvore->raiz = insere_na_arvore(arvore->raiz,7);
	arvore->raiz = insere_na_arvore(arvore->raiz,15);
	arvore->raiz = insere_na_arvore(arvore->raiz,13);


	

	mostra_arvore(arvore->raiz);
	
	return(0);
}