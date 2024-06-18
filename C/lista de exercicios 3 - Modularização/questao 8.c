#include <stdio.h>

double calcular_S(int N) {
    double S = 0.0;
    int numerador = 2;
    
    for (int n = 4; n <= N + 3; n++) {
        S += (double)(numerador) / (double)(n);
        numerador += n;
    }
    
    return S;
}

int main() {
    int N;
    printf("Digite um valor inteiro e positivo N: ");
    scanf("%d", &N);
    
    if (N <= 0) {
        printf("N precisa ser um valor inteiro e positivo.\n");
        return 1;
    }
    
    double resultado = calcular_S(N);
    printf("O valor de S para N = %d é: %.6lf\n", N, resultado);
    
    return 0;
}
