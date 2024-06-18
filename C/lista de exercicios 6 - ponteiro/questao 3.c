#include <stdio.h>

#define TAMANHO_VETOR 10

// Procedimento para preencher dois vetores X e Y com 10 elementos cada
void preencherVetores(int vetorX[], int vetorY[]) {
    printf("Preenchendo o vetor X:\n");
    for (int i = 0; i < TAMANHO_VETOR; ++i) {
        printf("Digite o elemento %d: ", i + 1);
        scanf("%d", &vetorX[i]);
    }

    printf("\nPreenchendo o vetor Y:\n");
    for (int i = 0; i < TAMANHO_VETOR; ++i) {
        printf("Digite o elemento %d: ", i + 1);
        scanf("%d", &vetorY[i]);
    }
}

// Procedimento para intercalar os elementos dos vetores X e Y em um novo vetor
void intercalarVetores(int vetorX[], int vetorY[], int vetorIntercalado[]) {
    for (int i = 0; i < TAMANHO_VETOR; ++i) {
        vetorIntercalado[2 * i] = vetorY[i];     // Posições pares com elementos do vetor Y
        vetorIntercalado[2 * i + 1] = vetorX[i]; // Posições ímpares com elementos do vetor X
    }
}

// Procedimento para exibir o conteúdo de um vetor
void exibirVetor(int vetor[], int tamanho) {
    printf("Conteúdo do vetor:\n");
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int vetorX[TAMANHO_VETOR];
    int vetorY[TAMANHO_VETOR];
    int vetorIntercalado[2 * TAMANHO_VETOR]; // Tamanho será 20

    // Preenche os vetores X e Y
    preencherVetores(vetorX, vetorY);

    // Intercala os elementos dos vetores X e Y no vetor intercalado
    intercalarVetores(vetorX, vetorY, vetorIntercalado);

    // Exibe o vetor intercalado
    printf("\nVetor intercalado:\n");
    exibirVetor(vetorIntercalado, 2 * TAMANHO_VETOR);

    return 0;
}
