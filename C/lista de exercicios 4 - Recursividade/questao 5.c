#include <stdio.h>

// Função recursiva para calcular o valor da série S
double serie(int n) {
    // Caso base: quando n = 1, retorna 1/1! = 1
    if (n == 1) {
        return 1.0;
    }
    // Caso recursivo: calcula o termo 1/n! e soma com a série para n-1
    return 1.0 / fatorial(n) + serie(n - 1);
}

// Função recursiva para calcular o fatorial de um número
int fatorial(int num) {
    // Caso base: fatorial de 0 é 1
    if (num == 0) {
        return 1;
    }
    // Caso recursivo: calcula o fatorial de num
    return num * fatorial(num - 1);
}

int main() {
    int n;

    // Solicita ao usuário inserir um número
    printf("Digite um número inteiro (n > 0): ");
    scanf("%d", &n);

    // Verifica se n é maior que 0
    if (n <= 0) {
        printf("O número precisa ser maior que zero.\n");
        return 1;
    }

    // Chama a função para calcular o valor da série
    double resultado = serie(n);

    // Exibe o resultado
    printf("O valor da série para n = %d é: %lf\n", n, resultado);

    return 0;
}
