#include <stdio.h>

// Função para ordenar três valores inteiros e verificar se são iguais
int ordenaValores(int *a, int *b, int *c) {
    // Ordena os valores usando bubble sort
    int trocou;
    do {
        trocou = 0;
        if (*a > *b) {
            int temp = *a;
            *a = *b;
            *b = temp;
            trocou = 1;
        }
        if (*b > *c) {
            int temp = *b;
            *b = *c;
            *c = temp;
            trocou = 1;
        }
    } while (trocou);

    // Verifica se os três valores são iguais
    if (*a == *b && *b == *c) {
        return 1; // Três valores iguais
    } else {
        return 0; // Valores diferentes
    }
}

int main() {
    int num1, num2, num3;

    // Solicita ao usuário inserir três números inteiros
    printf("Digite o primeiro número inteiro: ");
    scanf("%d", &num1);
    printf("Digite o segundo número inteiro: ");
    scanf("%d", &num2);
    printf("Digite o terceiro número inteiro: ");
    scanf("%d", &num3);

    // Chama a função para ordenar os valores e verificar se são iguais
    int iguais = ordenaValores(&num1, &num2, &num3);

    // Exibe os valores ordenados
    printf("Valores ordenados: %d, %d, %d\n", num1, num2, num3);

    // Exibe se os valores são iguais ou diferentes
    if (iguais) {
        printf("Os três valores são iguais.\n");
    } else {
        printf("Os três valores são diferentes.\n");
    }

    return 0;
}
