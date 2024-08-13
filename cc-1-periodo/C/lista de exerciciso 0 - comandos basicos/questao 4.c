#include <stdio.h>
#include <math.h>

int main() {
    float raio;
    float perimetro, area;
    const float PI = 3.14159265358979323846;

    // Leitura do raio do círculo
    printf("Digite o raio do círculo: ");
    scanf("%f", &raio);

    // Cálculo do perímetro (circunferência)
    perimetro = 2 * PI * raio;

    // Cálculo da área
    area = PI * raio * raio;

    // Exibição dos resultados
    printf("Perímetro do círculo: %.2f\n", perimetro);
    printf("Área do círculo: %.2f\n", area);

    return 0;
}
