#include <stdio.h>

void exibir_ordem_crescente(int a, int b, int c) {
    int temp;

    if (a > b) { temp = a; a = b; b = temp; }
    if (a > c) { temp = a; a = c; c = temp; }
    if (b > c) { temp = b; b = c; c = temp; }

    printf("Valores em ordem crescente: %d, %d, %d\n", a, b, c);

int main() {
    int N;
    printf("Digite o número de conjuntos: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int val1, val2, val3;
        
        printf("Digite os 3 valores do conjunto %d: ", i + 1);
        scanf("%d %d %d", &val1, &val2, &val3);

        exibir_ordem_crescente(val1, val2, val3);
    }

    return 0;
}
