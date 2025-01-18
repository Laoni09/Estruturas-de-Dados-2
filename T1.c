#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define VERMELHO 1
#define PRETO 0

typedef struct _nodo{
	int key;
	int cor;
	char *content;
	struct _nodo *esq, *dir, *pai;

} nodo;

nodo* criaNodo(int key, int cor, char *content){
	nodo* novo = (nodo*) malloc(sizeof(nodo));
	novo->key = key;
	novo->cor = cor;
	novo->content = content;
}

void rotacaoRR(nodo* alvo){
	nodo* aux = alvo->pai;
	aux->esq = alvo->dir;
	alvo->dir = aux;
	aux->pai->esq = alvo;
	alvo->pai = aux->pai;
	aux->pai = alvo;
}

void rotacaoLL(nodo *alvo){
	nodo *aux = alvo->pai;
	aux->dir = alvo->esq;
	alvo->esq = aux;
	aux->pai->dir = alvo;
	alvo->pai = aux->pai;
	aux->pai = alvo;
}

void rotacaoRL(nodo *alvo){
	rotacaoRR(alvo);
	rotacaoLL(alvo);
}

void rotacaoLR(nodo *alvo){
	rotacaoLL(alvo);
	rotacaoRR(alvo);
}

nodo *insere(nodo* raiz, int key, char *content){
	if(raiz == NULL) {
		nodo* novo = criaNodo(key, PRETO, content);
		novo->dir = NULL;
		novo->esq = NULL;
		novo->pai = NULL;
		return novo;
	}
	nodo *aux = raiz;
	while (1)
	{
		if(key < aux->key){
			if(aux->esq == NULL) break;
			aux = aux->esq;
		}
		else if (key > aux->key){
			if(aux->dir == NULL) break;
			aux = aux->dir;	
		}
	}
	nodo* novo = criaNodo(key, VERMELHO, content);
	novo->dir = NULL;
	novo->esq = NULL;
	novo->pai = aux;

	//verifica erros em nodos à esquerda
	if(key < aux->key) {
		aux->esq = novo;
		//aqui acessa o avo
		if(aux != raiz){
				printf("%d\n", novo->pai->pai->key);
		}

		//fixes
		//pai vermelho?
		if(novo->pai->cor == VERMELHO){
			//inserção na subárvore esquerda do filho esquerdo
			if(novo->pai->key < novo->pai->pai->key){
				if(novo->pai->pai->dir != NULL){
					//tio vermelho?
					if(novo->pai->pai->dir->cor == VERMELHO){
						novo->pai->pai->dir->cor = PRETO;
						//atenção para quando o vo for raiz
						novo->pai->pai->cor = VERMELHO;
						novo->pai->cor = PRETO;
					}
					
					//tio preto?	
					else if(novo->pai->pai->dir->cor == PRETO){
						rotacaoRR(novo->pai);
					}
				}

				else{
					rotacaoRR(novo->pai);
				}

				//recolore o irmão se necessário
				if(novo->pai->dir != NULL)
					novo->pai->dir->cor = VERMELHO;
			}
			//inserção na subárve direita do filho esquerdo (LR)
			if(novo->pai->key > novo->pai->pai->key){
				if(novo->pai->pai->dir != NULL){
					//tio vermelho?
					if(novo->pai->pai->dir->cor == VERMELHO){
						novo->pai->pai->dir->cor = PRETO;
						//atenção para quando o vo for raiz
						novo->pai->pai->cor = VERMELHO;
						novo->pai->cor = PRETO;
					}

					//tio preto?
					else if(novo->pai->pai->dir->cor == PRETO){
						rotacaoLR(novo->pai);
					}
				}
				else{
					rotacaoLR(novo->pai);
				}

				//recolore o irmão se necessário
				if(novo->pai->esq != NULL)
					novo->pai->esq->cor = VERMELHO;
			}
		}
	}

	//verifica erros em nodos à direita
	else if(key > aux->key) {
		aux->dir = novo;
		
		if(novo->pai->cor == VERMELHO){
			//RL
			if(novo->pai->key < novo->pai->pai->key){
				if(novo->pai->pai->esq != NULL){
					//tio vermelho?
					if(novo->pai->pai->esq->cor == VERMELHO){
						novo->pai->pai->esq->cor = PRETO;
						//atenção para quando o vo for raiz
						novo->pai->pai->cor = VERMELHO;
						novo->pai->cor = PRETO;
					}
					
					//tio preto?	
					else if(novo->pai->pai->esq->cor == PRETO){
						rotacaoRL(novo->pai);
					}
				}

				else{
					rotacaoRL(novo->pai);
				}

				//recolore o irmão se necessário
				if(novo->pai->dir != NULL)
					novo->pai->dir->cor = VERMELHO;
			}
			//LL
			if(novo->pai->key > novo->pai->pai->key){
				if(novo->pai->pai->esq != NULL){
					//tio vermelho?
					if(novo->pai->pai->esq->cor == VERMELHO){
						novo->pai->pai->esq->cor = PRETO;
						//atenção para quando o vo for raiz
						novo->pai->pai->cor = VERMELHO;
						novo->pai->cor = PRETO;
					}
					
					//tio preto?	
					else if(novo->pai->pai->esq->cor == PRETO){
						rotacaoLL(novo->pai);
					}
				}

				else{
					rotacaoLL(novo->pai);
				}

				//recolore o irmão se necessário
				if(novo->pai->esq != NULL)
					novo->pai->esq->cor = VERMELHO;
			}
		}
	}
	//corrige raiz vermelha
	novo->pai->cor = PRETO;
	raiz->cor = PRETO;
	return raiz;
	
}

void preOrder(nodo* raiz){
	if(raiz == NULL)
		return;
	printf("%d %d\n", raiz->key, raiz->cor);
	preOrder(raiz->esq);
	preOrder(raiz->dir);
}

int main(int argc, char *argv[]){
	nodo *raiz = NULL;
	char operation;
	int key;
	//a entrada de dados está correta?
	char *content = (char*) malloc(4096*sizeof(char));
	while(1){
		scanf("%s", &operation);
		switch(operation){
			case '+':
				//insere;
				scanf("%d %[^\n]", &key, content);
				raiz = insere(raiz, key, content);
				break;
			case '?':
				//busca;
				printf("?");
				break;
			case '>':
				//sucessor;
				printf(">");
				break;
			case '<':
				//antecessor;
				printf("<");
				break;
			case '#':
				//preorder;
				preOrder(raiz);
				//o gabarito tá certo?
				break;
			default:
				break;
		}
	}
	free(content);
	return 0;
}
