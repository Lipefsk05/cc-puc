#include <stdio.h>
#include <ctype.h>

void removeEspacosExtras(char *texto) {
    int i = 0; // Índice para percorrer o texto original
    int j = 0; // Índice para construir o texto resultante

    // Variável para indicar se o próximo caractere deve ser um espaço
    int deveSerEspaco = 0;

    while (texto[i] != '\0') {
        if (isspace(texto[i])) {
            if (!deveSerEspaco) {
                // Adiciona um espaço apenas se não for necessário outro espaço
                texto[j] = ' ';
                j++;
            }
            deveSerEspaco = 1; // Próximo caractere deve ser um espaço
        } else {
            texto[j] = texto[i];
            j++;
            deveSerEspaco = 0; // Próximo caractere não precisa ser um espaço
        }
        i++;
    }

    // Adiciona o caractere nulo ao final do texto resultante
    texto[j] = '\0';
}

int main() {
    char texto[1000];

    printf("Digite um texto:\n");
    fgets(texto, sizeof(texto), stdin);

    // Remove os espaços extras
    removeEspacosExtras(texto);

    // Imprime o texto resultante
    printf("Texto com espaços reduzidos:\n%s\n", texto);

    return 0;
}
