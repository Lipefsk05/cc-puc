#include <stdio.h>

// Função recursiva para encontrar a soma dos dígitos de um número
int somaDigitos(int numero) {
    // Caso base: se o número tiver apenas um dígito
    if (numero == 0) {
        return 0;
    }
    // Caso recursivo: retorna o último dígito somado ao restante dos dígitos
    return (numero % 10) + somaDigitos(numero / 10);
}

int main() {
    int numero;

    // Solicita ao usuário inserir um número
    printf("Digite um número inteiro: ");
    scanf("%d", &numero);

    // Chama a função para encontrar a soma dos dígitos
    int soma = somaDigitos(numero);

    // Exibe o resultado
    printf("A soma dos dígitos de %d é: %d\n", numero, soma);

    return 0;
}
