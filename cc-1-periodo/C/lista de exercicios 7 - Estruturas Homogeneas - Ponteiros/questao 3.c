#include <stdio.h>
#include <stdlib.h>

// Função para encontrar o maior elemento em um vetor
int encontrarMaiorElemento(int *vetor, int tamanho) {
    int maior = vetor[0]; // Assumimos que o primeiro elemento é o maior inicialmente

    // Percorre o vetor para encontrar o maior elemento
    for (int i = 1; i < tamanho; i++) {
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }

    return maior;
}

int main() {
    int *vetor;
    int tamanho;

    // Solicitar o tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);

    // Alocar memória para o vetor de inteiros
    vetor = (int *)malloc(tamanho * sizeof(int));

    // Verificar se a alocação foi bem-sucedida
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return 1;
    }

    // Preencher o vetor com valores informados pelo usuário
    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }

    // Encontrar o maior elemento no vetor
    int maior = encontrarMaiorElemento(vetor, tamanho);

    // Imprimir o maior elemento encontrado
    printf("O maior elemento do vetor é: %d\n", maior);

    // Liberar a memória alocada para o vetor
    free(vetor);

    return 0;
}
