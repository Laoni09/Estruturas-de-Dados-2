#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct {
    int v[MAX];
    int ini, fim;
} Fila;

Fila *cria_fila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = 0;
    return f;
}

void fila_push(Fila *f, int x) {
    f->v[ f->fim ] = x; // e se estiver cheia?
    f->fim = (f->fim+1)%MAX;
}
//como libera a fila estática?
int fila_pop(Fila *f) {
    int x = f->v[ f->ini ]; // e se estiver vazia?
    f->ini = (f->ini + 1)%MAX;
    return x;
}

int vazia(Fila *f) {
    return f->ini == f->fim ? 1 : 0;
}

int bfs(int **mat, int r, int v, int N, int *pai, int *dist){
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
            if(mat[atual][i] > 0 && enfilerado[i] == 0 && atual != v){
                enfilerado[i] = 1;
                fila_push(fila, i);
                dist[i] = dist[atual] + 1;
                pai[i] = atual;
            }
            if(atual == v){
                temCaminho++;
                //printf("%d ", dist[v]);
                free(enfilerado);
                return temCaminho;
            } 
        }
    }
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

void dfs(int **mat, int *visitado, int r, int N, int *nIlhas, int *nPontes, int primeiro){
    int i, v;
    if(primeiro == 1) printf("[ %d ", r + 1);
    else printf("%d ", r + 1);
    visitado[r] = 1;
    for(i = 0; i < N; i++){
        if(mat[r][i]){
            nPontes[0]++;
        }
        if(mat[r][i] > 0 && visitado[i] == 0){
            nIlhas[0]++;
            dfs(mat, visitado, i, N, nIlhas, nPontes, 0);
        }
    }
}

void arq(int **mat, int **entries, int nivel, int N){
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
            dfs(mat, visitado, i, N, nIlhas, nPontes, 1);
            printf("] (%d Ilhas, ", nIlhas[0]);
            printf("%d Pontes)", nPontes[0]/2);
            printf("\n");
        }
    }
    printf("Total: %d arquipelagos\n", nArquipelagos);
    //por que este free está errado?
    free(nIlhas);
    free(nPontes);
}

void ponteState(int **mat, int **entries, int nivel, int M, int N){
    int i, j;
    for(i = 0; i < M; i++){
        if(entries[i][2] <= nivel){
            //printf("%d %d %d\n", i, entries[i][0], entries[i][1]);
            mat[entries[i][0]-1][entries[i][1]-1] = 0;
            mat[entries[i][1]-1][entries[i][0]-1] = 0;
        }
        else{
            //printf("%d %d %d\n", i, entries[i][0], entries[i][1]);
            mat[entries[i][0]-1][entries[i][1]-1] = entries[i][2];
            mat[entries[i][1]-1][entries[i][0]-1] = entries[i][2];
        }
    }
}

int main(int argc, char *argv[]){
    //captura dos dados
    int N, M, i, j;
    int **entries;
    int **mat;
    int *alturaOriginal;
    scanf("%d %d", &N, &M);
    entries = (int**) malloc(M * sizeof(int*));
    mat = (int**) malloc(N * sizeof(int*));
    alturaOriginal = (int*) malloc(M * sizeof(int));

    for(i = 0; i < M; i++){ 
        entries[i] = (int*) malloc(3 * sizeof(int));
        scanf("%d %d %d", &entries[i][0], &entries[i][1], &entries[i][2]);
        alturaOriginal[i] = entries[i][2];
    }

    //alocando as colunas e zerando tudo
    for(i = 0; i < N; i++){
        mat[i] = (int*) malloc(N * sizeof(int));
        for(j = 0; j < N; j++){
            mat[i][j] = 0;
        }
    }
    //construindo a matriz de adjacencia (talvez reutilizar a função ponteState)
    for(i = 0; i < M; i++){
        //printf("%d %d %d\n", i, entries[i][0], entries[i][1]);
        mat[entries[i][0]-1][entries[i][1]-1] = alturaOriginal[i];
        mat[entries[i][1]-1][entries[i][0]-1] = alturaOriginal[i];
    }

    int nivel = 0;
    int r, v, temCaminho;
    char *operation = (char*) malloc(7*sizeof(char));
    while (1){
        scanf("%s", operation);
        if(strcmp(operation, "arq") == 0){
            printf("\n");
            arq(mat, entries, nivel, N);
        }
        else if(strcmp(operation, "caminho") == 0){
            scanf("%d %d", &r, &v);
            printf("\n");
            int *pai = (int*) malloc(N * sizeof(int));
            int *dist = (int*) malloc(N * sizeof(int));
            temCaminho = bfs(mat, r, v, N, pai, dist);
            if(temCaminho == 0){
                printf("sem caminho entre %d e %d", r, v);
            } else imprimeCaminho(r - 1, v - 1, pai, 0);
            printf(" (%d pontes)", dist[v-1]);
            free(pai);
            free(dist);
            printf("\n");
        }
        else if(strcmp(operation, "agua") == 0){
            scanf("%d", &nivel);
            printf("\n");
            ponteState(mat, entries, nivel, M, N);
            printf("Nivel da agua: %d m\n", nivel);
        }
        else break;
        char *operation = (char*) malloc(7*sizeof(char));
        printf("\n");
    }
    free(operation);
    free(alturaOriginal);
    for(i = 0; i < M; i++) free(entries[i]);
    for(i = 0; i < N; i++) free(mat[i]);
    return 0;
}
