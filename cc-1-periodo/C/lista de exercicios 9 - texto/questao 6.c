#include <stdio.h>
#include <string.h>

int main() {
    char palavra[50];

    printf("Digite uma palavra: ");
    scanf("%s", palavra);

    int tamanho = strlen(palavra);

    // Imprime a palavra na diagonal
    for (int i = 0; i < tamanho; i++) {
        // Imprime espaços antes da letra
        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        // Imprime a letra
        printf("%c\n", palavra[i]);
    }

    return 0;
}
