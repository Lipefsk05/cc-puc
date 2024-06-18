#include <stdio.h>

double calcular_S(int N) {
    double S = 1.0;    
    double termo = 1.0;
    for (int i = 1; i <= N; i++) {
        termo /= i;
        S += termo;
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
