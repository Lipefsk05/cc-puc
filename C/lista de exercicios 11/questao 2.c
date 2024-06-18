#include <stdio.h>
#include <string.h>

// Função para inverter uma string
void inverterString(char str[]) {
    int inicio = 0;
    int fim = strlen(str) - 1;
    char temp;

    while (inicio < fim) {
        // Troca os caracteres
        temp = str[inicio];
        str[inicio] = str[fim];
        str[fim] = temp;

        // Avança o início e retrocede o fim
        inicio++;
        fim--;
    }
}

int main() {
    char string[] = "Hello, World!";
    
    printf("String original: %s\n", string);
    
    // Inverte a string
    inverterString(string);
    
    printf("String invertida: %s\n", string);
    
    return 0;
}
