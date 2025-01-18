//trabalho realizado pelos alunos Laôni Moreira e Juan Peres
#include <stdlib.h>
#include <stdio.h>

typedef struct _nodo{
	int key;
	int balanc;
    int altura;
	char *content;
	struct _nodo *esq, *dir, *pai;

} nodo;

void ajustaBalanceamento(nodo *raiz){
	int alturaDir = 0;
	int alturaEsq = 0;
	if(raiz->dir != NULL) alturaDir = raiz->dir->altura;
	else alturaDir = 0;
	if(raiz->esq != NULL) alturaEsq = raiz->esq->altura;
	else alturaEsq = 0;
	if(alturaEsq >= alturaDir) raiz->altura = alturaEsq + 1;
	else raiz->altura = alturaDir + 1;
	raiz->balanc = alturaEsq - alturaDir;
}

nodo* rotacaoRR(nodo* alvo){
	nodo *aux = alvo->esq;
	alvo->esq = aux->dir;
	if(aux->dir != NULL) aux->dir->pai = alvo;
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
	if(aux->esq != NULL) aux->esq->pai = alvo;
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
	if(aux->dir != NULL) aux->dir->pai = alvo->dir;
	aux->dir = alvo->dir;
	if(aux->dir != NULL) aux->dir->pai = aux;
	alvo->dir = aux;
	aux->pai = alvo;

	//L
	nodo *aux2 = alvo->dir;
	alvo->dir = aux2->esq;
	if(aux2->esq != NULL) aux2->esq->pai = alvo;
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
	if(aux->esq != NULL) aux->esq->pai = alvo->esq;
	aux->esq = alvo->esq;
	if(aux->esq != NULL) aux->esq->pai = aux;
	alvo->esq = aux;
	aux->pai = alvo;

	//R
	nodo *aux2 = alvo->esq;
	alvo->esq = aux2->dir;
	if(aux2->dir != NULL) aux2->dir->pai = alvo;
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
	else if(x > raiz->key)
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
	else if (raiz->key == x) {
		printf("elemento repetido\n");
		return raiz;
	}
	return raiz;
}

int busca (nodo *raiz, int x) {
	if (raiz == NULL){
		printf("nao encontrado\n");
		return 0;
	}
	if (raiz->key == x) {
		printf("%s\n", raiz->content);
		return 1;
	}
	if (x < raiz->key) return busca(raiz->esq, x);
	else return busca(raiz->dir, x);
}

void freeTree(nodo *raiz){
	if (raiz == NULL) return;
	freeTree(raiz->esq);
	freeTree(raiz->dir);
	free(raiz->content);
	free(raiz);
}

void preOrder(nodo* raiz, int primeiro){
	if(raiz == NULL) 
		return;
	if(primeiro == 1) printf("%d", raiz->key);
	else printf(" %d", raiz->key);
	preOrder(raiz->esq, 0);
	preOrder(raiz->dir, 0);
}

void sucessor(nodo *raiz, int x){
	nodo *aux = raiz;
	//flag para ver se o número maior de menor diferença já foi encontrado
	nodo *nMenorDiferenca = NULL;
	if(raiz != NULL)
		if(raiz->key > x) nMenorDiferenca = raiz;
	int diferenca1;
	int diferenca2;
	while (1)
	{
		//verifica as situações de nodos à esquerda e à direita enquanto a chave ainda não foi encontrada
		if(aux == NULL){
			printf("chave invalida\n");
			return;
		}
		if(x == aux->key){
			if(aux->dir == NULL && nMenorDiferenca != NULL){
				printf("%d %s\n", nMenorDiferenca->key, nMenorDiferenca->content);
				return;
			}
			else if(aux->dir == NULL && nMenorDiferenca == NULL){
				printf("maior\n");
				return;
			}
			else if(aux->dir != NULL)
				aux = aux->dir;
			break;
		}
		if(x < aux->key){
			if(nMenorDiferenca == NULL)
				nMenorDiferenca = aux;
			else{
				//calcula as diferenças e o módulo se necessário
				diferenca1 = aux->key - x;
				diferenca2 = nMenorDiferenca->key - x;
				//compara as diferencas
				if(diferenca1 < diferenca2)
					nMenorDiferenca = aux;
			}
			aux = aux->esq;
		}
		else if (x > aux->key)
			aux = aux->dir;	
	}

	//verifica a situação do nodo imediatamente à direita
	if(nMenorDiferenca == NULL)
			nMenorDiferenca = aux;
	else{
		//calcula as diferenças
		diferenca1 = aux->key - x;
		diferenca2 = nMenorDiferenca->key - x;
		//compara as diferencas
		if(diferenca1 < diferenca2)
			nMenorDiferenca = aux;
	}

	//verifica as situações de nodos à direita e à esquerda depois que a chave foi encontrada
	while(1){
		if(aux->esq != NULL){
			aux = aux->esq;
			//calcula as diferenças
			diferenca1 = aux->key - x;
			diferenca2 = nMenorDiferenca->key - x;
			//compara as diferencas
			if(diferenca1 < diferenca2)
				nMenorDiferenca = aux;
		}
		else if(aux->dir != NULL){
			aux = aux->dir;
			//calcula as diferenças
			diferenca1 = aux->key - x;
			diferenca2 = nMenorDiferenca->key - x;
			//compara as diferencas
			if(diferenca1 < diferenca2)
				nMenorDiferenca = aux;
		}
		else{
			if(nMenorDiferenca == NULL)
				printf("maior\n");
			else printf("%d %s\n", nMenorDiferenca->key, nMenorDiferenca->content);
			return;
		}
	}
}


