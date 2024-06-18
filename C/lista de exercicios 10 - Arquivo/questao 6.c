#include <stdio.h>

int main() {
    int numero, divisor, soma_divisores = 0;
    FILE *arquivo;

    // Solicita ao usuário um número
    printf("Digite um número inteiro positivo: ");
    scanf("%d", &numero);

    // Abre o arquivo para escrita
    arquivo = fopen("soma_divisores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Imprime na tela todos os divisores do número e calcula a soma total
    printf("Divisores de %d:\n", numero);
    for (divisor = 1; divisor <= numero; divisor++) {
        if (numero % divisor == 0) {
            printf("%d ", divisor);
            soma_divisores += divisor;
        }
    }

    // Salva a soma total dos divisores no arquivo
    fprintf(arquivo, "Soma total dos divisores de %d: %d\n", numero, soma_divisores);

    // Fecha o arquivo
    fclose(arquivo);

    printf("\nSoma total dos divisores salva no arquivo soma_divisores.txt.\n");

    return 0;
}
