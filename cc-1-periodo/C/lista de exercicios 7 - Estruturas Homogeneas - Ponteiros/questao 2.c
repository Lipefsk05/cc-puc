#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para trocar dois caracteres em um vetor
void trocar(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Função para imprimir todas as permutações
void imprimirPermutacoes(char *vetor, int inicio, int tamanho) {
    if (inicio == tamanho - 1) {
        printf("%s\n", vetor); // Imprime a permutação atual quando chegamos ao fim
    } else {
        for (int i = inicio; i < tamanho; i++) {
            trocar(&vetor[inicio], &vetor[i]); // Troca os caracteres
            imprimirPermutacoes(vetor, inicio + 1, tamanho); // Chamada recursiva para o restante do vetor
            trocar(&vetor[inicio], &vetor[i]); // Troca de volta para restaurar o vetor original
        }
    }
}

int main() {
    char vetor[] = "abcd"; // Vetor de caracteres para permutar

    int tamanho = strlen(vetor); // Tamanho do vetor

    printf("Permutações do vetor '%s':\n", vetor);
    imprimirPermutacoes(vetor, 0, tamanho);

    return 0;
}
