#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo;
    char texto[1000];

    // Solicita ao usuário que digite um texto
    printf("Digite um texto para ser gravado no arquivo:\n");
    fgets(texto, sizeof(texto), stdin);

    // Abre o arquivo para escrita
    arquivo = fopen("texto.txt", "w");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Grava o texto fornecido pelo usuário no arquivo
    fprintf(arquivo, "%s", texto);

    // Fecha o arquivo
    fclose(arquivo);

    printf("O texto foi gravado no arquivo 'texto.txt'.\n");

    return 0;
}
