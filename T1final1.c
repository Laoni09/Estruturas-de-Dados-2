#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define VERMELHO 1
#define PRETO 0

typedef struct _nodo{
	int key;
	int balanc;
    int altura;
	char *content;
	struct _nodo *esq, *dir, *pai;

} nodo;

nodo* criaNodo(int key, char *content){
	nodo* novo = (nodo*) malloc(sizeof(nodo));
	novo->key = key;
	novo->balanc = 0;
    novo->altura = 1;
	novo->content = content;
}

void ajustaBalanceamento(nodo *raiz){
	int alturaDir = 0;
	int alturaEsq = 0;
	if(raiz->dir != NULL)
		alturaDir = raiz->dir->altura;
	else alturaDir = 0;
	if(raiz->esq != NULL)
		alturaEsq = raiz->esq->altura;
	else alturaEsq = 0;
	if(alturaEsq >= alturaDir)
		raiz->altura = alturaEsq + 1;
	else raiz->altura = alturaDir + 1;
	raiz->balanc = alturaEsq - alturaDir;
}

nodo* rotacaoRR(nodo* alvo){
	nodo *aux = alvo->esq;
	alvo->esq = aux->dir;
	if(aux->dir != NULL)
		aux->dir->pai = alvo;
	aux->dir = alvo;
	alvo->pai = aux;

	//consertando os balanceamentos
	ajustaBalanceamento(alvo);
	ajustaBalanceamento(aux);

	return aux;
}

nodo* rotacaoLL(nodo *alvo){
	nodo *aux = alvo->dir;
	alvo->dir = aux->esq;
	if(aux->esq != NULL)
		aux->esq->pai = alvo;
	aux->esq = alvo;
	alvo->pai = aux;

	//consertando os balanceamentos
	ajustaBalanceamento(alvo);
	ajustaBalanceamento(aux);

	return aux;
}


//verificar
nodo* rotacaoRL(nodo *alvo){
	//R
	nodo *aux = alvo->dir->esq;
	alvo->dir->esq = aux->dir;
	if(aux->dir != NULL)
		aux->dir->pai = alvo->dir;
	aux->dir = alvo->dir;
	if(aux->dir != NULL)
		aux->dir->pai = aux;
	alvo->dir = aux;
	aux->pai = alvo;

	//L
	nodo *aux2 = alvo->dir;
	alvo->dir = aux2->esq;
	if(aux2->esq != NULL)
		aux2->esq->pai = alvo;
	aux2->esq = alvo;
	aux2->esq->pai = aux2;

	//consertando os balanceamentos
	ajustaBalanceamento(aux2->dir);
	ajustaBalanceamento(aux2->esq);
	ajustaBalanceamento(aux2);

	return aux2;
}

nodo* rotacaoLR(nodo *alvo){
	//L
	nodo *aux = alvo->esq->dir;
	alvo->esq->dir = aux->esq;
	if(aux->esq != NULL)
		aux->esq->pai = alvo->esq;
	aux->esq = alvo->esq;
	if(aux->esq != NULL)
		aux->esq->pai = aux;
	alvo->esq = aux;
	aux->pai = alvo;

	//R
	nodo *aux2 = alvo->esq;
	alvo->esq = aux2->dir;
	if(aux2->dir != NULL)
		aux2->dir->pai = alvo;
	aux2->dir = alvo;
	alvo->pai = aux2;

	//consertando os balanceamentos
	ajustaBalanceamento(aux2->dir);
	ajustaBalanceamento(aux2->esq);
	ajustaBalanceamento(aux2);

	return aux2;
}

nodo* insere(nodo* raiz, int x, char *content) {
	if (raiz == NULL) {
		nodo* novo = (nodo*) malloc(sizeof(nodo));
        novo->altura = 1;
		novo->key = x;
		//está preenchendo todos os nós com o msm conteúdo????
		novo->content = content;
        novo->pai = NULL;
		novo->esq = NULL;
		novo->dir = NULL;
		printf("\n");
		return novo;
	}
	if (raiz->key == x){
		printf("elemento repetido\n");
		return raiz;
	}

    int alturaEsq;
    int alturaDir;
	if(x < raiz->key){ 
		raiz->esq = insere(raiz->esq, x, content);
        raiz->esq->pai = raiz;

		//verificando o balanceamento
        ajustaBalanceamento(raiz);

		if (raiz->balanc != -1 && raiz->balanc != 0 && raiz->balanc != 1)
		{
			if(x < raiz->key && x < raiz->esq->key){
				raiz = rotacaoRR(raiz);
			}
			else if(x < raiz->key && x > raiz->esq->key){
				raiz = rotacaoLR(raiz);
			}
		}
    }
	if(x > raiz->key)
	{
		raiz->dir = insere(raiz->dir, x, content);
		raiz->dir->pai = raiz;

		//verificando o balanceamento
        ajustaBalanceamento(raiz);

		if (raiz->balanc != -1 && raiz->balanc != 0 && raiz->balanc != 1)
		{
			if(x > raiz->key && x < raiz->dir->key){
				raiz = rotacaoRL(raiz);
			}
			else if(x > raiz->key && x > raiz->dir->key){
				raiz = rotacaoLL(raiz);
			}
		}
	}
	return raiz;
}

