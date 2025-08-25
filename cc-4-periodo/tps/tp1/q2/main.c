#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Função iterativa para verificar palíndromo ignorando caracteres especiais
bool veresp_iter(char c[]) {
    int i = 0;
    int j = strlen(c) - 1;

    while (i < j) {
        bool esq_special = c[i] < 32 || c[i] > 127;
        bool dir_special = c[j] < 32 || c[j] > 127;

        if (esq_special && dir_special) {
            i++;
            j--;
        } else if (esq_special) {
            i++;
        } else if (dir_special) {
            j--;
        } else {
            if (c[i] != c[j])
                return false;
            i++;
            j--;
        }
    }

    return true;
}

int main() {
    char c[1000];

    fgets(c, sizeof(c), stdin);
    c[strcspn(c, "\n")] = '\0';

    while (strcmp(c, "FIM") != 0) {
        bool n = veresp_iter(c);

        if (n)
            printf("SIM\n");
        else
            printf("NAO\n");

        if (!fgets(c, sizeof(c), stdin)) break; // termina se EOF
        c[strcspn(c, "\n")] = '\0';
    }

    return 0;
}