#include <stdio.h>

int main() {
    float A, B, temp;

    // Leitura dos dois números reais
    printf("Digite o valor de A: ");
    scanf("%f", &A);

    printf("Digite o valor de B: ");
    scanf("%f", &B);

    // Troca dos valores usando uma variável temporária
    temp = A;
    A = B;
    B = temp;

    // Exibição dos valores finais
    printf("Valores finais:\n");
    printf("A: %.2f\n", A);
    printf("B: %.2f\n", B);

    return 0;
}
