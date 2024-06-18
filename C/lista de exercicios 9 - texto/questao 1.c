#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Função para verificar se uma palavra é um conector
int ehConector(char *palavra) {
    char *conectores[] = {"e", "do", "da", "dos", "das", "de", "di", "du"};
    int numConectores = sizeof(conectores) / sizeof(conectores[0]);

    for (int i = 0; i < numConectores; i++) {
        if (strcmp(palavra, conectores[i]) == 0) {
            return 1; // É um conector
        }
    }
    return 0; // Não é um conector
}

// Função para imprimir as iniciais de um nome
void imprimirIniciais(char *nome) {
    int tamanho = strlen(nome);
    int i = 0;
    char iniciais[20]; // Supomos um máximo de 20 iniciais

    // Inicialmente não há nenhuma inicial
    iniciais[0] = '\0';

    while (i < tamanho) {
        // Ignora espaços iniciais
        while (i < tamanho && isspace(nome[i])) {
            i++;
        }

        // Começa a processar a palavra
        int j = i;
        while (j < tamanho && !isspace(nome[j])) {
            j++;
        }

        // Copia a palavra para um buffer temporário
        char palavra[50];
        strncpy(palavra, nome + i, j - i);
        palavra[j - i] = '\0';

        // Verifica se a palavra não é um conector
        if (!ehConector(palavra)) {
            // Transforma a primeira letra em maiúscula
            char inicial = toupper(palavra[0]);
            // Adiciona a inicial ao vetor de iniciais
            int len = strlen(iniciais);
            iniciais[len] = inicial;
            iniciais[len + 1] = '\0';
        }

        // Avança para o próximo espaço
        i = j + 1;
    }

    // Imprime as iniciais
    printf("As iniciais do nome \"%s\" são: %s\n", nome, iniciais);
}

int main() {
    char nome[100];

    printf("Digite um nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remover o caractere de nova linha, se presente

    imprimirIniciais(nome);

    return 0;
}