void antecessor(nodo *raiz, int x){
	nodo *aux = raiz;
	//flag para ver se o número menor de menor diferença já foi encontrado
	nodo *nMenorDiferenca = NULL;
	if(raiz != NULL)
		if(raiz->key < x) nMenorDiferenca = raiz;
	int diferenca1;
	int diferenca2;
	while (1)
	{
		//verifica as situações de nodos à esquerda e à direita enquanto a chave ainda não foi encontrada
		if(aux == NULL){
			printf("chave invalida\n");
			return;
		}
		if(x == aux->key){
			if(aux->esq == NULL && nMenorDiferenca != NULL){
				printf("%d %s\n", nMenorDiferenca->key, nMenorDiferenca->content);
				return;
			}
			else if(aux->esq == NULL && nMenorDiferenca == NULL){
				printf("menor\n");
				return;
			}
			else if(aux->esq != NULL)
				aux = aux->esq;
			break;
		}
		if(x < aux->key){
			aux = aux->esq;
		}
		else if (x > aux->key){
			if(nMenorDiferenca == NULL)
				nMenorDiferenca = aux;
			else{
				//calcula as diferenças
				diferenca1 = x - aux->key;
				diferenca2 = x - nMenorDiferenca->key;
				//compara as diferencas
				if(diferenca1 < diferenca2)
					nMenorDiferenca = aux;
			}
			aux = aux->dir;	
		}
	}

	//verifica a situação do nodo imediatamente à esquerda
	if(nMenorDiferenca == NULL)
			nMenorDiferenca = aux;
	else{
		//calcula as diferenças
		diferenca1 = x - aux->key;
		diferenca2 = x - nMenorDiferenca->key;
		//compara as diferencas
		if(diferenca1 < diferenca2)
			nMenorDiferenca = aux;
	}

	//verifica as situações de nodos à direita e à esquerda depois que a chave foi encontrada
	while(1){
		if(aux->dir != NULL){
			aux = aux->dir;
			//calcula as diferenças
			diferenca1 = x - aux->key;
			diferenca2 = x - nMenorDiferenca->key;
			//compara as diferencas
			if(diferenca1 < diferenca2)
				nMenorDiferenca = aux;
		}
		else if(aux->esq != NULL){
			aux = aux->esq;
			//calcula as diferenças
			diferenca1 = x - aux->key;
			diferenca2 = x - nMenorDiferenca->key;
			//compara as diferencas
			if(diferenca1 < diferenca2)
				nMenorDiferenca = aux;
		}
		else{
			if(nMenorDiferenca == NULL)
				printf("menor\n");
			else printf("%d %s\n", nMenorDiferenca->key, nMenorDiferenca->content);
			return;
		}
	}
}

int main(int argc, char *argv[]){
	nodo *raiz = NULL;
	char operation;
	int key;
	char *content = (char*) malloc(4096*sizeof(char));
	while (scanf("%s", &operation) != EOF){
		switch(operation){
			case '+':
				scanf("%d %[^\n]", &key, content);
				raiz = insere(raiz, key, content);
				content = (char*) malloc(4096*sizeof(char));			
				break;
			case '?':
				scanf("%d", &key);
				busca(raiz, key);
				break;
			case '>':
				scanf("%d", &key);
				sucessor(raiz, key);
				break;
			case '<':
				scanf("%d", &key);
				antecessor(raiz, key);
				break;
			case '#':
				if(raiz == NULL) printf("arvore vazia");
				preOrder(raiz, 1);
				printf("\n");
				break;
			default:
				break;
		}
	}
	free(content);
	freeTree(raiz);
	return 0;
}
