#include <stdio.h>

int main() {
    float primeiro_termo, razao;
    float decimo_termo;
    int n = 10;  // décimo termo

    // Leitura do primeiro termo da PA
    printf("Digite o primeiro termo da PA: ");
    scanf("%f", &primeiro_termo);

    // Leitura da razão da PA
    printf("Digite a razão da PA: ");
    scanf("%f", &razao);

    // Cálculo do décimo termo da PA
    // Fórmula do n-ésimo termo da PA: an = a1 + (n - 1) * r
    decimo_termo = primeiro_termo + (n - 1) * razao;

    // Exibição do décimo termo
    printf("O décimo termo da PA é: %.2f\n", decimo_termo);

    return 0;
}
