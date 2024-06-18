#include <stdio.h>

int main() {
    int valorInt;
    float valorReal;
    char caractere;

    int *ptrInt = &valorInt;
    float *ptrReal = &valorReal;
    char *ptrChar = &caractere;

    printf("Endereço de valorInt: %p, Conteúdo de valorInt: %d\n", (void *)&valorInt, valorInt);
    printf("Endereço de valorReal: %p, Conteúdo de valorReal: %.2f\n", (void *)&valorReal, valorReal);
    printf("Endereço de caractere: %p, Conteúdo de caractere: %c\n", (void *)&caractere, caractere);

    printf("\nDigite um novo valor inteiro: ");
    scanf("%d", &valorInt);
    printf("Digite um novo valor real: ");
    scanf("%f", &valorReal);
    printf("Digite um novo caractere: ");
    scanf(" %c", &caractere);  // %c precisa de um espaço antes para ignorar o '\n' do buffer

    printf("\nApós a modificação:\n");
    printf("Endereço de valorInt: %p, Conteúdo de valorInt: %d\n", (void *)&valorInt, valorInt);
    printf("Endereço de valorReal: %p, Conteúdo de valorReal: %.2f\n", (void *)&valorReal, valorReal);
    printf("Endereço de caractere: %p, Conteúdo de caractere: %c\n", (void *)&caractere, caractere);

    printf("\nEndereço de ptrInt: %p, Conteúdo de ptrInt: %p\n", (void *)&ptrInt, (void *)ptrInt);
    printf("Endereço de ptrReal: %p, Conteúdo de ptrReal: %p\n", (void *)&ptrReal, (void *)ptrReal);
    printf("Endereço de ptrChar: %p, Conteúdo de ptrChar: %p\n", (void *)&ptrChar, (void *)ptrChar);

    return 0;
}
