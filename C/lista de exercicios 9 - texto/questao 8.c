#include <stdio.h>
#include <ctype.h>

// Função para codificar a mensagem usando o Código de César
void codificarCesar(char *mensagem, int deslocamento) {
    int i = 0;

    while (mensagem[i] != '\0') {
        if (isalpha(mensagem[i])) { // Verifica se é uma letra do alfabeto
            char base = isupper(mensagem[i]) ? 'A' : 'a'; // Base dependendo se é maiúscula ou minúscula
            mensagem[i] = (mensagem[i] - base + deslocamento) % 26 + base;
        }
        i++;
    }
}

int main() {
    char mensagem[1000];

    // Lê a mensagem de entrada
    printf("Digite uma mensagem para codificar usando o Código de César (deslocamento de 3 posições):\n");
    fgets(mensagem, sizeof(mensagem), stdin);

    // Codifica a mensagem usando Código de César com deslocamento de 3 posições
    codificarCesar(mensagem, 3);

    // Imprime a mensagem codificada
    printf("Mensagem codificada: %s", mensagem);

    return 0;
}
