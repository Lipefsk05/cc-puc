#include <stdio.h>
#include <ctype.h>

int main() {
    int N;
    char letra;
    FILE *arquivo;
    int contador_vogais = 0;

    // Solicita ao usuário a quantidade de letras a serem inseridas
    printf("Digite a quantidade de letras que deseja inserir no arquivo: ");
    scanf("%d", &N);

    // Abre o arquivo para escrita
    arquivo = fopen("letras.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Solicita ao usuário inserir as N letras
    printf("Digite as %d letras, uma por linha:\n", N);
    for (int i = 0; i < N; i++) {
        scanf(" %c", &letra); // Utilizamos " %c" para ignorar espaços e quebras de linha
        fputc(letra, arquivo); // Escreve a letra no arquivo
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Abre o arquivo para leitura
    arquivo = fopen("letras.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 1;
