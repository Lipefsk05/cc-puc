#include <stdio.h>

int main() {
    int n;
    float S = 0.0;

    printf("Digite um valor inteiro e positivo para n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("O valor deve ser inteiro e positivo.\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        float termo = 1.0 / i;
        S += termo;
        printf("Termo %d: %.2f\n", i, termo);
    }

    printf("Valor final de S: %.2f\n", S);

    return 0;
}
