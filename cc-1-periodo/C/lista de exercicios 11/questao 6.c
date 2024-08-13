#include <stdio.h>
#include <stdlib.h>

// Função para multiplicar um vetor por uma matriz
float *multiplicarVetorPorMatriz(float vetor[], float **matriz, int linhas, int colunas) {
    // Alocando dinamicamente o vetor resultado
    float *vetorResultado = (float *)malloc(linhas * sizeof(float));
    if (vetorResultado == NULL) {
        printf("Erro ao alocar vetor resultado.\n");
        return NULL;
    }

    // Calculando o produto vetor * matriz
    for (int i = 0; i < linhas; i++) {
        vetorResultado[i] = 0;
        for (int j = 0; j < colunas; j++) {
            vetorResultado[i] += vetor[j] * matriz[j][i];
        }
    }

    return vetorResultado;
}

// Função para liberar a memória alocada para um vetor
void liberarVetor(float *vetor) {
    if (vetor != NULL) {
        free(vetor);
    }
}

// Função para imprimir um vetor (apenas para verificação)
void imprimirVetor(float vetor[], int tamanho) {
    printf("[ ");
    for (int i = 0; i < tamanho; i++) {
        printf("%.2f ", vetor[i]);
    }
    printf("]\n");
}

// Função para imprimir uma matriz (apenas para verificação)
void imprimirMatriz(float **matriz, int linhas, int colunas) {
    printf("Matriz:\n");
    for (int i = 0; i < colunas; i++) {
        for (int j = 0; j < linhas; j++) {
            printf("%.2f ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int linhas, colunas;

    printf("Digite o número de linhas da matriz: ");
    scanf("%d", &linhas);
    printf("Digite o número de colunas da matriz: ");
    scanf("%d", &colunas);

    // Alocando dinamicamente a matriz
    float **matriz = (float **)malloc(colunas * sizeof(float *));
    if (matriz == NULL) {
        printf("Erro ao alocar matriz (1ª dimensão).\n");
        return 1;
    }

    for (int i = 0; i < colunas; i++) {
        matriz[i] = (float *)malloc(linhas * sizeof(float));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar matriz (2ª dimensão), liberando memória alocada...\n");
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return 1;
        }
    }

    // Preenchendo a matriz com valores de exemplo
    printf("Digite os elementos da matriz:\n");
    for (int i = 0; i < colunas; i++) {
        for (int j = 0; j < linhas; j++) {
            printf("Matriz[%d][%d]: ", i, j);
            scanf("%f", &matriz[i][j]);
        }
    }

    // Alocando dinamicamente o vetor
    float *vetor = (float *)malloc(colunas * sizeof(float));
    if (vetor == NULL) {
        printf("Erro ao alocar vetor.\n");
        // Liberando memória alocada para a matriz
        for (int i = 0; i < colunas; i++) {
            free(matriz[i]);
        }
        free(matriz);
        return 1;
    }

    // Preenchendo o vetor com valores de exemplo
    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < colunas; i++) {
        printf("Vetor[%d]: ", i);
        scanf("%f", &vetor[i]);
    }

    // Multiplicando o vetor pela matriz
    float *vetorResultado = multiplicarVetorPorMatriz(vetor, matriz, linhas, colunas);

    if (vetorResultado != NULL) {
        printf("\nResultado da multiplicação (Vetor * Matriz):\n");
        imprimirVetor(vetorResultado, linhas);

        // Liberando memória alocada
        liberarVetor(vetorResultado);
    }

    // Liberando memória alocada para o vetor e a matriz
    free(vetor);
    for (int i = 0; i < colunas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
