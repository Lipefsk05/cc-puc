#include <stdio.h>

int main() {
    char string[1000];
    int i;

    printf("Digite uma cadeia de caracteres: ");
    fgets(string, sizeof(string), stdin);

    for (i = 0; string[i] != '\0'; i++) {
        // Converte apenas caracteres minúsculos
        if (string[i] >= 'a' && string[i] <= 'z') {
            string[i] = string[i] - 32; // Subtrai 32 para converter para maiúscula
        }
    }

    printf("A cadeia de caracteres em maiúscula é: %s", string);

    return 0;
}
