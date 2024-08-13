#include <stdio.h>

int main() {
    float a, b, x;


    printf("Digite o coeficiente 'a': ");
    scanf("%f", &a);
    printf("Digite o coeficiente 'b': ");
    scanf("%f", &b);


    if (a == 0) {
        if (b == 0) {
            printf("A equacao tem infinitas solucoes.\n");
        } else {
            printf("A equacao nao tem solucao.\n");
        }
    } else {
        x = -b / a;
        printf("A raiz da equacao e: %.2f\n", x);
    }

    return 0;
}
