#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    // Solicitar o número de elementos do vetor
    printf("Digite o número de elementos do vetor: ");
    scanf("%d", &n);

    // Alocar memória para o vetor de inteiros
    int *vetor = (int *)malloc(n * sizeof(int));

    // Verificar se a alocação foi bem-sucedida
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return 1;
    }

    // Preencher o vetor com valores informados pelo usuário
    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    // Imprimir os elementos do vetor usando um ponteiro
    printf("Elementos do vetor usando um ponteiro:\n");
    int *ptr = vetor; // Inicializa o ponteiro para apontar para o primeiro elemento do vetor
    for (int i = 0; i < n; i++) {
        printf("%d ", *ptr); // Imprime o valor apontado pelo ponteiro
        ptr++; // Move o ponteiro para apontar para o próximo elemento do vetor
    }
    printf("\n");

    // Liberar a memória alocada para o vetor
    free(vetor);

    return 0;
}
