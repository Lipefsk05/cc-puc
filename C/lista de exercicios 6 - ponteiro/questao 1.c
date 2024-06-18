#include <stdio.h>

#define TAMANHO_TURMA 10

// Procedimento para preencher o vetor de notas
void preencherNotas(float notas[]) {
    printf("Digite as notas dos %d alunos:\n", TAMANHO_TURMA);
    for (int i = 0; i < TAMANHO_TURMA; ++i) {
        printf("Nota do aluno %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

// Procedimento para calcular média e contar notas acima da média
void calcularMediaEContarAcima(float notas[]) {
    float soma = 0;
    float media;
    int acimaMedia = 0;

    // Calcula a soma das notas
    for (int i = 0; i < TAMANHO_TURMA; ++i) {
        soma += notas[i];
    }

    // Calcula a média
    media = soma / TAMANHO_TURMA;

    // Conta quantas notas estão acima da média
    for (int i = 0; i < TAMANHO_TURMA; ++i) {
        if (notas[i] > media) {
            acimaMedia++;
        }
    }

    // Exibe a média e o número de notas acima da média
    printf("\nMédia da turma: %.2f\n", media);
    printf("Alunos com nota acima da média: %d\n", acimaMedia);
}

int main() {
    float notas[TAMANHO_TURMA];

    // Preenche o vetor de notas
    preencherNotas(notas);

    // Calcula a média e conta quantos alunos estão acima da média
    calcularMediaEContarAcima(notas);

    return 0;
}
