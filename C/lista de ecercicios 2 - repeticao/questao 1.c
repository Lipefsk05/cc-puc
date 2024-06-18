#include <stdio.h>

int main() {
    int num, positivos = 0, negativos = 0, zeros = 0;

    printf("Digite uma sequência de valores inteiros (separados por espaço): ");


    while (scanf("%d", &num) == 1) {
        if (num > 0) {
            positivos++;
        } else if (num < 0) {
            negativos++;
        } else {
            zeros++;
        }
    }

    printf("Quantidade de números positivos: %d\n", positivos);
    printf("Quantidade de números negativos: %d\n", negativos);
    printf("Quantidade de zeros: %d\n", zeros);

    return 0;
}
