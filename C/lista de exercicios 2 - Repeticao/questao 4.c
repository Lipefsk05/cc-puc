#include <stdio.h>


int fatorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * fatorial(n - 1);
    }
}

int main() {
    int N;
    float E = 1.0;

    printf("Digite um valor inteiro e positivo para N: ");
    scanf("%d", &N);

    // Calcula e soma os inversos dos fatoriais de 1 até N
    for (int i = 1; i <= N; i++) {
        E += 1.0 / fatorial(i);
    }

    printf("O valor de E é: %f\n", E);

    return 0;
}
