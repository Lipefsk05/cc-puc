#include <stdio.h>

void exibir_conceito(float media) {
    if (media <= 39) {
        printf("Conceito: F\n");
    } else if (media <= 59) {
        printf("Conceito: E\n");
    } else if (media <= 69) {
        printf("Conceito: D\n");
    } else if (media <= 79) {
        printf("Conceito: C\n");
    } else if (media <= 89) {
        printf("Conceito: B\n");
    } else {
        printf("Conceito: A\n");
    }
}

int main() {
    int N;
    printf("Informe a quantidade de alunos: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        float media;
        printf("Informe a média do aluno %d: ", i + 1);
        scanf("%f", &media);
        exibir_conceito(media);
    }

    return 0;
}
