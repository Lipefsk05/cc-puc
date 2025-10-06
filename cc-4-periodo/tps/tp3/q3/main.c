#include <stdio.h>
#include <string.h>

int somaDigitos(char *s, int i) {
    if (s[i] == '\0')
    return 0;
    
    return (s[i] - '0') + somaDigitos(s, i + 1);
}

void processa() {
    char n[100];
    if (scanf(" %[^\n]", n) != 1) return;

    if (strcmp(n, "FIM") == 0) return;

    printf("%d\n", somaDigitos(n, 0));

    processa();
}

int main() {
    processa();
    return 0;
}
