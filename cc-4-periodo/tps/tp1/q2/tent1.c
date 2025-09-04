#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool pali(char c[], int i, int j) {
    if (i >= j) return true; 

    bool esq = c[i] < 32 || c[i] > 127;
    bool dir = c[j] < 32 || c[j] > 127;

    if (esq && dir)
        return pali(c, i + 1, j - 1);
    else if (esq)
        return pali(c, i + 1, j); 
    else if (dir)
        return pali(c, i, j - 1); 
    else if (c[i] != c[j])
        return false; 
    else
        return pali(c, i + 1, j - 1); 
}

int main() {
    char c[1000];

    fgets(c, sizeof(c), stdin);
    c[strcspn(c, "\n")] = '\0';

    while (strcmp(c, "FIM") != 0) {
        bool n = pali(c, 0, strlen(c) - 1);

        if (n)
            printf("SIM\n");
        else
            printf("NAO\n");

        if (!fgets(c, sizeof(c), stdin)) break;
        c[strcspn(c, "\n")] = '\0';
    }

    return 0;
}
    