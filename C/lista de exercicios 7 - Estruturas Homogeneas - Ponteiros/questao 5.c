#include <stdio.h>

// Função para trocar dois elementos de um vetor
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ordenar o vetor usando Bubble Sort
void ordenarVetor(int *vetor, int tamanho) {
    int i, j;
    for (i = 0; i < tamanho-1; i++) {
        // Últimos i elementos já estão ordenados, não precisamos mais verificar
        for (j = 0; j < tamanho-i-1; j++) {
            // Troca os elementos se estiverem na ordem errada
            if (*(vetor+j) > *(vetor+j+1)) {
                trocar(vetor+j, vetor+j+1);
            }
        }
    }
}

// Função para imprimir o vetor
void imprimirVetor(int *vetor, int tamanho) {
    printf("Vetor ordenado:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", *(vetor+i));
    }
    printf("\n");
}

int main() {
    int vetor[] = {64, 34, 25, 12, 22, 11, 90};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    // Ordenar o vetor usando ponteiros
    ordenarVetor(vetor, tamanho);

    // Imprimir o vetor ordenado
    imprimirVetor(vetor, tamanho);

    return 0;
}
