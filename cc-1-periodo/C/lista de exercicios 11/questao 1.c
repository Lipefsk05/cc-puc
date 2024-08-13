#include <stdio.h>

// Função para ordenar um vetor de floats em ordem decrescente
void ordenarDecrescente(float vetor[], int tamanho) {
    int i, j;
    float chave;

    for (i = 1; i < tamanho; i++) {
        chave = vetor[i];
        j = i - 1;

        // Move os elementos do vetor[0..i-1], que são maiores que chave,
        // para uma posição à frente de sua posição atual
        while (j >= 0 && vetor[j] < chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

// Função para imprimir o vetor
void imprimirVetor(float vetor[], int tamanho) {
    printf("[ ");
    for (int i = 0; i < tamanho; i++) {
        printf("%.2f ", vetor[i]);
    }
    printf("]\n");
}

int main() {
    float vetor[] = {3.5, 1.2, 4.8, 2.1, 5.6};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original:\n");
    imprimirVetor(vetor, tamanho);

    // Ordena o vetor em ordem decrescente
    ordenarDecrescente(vetor, tamanho);

    printf("\nVetor ordenado em ordem decrescente:\n");
    imprimirVetor(vetor, tamanho);

    return 0;
}
