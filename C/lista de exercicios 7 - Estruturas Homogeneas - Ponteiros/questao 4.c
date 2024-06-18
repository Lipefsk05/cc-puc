#include <stdio.h>
#include <ctype.h> // Para usar as funções isalpha e tolower

// Função para contar o número de vogais e consoantes em uma string
void contarVogaisConsoantes(char *str, int *vogais, int *consoantes) {
    while (*str != '\0') {
        if (isalpha(*str)) { // Verifica se o caractere é uma letra
            // Converte o caractere para minúsculo
            char letra = tolower(*str);
            
            // Verifica se é vogal
            if (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u') {
                (*vogais)++;
            } else {
                (*consoantes)++;
            }
        }
        str++; // Move o ponteiro para o próximo caractere
    }
}

int main() {
    char str[100]; // Vetor de caracteres para armazenar a string
    int vogais = 0, consoantes = 0;

    // Solicitar a string ao usuário
    printf("Digite uma string: ");
    fgets(str, sizeof(str), stdin);

    // Contar o número de vogais e consoantes usando um ponteiro
    contarVogaisConsoantes(str, &vogais, &consoantes);

    // Exibir o resultado
    printf("Número de vogais: %d\n", vogais);
    printf("Número de consoantes: %d\n", consoantes);

    return 0;
}
