#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool pali(char c[], int i, int j) {
    if (i >= j)  
        return true;

    if (c[i] == '\uFFFD' || c[j] == '\uFFFD') {
        if (i == j)
            return true;
        return false;
    }

    if (c[i] != c[j]) {
        return false;
    }

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
    