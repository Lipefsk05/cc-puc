#include <stdio.h>

void verificar_triangulo(float x, float y, float z) {

    if ((x < y + z) && (y < x + z) && (z < x + y)) {

        if (x == y && y == z) {
            printf("Triângulo Equilátero\n");
        } else if (x == y || x == z || y == z) {
            printf("Triângulo Isósceles\n");
        } else {
            printf("Triângulo Escaleno\n");
        }
    } else {
        printf("Os valores não formam um triângulo\n");
    }
}

int main() {
    float x, y, z;
    char continuar;

    do {

        printf("Informe os comprimentos dos lados do triângulo (X Y Z): ");
        scanf("%f %f %f", &x, &y, &z);

        verificar_triangulo(x, y, z);

        printf("Deseja verificar outro triângulo? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return 0;
}
