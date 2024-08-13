#include <stdio.h>

int main() {
    FILE *arquivo;
    char caractere;
    int contador_a = 0;

    // Abre o arquivo para leitura
    arquivo = fopen("texto.txt", "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê o arquivo caractere por caractere
    while ((caractere = fgetc(arquivo)) != EOF) {
        if (caractere == 'a' || caractere == 'A') {
            contador_a++;
        }
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Imprime a quantidade de caracteres 'a'
    printf("Quantidade de caracteres 'a' no arquivo: %d\n", contador_a);

    return 0;
}
