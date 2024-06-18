#include <stdio.h>
#include <string.h>

int main() {
    char vetor[100]; // vetor de caracteres
    char *ptr;       // ponteiro para percorrer o vetor
    int tamanho;     // tamanho do vetor de caracteres

    // Solicita ao usuário que digite uma string
    printf("Digite uma string: ");
    fgets(vetor, sizeof(vetor), stdin);

    // Remove o caractere de nova linha inserido pelo fgets
    vetor[strcspn(vetor, "\n")] = '\0';

    // Define o ponteiro ptr para apontar para o final da string
    ptr = vetor + strlen(vetor) - 1;

    printf("String ao contrário: ");
    // Imprime a string ao contrário usando o ponteiro
    while (ptr >= vetor) {
        printf("%c", *ptr);
        ptr--;
    }
    printf("\n");

    return 0;
}
