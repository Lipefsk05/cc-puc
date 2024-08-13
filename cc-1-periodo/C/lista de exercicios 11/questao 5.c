#include <stdio.h>
#include <stdlib.h>

// Função para alocar dinamicamente uma matriz com elementos zerados
int **alocarMatriz(int linhas, int colunas) {
    int **matriz;
    int i, j;

    // Alocando o array de ponteiros para as linhas da matriz
    matriz = (int **)malloc(linhas * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro ao alocar matriz (1ª dimensão).\n");
        return NULL;
    }

    // Alocando cada linha da matriz
    for (i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar matriz (2ª dimensão), liberando memória alocada...\n");
            // Liberar todas as linhas já alocadas
            for (j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
        
        // Inicializando a linha com zeros
        for (j = 0; j < colunas; j++) {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

// Função para liberar a memória alocada para a matriz
void liberarMatriz(int **matriz, int linhas) {
    if (matriz == NULL) {
        return;
    }

    // Liberando cada linha da matriz
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }

    // Liberando o array de ponteiros para as linhas
    free(matriz);
}

// Função para imprimir a matriz (apenas para verificação)
void imprimirMatriz(int **matriz, int linhas, int colunas) {
    printf("Matriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int linhas, colunas;
    int **matriz;

    printf("Digite o número de linhas da matriz: ");
    scanf("%d", &linhas);
    printf("Digite o número de colunas da matriz: ");
    scanf("%d", &colunas);

    // Alocando dinamicamente a matriz
    matriz = alocarMatriz(linhas, colunas);

    if (matriz != NULL) {
        printf("Matriz alocada com sucesso:\n");
        imprimirMatriz(matriz, linhas, colunas);

        // Liberando a memória alocada
        liberarMatriz(matriz, linhas);
    }

    return 0;
}
