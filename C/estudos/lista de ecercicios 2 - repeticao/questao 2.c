#include <stdio.h>

int main() {
    int num, total = 0, positivos = 0, negativos = 0, zeros = 0;

    printf("Digite uma sequência de valores inteiros (separados por espaço): ");


    while (scanf("%d", &num) == 1) {
        total++;
        if (num > 0) {
            positivos++;
        } else if (num < 0) {
            negativos++;
        } else {
            zeros++;
        }
    }

    printf("Quantidade de números positivos: %d (%.2f%%)\n", positivos, (float)positivos / total * 100);
    printf("Quantidade de números negativos: %d (%.2f%%)\n", negativos, (float)negativos / total * 100);
    printf("Quantidade de zeros: %d (%.2f%%)\n", zeros, (float)zeros / total * 100);

    return 0;
}
