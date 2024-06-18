#include <stdio.h>

int main() {
    int L;

    printf("Digite o número de elementos da série de Fibonacci que deseja imprimir: ");
    scanf("%d", &L);

    if (L <= 0) {
        printf("O número deve ser maior que zero.\n");
        return 1;
    }

    long long int fibonacci[L];

    fibonacci[0] = 0;
    if (L > 1) {
        fibonacci[1] = 1;
    }

    for (int i = 2; i < L; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }

    printf("Os primeiros %d elementos da série de Fibonacci são:\n", L);
    for (int i = 0; i < L; i++) {
        printf("%lld ", fibonacci[i]);
    }
    printf("\n");

    return 0;
}
