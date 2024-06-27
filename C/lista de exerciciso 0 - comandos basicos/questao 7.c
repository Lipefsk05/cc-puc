Ler a razão e o primeiro termo de uma PG e mostrar o seu quinto termo#include <stdio.h>
#include <math.h>

int main() {
    float primeiro_termo, razao;
    float quinto_termo;
    int n = 5;  // quinto termo

    // Leitura do primeiro termo da PG
    printf("Digite o primeiro termo da PG: ");
    scanf("%f", &primeiro_termo);

    // Leitura da razao da PG
    printf("Digite a razao da PG: ");
    scanf("%f", &razao);

    // Calculo do quinto termo da PG
    quinto_termo = primeiro_termo * pow(razao, n - 1);

    // Exibicao do quinto termo
    printf("O quinto termo da PG é: %.2f\n", quinto_termo);

    return 0;
}
