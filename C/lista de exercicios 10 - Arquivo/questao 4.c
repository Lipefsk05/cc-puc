#include <stdio.h>

int main() {
    FILE *arquivo;
    char linha[1000]; // Tamanho máximo da linha
    int contador_linhas = 0;

    // Abre o arquivo para leitura
    arquivo = fopen("texto.txt", "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê e imprime cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
        contador_linhas++;
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Imprime a quantidade de linhas
    printf("\nO arquivo possui %d linhas.\n", contador_linhas);

    return 0;
}
