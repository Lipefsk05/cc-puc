#include <stdio.h>

int main() {
    int numeros[10];
    int divisivelPor3e9 = 0, divisivelPor2e5 = 0;

    printf("Digite dez números:\n");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &numeros[i]);
    }

    for (int i = 0; i < 10; i++) {
        if (numeros[i] % 3 == 0 && numeros[i] % 9 == 0) {
            printf("%d é divisível por 3 e 9.\n", numeros[i]);
            divisivelPor3e9++;
        } else if (numeros[i] % 2 == 0 && numeros[i] % 5 == 0) {
            printf("%d é divisível por 2 e 5.\n", numeros[i]);
            divisivelPor2e5++;
        } else {
            printf("%d não é divisível pelos valores.\n", numeros[i]);
        }
    }

    printf("\nQuantidade de números divisíveis por 3 e 9: %d\n", divisivelPor3e9);
    printf("Quantidade de números divisíveis por 2 e 5: %d\n", divisivelPor2e5);

    return 0;
}
