#include <stdio.h>
#include <stdlib.h>

#define SIZE 4

// Função para preencher a matriz 4x4
void preencherMatriz(int M[SIZE][SIZE]) {
    printf("Preenchendo a matriz %dx%d:\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("M[%d][%d]: ", i, j);
            scanf("%d", &M[i][j]);
        }
    }
}

// Função para calcular a soma dos elementos abaixo da diagonal principal
int somaElementosAbaixoDiagonal(int M[SIZE][SIZE]) {
    int soma = 0;
    for (int i = 1; i < SIZE; i++) {
        for (int j = 0; j < i; j++) {
            soma += M[i][j];
        }
    }
    return soma;
}

// Função para mostrar os elementos da diagonal principal
void mostrarDiagonalPrincipal(int M[SIZE][SIZE]) {
    printf("Elementos da diagonal principal:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", M[i][i]);
    }
    printf("\n");
}

int main() {
    int M[SIZE][SIZE];

    // Preencher a matriz
    preencherMatriz(M);

    // Mostrar os elementos da diagonal principal
    mostrarDiagonalPrincipal(M);

    // Calcular e mostrar a soma dos elementos abaixo da diagonal principal
    int soma = somaElementosAbaixoDiagonal(M);
    printf("Soma dos elementos abaixo da diagonal principal: %d\n", soma);

    return 0;
}
