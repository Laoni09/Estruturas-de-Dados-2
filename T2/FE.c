#include <stdio.h>
#include <stdlib.h>
#include "FE.h"

Fila *cria_fila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = 0;
    return f;
}

void fila_push(Fila *f, int x) {
    f->v[ f->fim ] = x;
    f->fim = (f->fim+1)%MAX;
}

int fila_pop(Fila *f) {
    int x = f->v[ f->ini ];
    f->ini = (f->ini + 1)%MAX;
    return x;
}

int vazia(Fila *f) {
    return f->ini == f->fim ? 1 : 0;
}

void freeFila(Fila *f){
    free(f);
}
