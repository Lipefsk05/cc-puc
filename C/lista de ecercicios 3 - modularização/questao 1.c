#include <stdio.h>

void calcular_media(float nota1, float nota2, float nota3, char tipo) {
    float media;
    if (tipo == 'A' || tipo == 'a') {
        media = (nota1 + nota2 + nota3) / 3.0;
        printf("Média aritmética: %.2f\n", media);
    } else if (tipo == 'P' || tipo == 'p') {
        media = (nota1 * 5 + nota2 * 3 + nota3 * 2) / 10.0;
        printf("Média ponderada: %.2f\n", media);
    } else {
        printf("Tipo de média inválido.\n");
    }
}

int main() {
    int N;
    printf("Digite o número de alunos: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        float nota1, nota2, nota3;
        char tipo;

        printf("Digite as 3 notas do aluno %d: ", i + 1);
        scanf("%f %f %f", &nota1, &nota2, &nota3);

        printf("Digite 'A' para média aritmética ou 'P' para média ponderada: ");
        scanf(" %c", &tipo);

        calcular_media(nota1, nota2, nota3, tipo);
    }

    return 0;
}
