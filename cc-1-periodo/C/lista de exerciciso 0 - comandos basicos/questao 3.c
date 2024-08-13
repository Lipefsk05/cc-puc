#include <stdio.h>
#include <math.h>

int main() {
    float base, altura;
    float perimetro, area, diagonal;

    // Leitura da base do retângulo
    printf("Digite a base do retângulo: ");
    scanf("%f", &base);

    // Leitura da altura do retângulo
    printf("Digite a altura do retângulo: ");
    scanf("%f", &altura);

    // Cálculo do perímetro
    perimetro = 2 * (base + altura);

    // Cálculo da área
    area = base * altura;

    // Cálculo da diagonal utilizando o teorema de Pitágoras
    diagonal = sqrt((base * base) + (altura * altura));

    // Exibição dos resultados
    printf("Perímetro do retângulo: %.2f\n", perimetro);
    printf("Área do retângulo: %.2f\n", area);
    printf("Diagonal do retângulo: %.2f\n", diagonal);

    return 0;
}