int busca (nodo *raiz, int x) {
	if (raiz == NULL){
		printf("nao encontrado\n");
		return 0;
	}
	if (raiz->key == x) {
		printf(" %s\n", raiz->content);
		return 1;
	}
	if (x < raiz->key)
		return busca(raiz->esq, x);
	else
		return busca(raiz->dir, x);
}

void freeTree(nodo *raiz){
	if (raiz == NULL) 
		return;
	freeTree(raiz->esq);
	freeTree(raiz->dir);
	free(raiz);
}

void preOrder(nodo* raiz){
	if(raiz == NULL)
		return;
	printf("%d %s\n", raiz->key, raiz->content);
	preOrder(raiz->esq);
	preOrder(raiz->dir);
}

void sucessor(nodo *raiz, int x){
	nodo *aux = raiz;
	//flag para ver se o número maior de menor diferença já foi encontrado
	int nMenorDiferenca = -1;
	if(raiz != NULL){
		if(raiz->key > x)
			nMenorDiferenca = raiz->key;
	}
	int diferenca1;
	int diferenca2;
	while (1)
	{
		if(aux == NULL){
			printf("chave invalida\n");
			return;
		}
		if(x == aux->key){
			if(aux->dir == NULL && nMenorDiferenca > 0)
				printf("%d\n", nMenorDiferenca);
			else if(aux->dir == NULL && nMenorDiferenca < 0)
				printf("maior\n");
			else if(aux != NULL)
				aux = aux->dir;
			break;
		}
		if(x < aux->key){
			if(nMenorDiferenca == -1){
				nMenorDiferenca = aux->key;
			}
			else{
				//calcula as diferenças e o módulo se necessário
				diferenca1 = aux->key - x;
				if(diferenca1 < 0) diferenca1 = diferenca1*(-1);
				diferenca2 = nMenorDiferenca - x;
				if(diferenca2 < 0) diferenca2 = diferenca2*(-1);
				//compara as diferencas
				if(diferenca1 < diferenca2)
					nMenorDiferenca = aux->key;
			}
			aux = aux->esq;
		}
		else if (x > aux->key){
			aux = aux->dir;	
		}
	}

	while(1){
		if(nMenorDiferenca == -1){
			nMenorDiferenca = aux->key;
		}
		else{
			//calcula as diferenças e o módulo se necessário
			diferenca1 = aux->key - x;
			diferenca2 = nMenorDiferenca - x;
			if(diferenca2 < 0) diferenca2 = diferenca2*(-1);
			//compara as diferencas
			if(diferenca1 < diferenca2)
				nMenorDiferenca = aux->key;
		}
		if(aux->esq != NULL){
			aux = aux->esq;
			//calcula as diferenças e o módulo se necessário
			diferenca1 = aux->key - x;
			diferenca2 = nMenorDiferenca - x;
			if(diferenca2 < 0) diferenca2 = diferenca2*(-1);
			//compara as diferencas
			if(diferenca1 < diferenca2)
				nMenorDiferenca = aux->key;
		}
		if(aux == NULL){
			break;
		}
	}
}


void antecessor(nodo *raiz, int x){
	
}

int main(int argc, char *argv[]){
	nodo *raiz = NULL;
	char operation;
	int key;
	//a entrada de dados está correta?
	char *content = (char*) malloc(1024*sizeof(char));
	while(1){
		scanf("%s", &operation);
		switch(operation){
			case '+':
				//insere
				scanf("%d %[^\n]", &key, content);
				raiz = insere(raiz, key, content);
				content = (char*) malloc(1024*sizeof(char));			
				break;
			case '?':
				//busca;
				scanf("%d", &key);
				//tratar o retorno
				busca(raiz, key);
				break;
			case '>':
				//sucessor;
				//sucessor seria o numero maior que ele?
				scanf("%d", &key);
				sucessor(raiz, key);
				break;
			case '<':
				//antecessor;
				//antecessor seria o numero menor que ele?
				scanf("%d", &key);
				antecessor(raiz, key);
				break;
			case '#':
				//preorder;
				if(raiz == NULL) printf("arvore vazia\n");
				preOrder(raiz);
				break;
			default:
				break;
		}
	}
	free(content);
	freeTree(raiz);
	return 0;
}
