#include <stdio.h>
#define PI 3.14159

// Procedimento para calcular o comprimento e a área da circunferência
void calcCircunferencia(float R, float *compr, float *area) {
    *compr = 2 * PI * R;
    *area = PI * R * R;
}

int main() {
    float raio, comprimento, area;

    // Leitura do raio
    printf("Digite o raio da circunferência: ");
    scanf("%f", &raio);

    // Chamada do procedimento para calcular comprimento e área
    calcCircunferencia(raio, &comprimento, &area);

    // Exibição dos resultados
    printf("Comprimento da circunferência: %.2f\n", comprimento);
    printf("Área da circunferência: %.2f\n", area);

    return 0;
}
