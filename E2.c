#include <stdio.h>
#include <stdlib.h>

int main(){
    int m, n, i, j;

    scanf("%d %d", &n, &m);

    int grafos[n][n];
    int vertices[m][2];
    int grau[n];

    // zerando a matriz
    for(i=0; i < n; i++){
        for(j=0; j<n; j++){
            grafos[i][j]=0;
        }
    }
    //zerando o vetor de grau
    for(i = 0; i < n; i++){
        grau[i] = 0;
    }

    //capturando as arestas
    for(i=0; i < m; i++){
        scanf("%d %d", &vertices[i][0], &vertices [i][1]);
    }

    //construindo a matriz de adjacencia
    for(i=0; i < m; i++){
        grafos[vertices[i][0]][vertices [i][1]] = 1;
        grafos[vertices[i][1]][vertices [i][0]] = 1;
    }

    //imprimindo a matriz de adjacencia
    for(i=0; i < n; i++){
        for(j=0; j<n; j++){
            printf("%d ", grafos[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //preenchendo o vetor de graus
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(grafos[i][j] == 1){
                grau[j]++;
            }
        }
    }

    //imprimindo o vetor de grau
    for(i = 0; i < n; i++){
        printf("%d ", grau[i]);
    }
    printf("\n");

    return 0;
}