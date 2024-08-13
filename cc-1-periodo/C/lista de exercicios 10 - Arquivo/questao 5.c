#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo1, *arquivo2, *arquivo_destino;
    char caracter;
    char nome_arquivo1[] = "arquivo1.txt";
    char nome_arquivo2[] = "arquivo2.txt";
    char nome_arquivo_destino[] = "arquivo_destino.txt";

    // Abre o primeiro arquivo para leitura
    arquivo1 = fopen(nome_arquivo1, "r");
    if (arquivo1 == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo1);
        return 1;
    }

    // Abre o segundo arquivo para leitura
    arquivo2 = fopen(nome_arquivo2, "r");
    if (arquivo2 == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo2);
        fclose(arquivo1);
        return 1;
    }

    // Abre o arquivo destino para escrita
    arquivo_destino = fopen(nome_arquivo_destino, "w");
    if (arquivo_destino == NULL) {
        printf("Erro ao abrir o arquivo destino %s.\n", nome_arquivo_destino);
        fclose(arquivo1);
        fclose(arquivo2);
        return 1;
    }

    // Copia o conteúdo do primeiro arquivo para o arquivo destino
    while ((caracter = fgetc(arquivo1)) != EOF) {
        fputc(caracter, arquivo_destino);
    }

    // Copia o conteúdo do segundo arquivo para o arquivo destino
    while ((caracter = fgetc(arquivo2)) != EOF) {
        fputc(caracter, arquivo_destino);
    }

    // Fecha todos os arquivos
    fclose(arquivo1);
    fclose(arquivo2);
    fclose(arquivo_destino);

    printf("Conteúdo dos arquivos %s e %s foi concatenado em %s.\n", nome_arquivo1, nome_arquivo2, nome_arquivo_destino);

    return 0;
}
