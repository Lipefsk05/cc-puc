#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// Procedimento para preencher a matriz M(10x10)
void preencherMatriz(int M[SIZE][SIZE]) {
    printf("Preenchendo a matriz M(%dx%d):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("M[%d][%d]: ", i, j);
            scanf("%d", &M[i][j]);
        }
    }
}

// Procedimento para exibir a matriz M(10x10)
void exibirMatriz(int M[SIZE][SIZE]) {
    printf("Matriz M(%dx%d):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Procedimento para trocar a linha 2 com a linha 8
void trocarLinhas2e8(int M[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        int temp = M[1][j];
        M[1][j] = M[7][j];
        M[7][j] = temp;
    }
}

// Procedimento para trocar a coluna 4 com a coluna 10
void trocarColunas4e10(int M[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int temp = M[i][3];
        M[i][3] = M[i][9];
        M[i][9] = temp;
    }
}

// Procedimento para trocar a diagonal principal com a diagonal secundária
void trocarDiagonais(int M[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int temp = M[i][i];
        M[i][i] = M[i][SIZE - 1 - i];
        M[i][SIZE - 1 - i] = temp;
    }
}

// Procedimento para trocar a linha 5 com a coluna 10
void trocarLinha5eColuna10(int M[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int temp = M[4][i];
        M[4][i] = M[i][9];
        M[i][9] = temp;
    }
}

int main() {
    int M[SIZE][SIZE];

    // Preencher e exibir a matriz original
    preencherMatriz(M);
    exibirMatriz(M);

    // Trocar a linha 2 com a linha 8 e exibir a matriz resultante
    trocarLinhas2e8(M);
    printf("Após trocar a linha 2 com a linha 8:\n");
    exibirMatriz(M);

    // Trocar a coluna 4 com a coluna 10 e exibir a matriz resultante
    trocarColunas4e10(M);
    printf("Após trocar a coluna 4 com a coluna 10:\n");
    exibirMatriz(M);

    // Trocar a diagonal principal com a diagonal secundária e exibir a matriz resultante
    trocarDiagonais(M);
    printf("Após trocar a diagonal principal com a diagonal secundária:\n");
    exibirMatriz(M);

    // Trocar a linha 5 com a coluna 10 e exibir a matriz resultante
    trocarLinha5eColuna10(M);
    printf("Após trocar a linha 5 com a coluna 10:\n");
    exibirMatriz(M);

    return 0;
}
