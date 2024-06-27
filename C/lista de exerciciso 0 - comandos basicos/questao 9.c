#include <stdio.h>

int main() {
    int numerador, denominador;
    float decimal;

    // Leitura do numerador e denominador da fração
    printf("Digite o numerador da fração: ");
    scanf("%d", &numerador);

    printf("Digite o denominador da fração: ");
    scanf("%d", &denominador);

    // Verificação para evitar divisão por zero
    if (denominador == 0) {
        printf("Erro: O denominador não pode ser zero.\n");
        return 1; // Sai do programa com erro
    }

    // Cálculo do número decimal
    decimal = (float) numerador / denominador;

    // Exibição do resultado
    printf("O valor decimal da fração %d/%d é: %.2f\n", numerador, denominador, decimal);

    return 0;
}
