#include <stdio.h>

// Função recursiva para calcular a divisão usando subtrações sucessivas
int divisao(int numerador, int denominador) {
    // Caso base: se o numerador for menor que o denominador, retorna 0
    if (numerador < denominador) {
        return 0;
    }
    // Caso recursivo: subtrai o denominador do numerador e chama recursivamente a função
    return 1 + divisao(numerador - denominador, denominador);
}

int main() {
    int numerador, denominador;

    // Solicita ao usuário inserir o numerador e o denominador
    printf("Digite o numerador: ");
    scanf("%d", &numerador);
    printf("Digite o denominador: ");
    scanf("%d", &denominador);

    // Chama a função para calcular a divisão
    int resultado = divisao(numerador, denominador);

    // Exibe o resultado
    printf("%d / %d = %d\n", numerador, denominador, resultado);

    return 0;
}
