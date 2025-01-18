#include <stdio.h>
#include <stdlib.h>

typedef struct _nodo
{
    int key;
    struct _nodo *dir, *esq;
}nodo;

nodo* insere(nodo* raiz, int x) {
	if (raiz == NULL) {
		nodo* novo = (nodo*) malloc(sizeof(nodo));
		novo->key = x;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
	if(x < raiz->key) 
		raiz->esq = insere(raiz->esq, x);
	if(x > raiz->key)
		raiz->dir = insere(raiz->dir, x);
	return raiz;
}

void merge(nodo *raiz, int *N, int j, int k){
    if(j == k) return;
    
}

int main(int argc, char *argv[]){
    int N[100];
    int i = 0;
    while(1)
    {
        int x;
        scanf("%d", &x);
        if(x == -1) break;
        N[i] = x;
        i++;
    }
    int j, k;
    for(j = 0; j < i; j++){
        for(k = 0; k < i; k++){
            if(N[k] > N[j]){
                int aux = N[k];
                N[k] = N[j];
                N[j] = aux;
            }
        }
    }
    //for(j = 0; j < i; j++) printf("%d ", N[j]);

    int merge;

    
    return 0;
}