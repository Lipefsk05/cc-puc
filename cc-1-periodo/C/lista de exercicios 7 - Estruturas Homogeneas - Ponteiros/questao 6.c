#include <stdio.h>

// Função para calcular a soma dos elementos do vetor usando ponteiro
int calcularSoma(int *vetor, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += *(vetor + i); // Adiciona o valor apontado pelo ponteiro ao total da soma
    }
    return soma;
}

int main() {
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    // Calcular a soma dos elementos do vetor usando ponteiro
    int soma = calcularSoma(vetor, tamanho);

    // Exibir a soma
    printf("A soma de todos os elementos do vetor é: %d\n", soma);

    return 0;
}
