#include <stdio.h>

int main() {
    FILE *arquivo;
    int i;

    // Abre o arquivo para escrita
    arquivo = fopen("numeros.txt", "w");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Escreve os números de 1 até 10 no arquivo, um por linha
    for (i = 1; i <= 10; i++) {
        fprintf(arquivo, "%d\n", i);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Os números de 1 a 10 foram escritos no arquivo 'numeros.txt'.\n");

    return 0;
}
