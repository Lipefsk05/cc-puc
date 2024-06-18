#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 6

// Procedimento para preencher a matriz A
void preencherMatrizA(int A[ROWS][COLS]) {
    printf("Preenchendo a matriz A %dx%d:\n", ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }
}

// Procedimento para preencher a matriz B
void preencherMatrizB(int B[ROWS][COLS]) {
    printf("Preenchendo a matriz B %dx%d:\n", ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }
}

// Função para calcular a matriz S (Soma de A e B)
void somaMatrizes(int A[ROWS][COLS], int B[ROWS][COLS], int S[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            S[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Função para calcular a matriz D (Diferença A - B)
void diferencaMatrizes(int A[ROWS][COLS], int B[ROWS][COLS], int D[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            D[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Procedimento para exibir uma matriz
void exibirMatriz(int matriz[ROWS][COLS], char nome[]) {
    printf("Matriz %s:\n", nome);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int A[ROWS][COLS], B[ROWS][COLS];
    int S[ROWS][COLS], D[ROWS][COLS];

    // Preencher as matrizes A e B
    preencherMatrizA(A);
    preencherMatrizB(B);

    // Calcular a matriz S (Soma de A e B)
    somaMatrizes(A, B, S);

    // Calcular a matriz D (Diferença A - B)
    diferencaMatrizes(A, B, D);

    // Exibir as matrizes resultantes
    exibirMatriz(S, "S (A + B)");
    exibirMatriz(D, "D (A - B)");

    return 0;
}
