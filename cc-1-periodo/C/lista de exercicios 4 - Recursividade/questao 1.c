#include <stdio.h>

// Função recursiva para contar os dígitos de um número
int contarDigitos(int numero) {
    // Caso base: se o número tiver apenas um dígito
    if (numero == 0) {
        return 0;
    }
    // Caso recursivo: chama a função para o quociente do número por 10
    return 1 + contarDigitos(numero / 10);
}

int main() {
    int numero;

    // Solicita ao usuário inserir um número
    printf("Digite um número inteiro: ");
    scanf("%d", &numero);

    // Chama a função para contar os dígitos
    int numDigitos = contarDigitos(numero);

    // Exibe o resultado
    printf("O número de dígitos de %d é: %d\n", numero, numDigitos);

    return 0;
}
