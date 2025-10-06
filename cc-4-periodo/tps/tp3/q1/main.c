#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isVogRec(char *s, int i) {

    if (s[i] == '\0')
    return true;
    
    char c = tolower(s[i]);
    
    if (strchr("aeiou", c) == NULL) return false;
    return isVogRec(s, i + 1);
}

bool isVog(char *s) {
    return isVogRec(s, 0);
}

bool isConRec(char *s, int i) {

    if (s[i] == '\0')
    return true;
    
    char c = tolower(s[i]);
    
    if (strchr("bcdfghjklmnpqrstvwxyz", c) == NULL) return false;
    return isConRec(s, i + 1);
}

bool isCon(char *s) {
    
    return (strlen(s) > 0) && isConRec(s, 0);
}

bool isIntRec(char *s, int i) {

    if (s[i] == '\0')
    return true;

    if (!isdigit(s[i]))
    return false;

    return isIntRec(s, i + 1);
}

bool isInt(char *s) {
    return (strlen(s) > 0) && isIntRec(s, 0);
}

// Função recursiva para verificar se é real (1 ponto ou vírgula)
bool isReaRec(char *s, int i, int sepCount) {
    
    if (s[i] == '\0')
    return (sepCount == 1);
    
    if (s[i] == '.' || s[i] == ',') {
        sepCount++;
        if (sepCount > 1) return false;
    }
    else if (!isdigit(s[i])) {
    
        return false;
    }
    
    return isReaRec(s, i + 1, sepCount);
}

bool isRea(char *s) {
    
    return (strlen(s) > 0) && isReaRec(s, 0, 0);
}

void processa() {

    char s[1000];

    if (!fgets(s, sizeof(s), stdin))
    return;
    
    s[strcspn(s, "\n")] = '\0';

    if (strcmp(s, "FIM") == 0)
    return;

    printf("%s ", isVog(s) ? "SIM" : "NAO");
    printf("%s ", isCon(s) ? "SIM" : "NAO");

    if (isInt(s)) {
        printf("SIM SIM\n");
    } else {
        printf("NAO ");
        printf("%s\n", isRea(s) ? "SIM" : "NAO");
    }

    processa();
}

int main() {
    
    processa();
    return 0;
}
