#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// Função para preencher a matriz M 5x5
void preencherMatriz(int M[SIZE][SIZE]) {
    printf("Preenchendo a matriz %dx%d:\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("M[%d][%d]: ", i, j);
            scanf("%d", &M[i][j]);
        }
    }
}

// Função para calcular a soma da linha 4 da matriz
int somaLinha4(int M[SIZE][SIZE]) {
    int soma = 0;
    for (int j = 0; j < SIZE; j++) {
        soma += M[4][j];
    }
    return soma;
}

// Função para calcular a soma da coluna 2 da matriz
int somaColuna2(int M[SIZE][SIZE]) {
    int soma = 0;
    for (int i = 0; i < SIZE; i++) {
        soma += M[i][2];
    }
    return soma;
}

// Função para calcular a soma da diagonal principal da matriz
int somaDiagonalPrincipal(int M[SIZE][SIZE]) {
    int soma = 0;
    for (int i = 0; i < SIZE; i++) {
        soma += M[i][i];
    }
    return soma;
}

// Função para calcular a soma da diagonal secundária da matriz
int somaDiagonalSecundaria(int M[SIZE][SIZE]) {
    int soma = 0;
    for (int i = 0; i < SIZE; i++) {
        soma += M[i][SIZE - 1 - i];
    }
    return soma;
}

// Função para calcular a soma de todos os elementos da matriz
int somaTodosElementos(int M[SIZE][SIZE]) {
    int soma = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            soma += M[i][j];
        }
    }
    return soma;
}

int main() {
    int M[SIZE][SIZE];

    // Preencher a matriz
    preencherMatriz(M);

    // Calcular e exibir as somas
    printf("\nSomas:\n");
    printf("a) Soma da linha 4: %d\n", somaLinha4(M));
    printf("b) Soma da coluna 2: %d\n", somaColuna2(M));
    printf("c) Soma da diagonal principal: %d\n", somaDiagonalPrincipal(M));
    printf("d) Soma da diagonal secundária: %d\n", somaDiagonalSecundaria(M));
    printf("e) Soma de todos os elementos: %d\n", somaTodosElementos(M));

    return 0;
}
