#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função para remover espaços e pontuações de uma string
void limparString(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!isspace((unsigned char)str[i]) && !ispunct((unsigned char)str[i])) {
            str[j++] = tolower((unsigned char)str[i]);
        }
        i++;
    }
    str[j] = '\0'; // Adiciona o caractere nulo ao final da string
}

// Função para verificar se a string é um palíndromo
int ehPalindromo(char *str) {
    int inicio = 0;
    int fim = strlen(str) - 1;

    while (fim > inicio) {
        if (str[inicio++] != str[fim--]) {
            return 0; // Não é um palíndromo
        }
    }

    return 1; // É um palíndromo
}

int main() {
    char texto[1000];

    printf("Digite uma sequência de caracteres: ");
    fgets(texto, sizeof(texto), stdin);

    // Remover espaços e pontuações
    limparString(texto);

    // Verificar se é um palíndromo
    if (ehPalindromo(texto)) {
        printf("A sequência \"%s\" é um palíndromo.\n", texto);
    } else {
        printf("A sequência \"%s\" não é um palíndromo.\n", texto);
    }

    return 0;
}
