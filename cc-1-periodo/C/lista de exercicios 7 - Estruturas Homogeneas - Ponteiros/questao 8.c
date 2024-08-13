#include <stdio.h>

int main() {
    char letra = 'A';
    char *ptr = &letra;

    printf("Letras do alfabeto maiúsculo usando ponteiro:\n");

    // Imprime todas as letras maiúsculas
    for (; *ptr <= 'Z'; (*ptr)++) {
        printf("%c ", *ptr);
    }
    printf("\n");

    return 0;
}
