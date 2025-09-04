#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isVog(char *s) {

    int tam = strlen(s);
    
    for (int i = 0; i < tam; i++) {
    
        char c = tolower(s[i]);
    
        if (strchr("aeiou", c) == NULL)
            return false;
    }
    return true;
}

bool isCon(char *s) {
    
    int tam = strlen(s);
    
    for (int i = 0; i < tam; i++) {
    
        char c = tolower(s[i]);
    
        if (strchr("bcdfghjklmnpqrstvwxyz", c) == NULL)
            return false;
    }
    return true;
}

bool isInt(char *s) {
    
    int tam = strlen(s);
    
    if (tam == 0) return false;
    
    for (int i = 0; i < tam; i++) {
    
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}

bool isRea(char *s) {
    
    int tam = strlen(s);
    int sepCount = 0;
        
    if (tam == 0)
        return false;

    for (int i = 0; i < tam; i++) {
    
        if (s[i] == '.' || s[i] == ',') {
    
            sepCount++;

            if (sepCount > 1)
                return false;
    
        }else if (!isdigit(s[i])) {
            return false;
        }
    }
    return sepCount == 1;
}

int main() {
    char s[1000];

    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    while (strcmp(s, "FIM") != 0) {
        printf("%s ", isVog(s) ? "SIM" : "NAO");
        printf("%s ", isCon(s) ? "SIM" : "NAO");

        if(isInt(s)){
            printf("SIM SIM\n");
        }else{
            printf("NAO ");
            printf("%s\n", isRea(s) ? "SIM" : "NAO");
        }

        fgets(s, sizeof(s), stdin);
        s[strcspn(s, "\n")] = '\0';
    }

    return 0;
}
