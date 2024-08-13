#include <stdio.h>

// Função para imprimir os elementos do vetor na ordem inversa
void imprimirInverso(int vetor[], int tamanho) {
    printf("Vetor na ordem inversa:\n");
    for (int i = tamanho - 1; i >= 0; i--) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    // Imprimir os elementos do vetor na ordem inversa
    imprimirInverso(vetor, tamanho);

    return 0;
}
