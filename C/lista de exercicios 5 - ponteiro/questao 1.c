#include <stdio.h>

int main() {
    int numero1, numero2;
    int *endereco1, *endereco2;

    // Solicita ao usuário inserir dois números inteiros
    printf("Digite o primeiro número inteiro: ");
    scanf("%d", &numero1);
    printf("Digite o segundo número inteiro: ");
    scanf("%d", &numero2);

    // Obtém os endereços das variáveis
    endereco1 = &numero1;
    endereco2 = &numero2;

    // Compara os endereços e exibe o maior deles
    if (endereco1 > endereco2) {
        printf("O endereço de numero1 é maior: %p\n", (void *)endereco1);
    } else if (endereco2 > endereco1) {
        printf("O endereço de numero2 é maior: %p\n", (void *)endereco2);
    } else {
        printf("Os endereços são iguais: %p\n", (void *)endereco1);
    }

    return 0;
}
