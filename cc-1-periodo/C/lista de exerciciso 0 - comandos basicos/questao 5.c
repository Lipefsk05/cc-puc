#include <stdio.h>
#include <math.h>

int main() {
    float cateto1, cateto2, hipotenusa;

    // Leitura dos valores dos catetos
    printf("Digite o valor do primeiro cateto: ");
    scanf("%f", &cateto1);

    printf("Digite o valor do segundo cateto: ");
    scanf("%f", &cateto2);

    // Cálculo da hipotenusa utilizando o teorema de Pitágoras
    hipotenusa = sqrt((cateto1 * cateto1) + (cateto2 * cateto2));

    // Exibição da hipotenusa
    printf("O valor da hipotenusa é: %.2f\n", hipotenusa);

    return 0;
}
