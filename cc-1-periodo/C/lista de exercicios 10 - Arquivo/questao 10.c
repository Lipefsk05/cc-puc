#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo;
    float numero;
    float soma = 0.0;
    float min = 0.0, max = 0.0;
    int count = 0;

    // Abre o arquivo para leitura
    arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê os números do arquivo e calcula min, max, soma e count
    if (fscanf(arquivo, "%f", &numero) != EOF) {
        min = max = soma = numero;
        count = 1;
    }

    while (fscanf(arquivo, "%f", &numero) != EOF) {
        soma += numero;
        if (numero < min)
            min = numero;
        if (numero > max)
            max = numero;
        count++;
    }

    fclose(arquivo);

    // Calcula a média
    float media = soma / count;

    // Imprime os resultados na tela
    printf("Valor máximo: %.2f\n", max);
    printf("Valor mínimo: %.2f\n", min);
    printf("Média: %.2f\n", media);

    return 0;
}
