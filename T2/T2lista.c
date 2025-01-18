#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FE.h"
#define MAX 100

typedef struct Nodo {
    int info;
    int peso;
    struct Nodo *prox;
} nodo;

nodo *insereLista(nodo *lista, int v, int ponte) {
    nodo *novo = (nodo *) malloc(sizeof(novo));
    novo->info = v;
    novo->peso = ponte;
    novo->prox = lista;
    return novo;
}

void freeLista(nodo *lista){
    if(lista == NULL) return;
    freeLista(lista->prox);
    free(lista);
}

void handleAltura(nodo *lista, int v, int altura){
    if(lista == NULL) return;
    if(lista->info == v){
        lista->peso = altura;
    }
    handleAltura(lista->prox, v, altura);
}

int iesimaPonte(nodo *lista, int i){
    if(lista == NULL) return 0;
    if(i == lista->info) {
        return lista->peso;
    }
    iesimaPonte(lista->prox, i);
}

int bfs(nodo *lista[MAX], int r, int v, int N, int *pai, int *dist){
    r = r - 1;
    v = v - 1;
    int atual = v;
    Fila *fila = cria_fila();
    int *enfilerado = (int*) malloc(N * sizeof(int));
    int i, temCaminho = 0;

    for(i = 0; i < N; i++) {
        enfilerado[i] = 0;
        dist[i] = 0;
        pai[i] = -1;
    }

    fila_push(fila, r);
    enfilerado[r] = 1;
    while(vazia(fila) != 1){
        atual = fila_pop(fila);
        for(i = 0; i < N; i++){
            if(iesimaPonte(lista[atual], i + 1) > 0 && enfilerado[i] == 0 && atual != v){
                enfilerado[i] = 1;
                fila_push(fila, i);
                dist[i] = dist[atual] + 1;
                pai[i] = atual;
            }
            if(atual == v){
                temCaminho++;
                free(enfilerado);
                return temCaminho;
            } 
        }
    }
    freeFila(fila);
    free(enfilerado);
    return 0;
}

void imprimeCaminho(int r, int v, int *pai, int ultimo){
    if(v != r){
        imprimeCaminho(r, pai[v], pai, 0);
    } else ultimo = 1;

    if(ultimo == 1) printf("%d", v + 1);
    else printf(" -> %d", v + 1);
}

void dfs(nodo *lista[MAX], int *visitado, int r, int N, int *nIlhas, int *nPontes, int primeiro){
    int i, v;
    if(primeiro == 1) printf("[ %d ", r + 1);
    else printf("%d ", r + 1);
    visitado[r] = 1;
    for(i = 0; i < N; i++){
        if(iesimaPonte(lista[r], i + 1) > 0){
            nPontes[0]++;
        }
        if(visitado[i] == 0 && iesimaPonte(lista[r], i + 1) > 0){
            nIlhas[0]++;
            dfs(lista, visitado, i, N, nIlhas, nPontes, 0);
        }
    }
}

void arq(nodo *lista[MAX], int **entries, int nivel, int N){
    int *visitado = (int*) malloc(N * sizeof(int));
    int i, nArquipelagos = 0;
    int *nIlhas = (int*) malloc(1024 * sizeof(int));
    int *nPontes = (int*) malloc(1024 * sizeof(int));
    for(i = 0; i < N; i++){
        visitado[i] = 0;
    }
    for(i = 0; i < N; i++){
        if(visitado[i] == 0){
            nArquipelagos++;
            nIlhas[0] = 1;
            nPontes[0] = 0;
            dfs(lista, visitado, i, N, nIlhas, nPontes, 1);
            printf("] (%d Ilhas, ", nIlhas[0]);
            printf("%d Pontes)", nPontes[0]/2);
            printf("\n");
        }
    }
    printf("Total: %d arquipelagos\n", nArquipelagos);
    free(nIlhas);
    free(nPontes);
}

void ponteState(nodo *lista[MAX], int **entries, int nivel, int M, int N){
    int i, j;
    for(i = 0; i < M; i++){
        if(entries[i][2] <= nivel){
            handleAltura(lista[entries[i][0]-1], entries[i][1], 0);
            handleAltura(lista[entries[i][1]-1], entries[i][0], 0);
        }
        else{
            handleAltura(lista[entries[i][0]-1], entries[i][1], entries[i][2]);
            handleAltura(lista[entries[i][1]-1], entries[i][0], entries[i][2]);
        }
    }
}

int main(int argc, char *argv[]){
    int N, M, i, j;
    int **entries;
    int *alturaOriginal;
    scanf("%d %d", &N, &M);
    entries = (int**) malloc(M * sizeof(int*));
    alturaOriginal = (int*) malloc(M * sizeof(int));
    nodo *lista[N];
    for(i = 0; i < N; i++){
        lista[i] = NULL;
    }

    for(i = 0; i < M; i++){ 
        entries[i] = (int*) malloc(3 * sizeof(int));
        scanf("%d %d %d", &entries[i][0], &entries[i][1], &entries[i][2]);
        alturaOriginal[i] = entries[i][2];
    }

    //construindo a lista de adjacencia
    for(i = 0; i < M; i++){
        lista[entries[i][0]-1] = insereLista(lista[entries[i][0]-1], entries[i][1], alturaOriginal[i]);
        lista[entries[i][1]-1] = insereLista(lista[entries[i][1]-1], entries[i][0], alturaOriginal[i]);
    }

    int nivel = 0;
    int r, v, temCaminho;
    char *operation = (char*) malloc(7*sizeof(char));
    while (1){
        scanf("%s", operation);
        if(strcmp(operation, "arq") == 0){
            printf("\n");
            arq(lista, entries, nivel, N);
        }
        else if(strcmp(operation, "caminho") == 0){
            scanf("%d %d", &r, &v);
            printf("\n");
            int *pai = (int*) malloc(N * sizeof(int));
            int *dist = (int*) malloc(N * sizeof(int));
            temCaminho = bfs(lista, r, v, N, pai, dist);
            if(temCaminho == 0){
                printf("sem caminho entre %d e %d", r, v);
            } else {
                imprimeCaminho(r - 1, v - 1, pai, 0);
                printf(" (%d pontes)", dist[v-1]);
            }
            free(pai);
            free(dist);
            printf("\n");
        }
        else if(strcmp(operation, "agua") == 0){
            scanf("%d", &nivel);
            printf("\n");
            ponteState(lista, entries, nivel, M, N);
            printf("Nivel da agua: %d m\n", nivel);
        }
        else break;
        char *operation = (char*) malloc(7*sizeof(char));
    }
    free(operation);
    free(alturaOriginal);
    for(i = 0; i < M; i++) free(entries[i]);
    for(i = 0; i < N; i++) freeLista(lista[i]);
    return 0;
}
