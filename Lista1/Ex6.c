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

int LCA(nodo *raiz, int x, int y){
    if(x < raiz->chave && y > raiz->chave){
        //ver isso aq
        return raiz->chave;
    } 
    if(x == raiz->esq->chave)
        return raiz->chave;
    if(y == raiz->dir->chave)
        return raiz->chave;

    if(y > raiz->chave)
        return LCA(raiz->dir, x, y);
    else 
        return LCA(raiz->esq, x, y);
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

    while (1)
    {
        int x, y, lca;
        scanf("%d %d", &x, &y);
        if(x == -1)
            break;
        lca = LCA(tree, x, y);
        printf("%d\n", lca);
    }
        

	printf("preorder: ");
	preorder(tree);
	printf("\n");
	printf("inorder: ");
	inorder(tree);
	printf("\n");

	freeTree(tree);

	return 0;
}