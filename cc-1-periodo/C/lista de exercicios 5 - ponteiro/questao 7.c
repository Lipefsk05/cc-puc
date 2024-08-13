#include <stdio.h>

// Função para encontrar o maior e o menor valor entre dois inteiros
void maiorMenor(int *a, int *b) {
    if (*a < *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

int main() {
    int num1, num2;

    // Solicita ao usuário inserir dois números inteiros
    printf("Digite o primeiro número inteiro: ");
    scanf("%d", &num1);
    printf("Digite o segundo número inteiro: ");
    scanf("%d", &num2);

    // Chama a função para encontrar o maior e o menor valor
    maiorMenor(&num1, &num2);

    // Exibe os valores modificados
    printf("Maior valor: %d\n", num1);
    printf("Menor valor: %d\n", num2);

    return 0;
}
