#include <stdlib.h>
#include <stdio.h>

typedef struct _nodo {
	int chave;
	// void *conteudo; opcional
	struct _nodo *esq, *dir;
} nodo;

nodo* insere(nodo* raiz, int x) {
	if (raiz == NULL) {
		nodo* novo = (nodo*) malloc(sizeof(nodo));
		novo->chave = x;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
	if(x < raiz->chave) 
		raiz->esq = insere(raiz->esq, x);
	if(x > raiz->chave)
		raiz->dir = insere(raiz->dir, x);
	return raiz;
}

int busca (nodo *raiz, int x) {
	if (raiz == NULL) return 0;
	if (raiz->chave == x) return 1;
	if (x < raiz->chave)
		return busca(raiz->esq, x);
	else
		return busca(raiz->dir, x);
}

void inorder(nodo *raiz){
	if (raiz == NULL)
		return;
	inorder(raiz->esq);
	printf("%d ", raiz->chave);
	inorder(raiz->dir);
}

void preorder(nodo *raiz){
	if (raiz == NULL) 
		return;
	printf("%d ", raiz->chave);
	preorder(raiz->esq);
	preorder(raiz->dir);
}

void freeTree(nodo *raiz){
	if (raiz == NULL) 
		return;
	freeTree(raiz->esq);
	freeTree(raiz->dir);
	free(raiz);
}

int main(int argc, char *argv[])
{
	nodo* tree = NULL;
	int* n = (int*) malloc(sizeof(int));
	int i = 0;
	int j;

	while(1){
		int x;
		scanf("%d", &x);
		if(x == -1){
			break;
		}
		tree = insere(tree, x);
	}

	while(1){
                int x;
                scanf("%d", &x);
                if(x == -1){
                        break;
                }
		n[i] = x;
		n = realloc(n, sizeof(n) + sizeof(int));
		i++;
        }

	for(j = 0; j < i; j++){
		int x = n[j];
		int encontrado = busca(tree, x);
                if(encontrado)
                        printf("%d encontrado\n", x);
                if(encontrado == 0)
                        printf("%d nao encontrado\n", x);
	}
	printf("preorder: ");
	preorder(tree);
	printf("\n");
	printf("inorder: ");
	inorder(tree);
	printf("\n");

	free(n);
	freeTree(tree);

	return 0;
}
