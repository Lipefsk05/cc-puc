#include <stdio.h>

// Função recursiva para calcular o resto da divisão usando subtrações sucessivas
int resto(int numerador, int denominador) {
    // Caso base: se o numerador for menor que o denominador, retorna o próprio numerador
    if (numerador < denominador) {
        return numerador;
    }
    // Caso recursivo: subtrai o denominador do numerador e chama recursivamente a função
    return resto(numerador - denominador, denominador);
}

int main() {
    int numerador, denominador;

    // Solicita ao usuário inserir o numerador e o denominador
    printf("Digite o numerador: ");
    scanf("%d", &numerador);
    printf("Digite o denominador: ");
    scanf("%d", &denominador);

    // Chama a função para calcular o resto da divisão
    int resultado = resto(numerador, denominador);

    // Exibe o resultado
    printf("Resto de %d / %d = %d\n", numerador, denominador, resultado);

    return 0;
}
