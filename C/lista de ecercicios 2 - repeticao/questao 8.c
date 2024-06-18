#include <stdio.h>

int main() {
    int L;

    printf("Digite um número limite (L) para a série de Fibonacci: ");
    scanf("%d", &L);

    if (L <= 0) {
        printf("O número limite deve ser maior que zero.\n");
        return 1;
    }

    long long int a = 0, b = 1;
    long long int fibonacci = a;

    printf("Os elementos da série de Fibonacci menores que %d são:\n", L);
    printf("%lld ", fibonacci);

    while (1) {
        fibonacci = a + b;
        if (fibonacci >= L) {
            break;
        }
        printf("%lld ", fibonacci);
        a = b;
        b = fibonacci;
    }
    printf("\n");

    return 0;
}
