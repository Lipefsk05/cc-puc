#include <stdio.h>
#include <stdbool.h>

bool verificar_positivo(int num) {
    if (num > 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int N;
    printf("Digite a quantidade de números a serem verificados: ");
    scanf("%d", &N);
    

    int numero;
    
    for (int i = 0; i < N; i++) {
        printf("Digite o %do número: ", i + 1);
        scanf("%d", &numero);
        

        if (verificar_positivo(numero)) {
            printf("%d é um número positivo.\n", numero);
        } else {
            printf("%d não é um número positivo.\n", numero);
        }
    }
    
    return 0;
}
