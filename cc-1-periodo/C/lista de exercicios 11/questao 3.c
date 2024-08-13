#include <stdio.h>
#include <string.h>

// Função para contar o número de vezes que a segunda string aparece na primeira string
int contarOcorrencias(char str1[], char str2[]) {
    int ocorrencias = 0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Percorre a string str1 procurando por ocorrências de str2
    for (int i = 0; i <= len1 - len2; i++) {
        // Verifica se há uma correspondência de str2 em str1 a partir da posição i
        int j;
        for (j = 0; j < len2; j++) {
            if (str1[i + j] != str2[j]) {
                break;
            }
        }
        // Se str2 foi encontrado, incrementa o contador de ocorrências
        if (j == len2) {
            ocorrencias++;
        }
    }

    return ocorrencias;
}

int main() {
    char str1[] = "Hello, Hello World! Hello!";
    char str2[] = "Hello";

    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);

    // Conta o número de vezes que str2 aparece em str1
    int ocorrencias = contarOcorrencias(str1, str2);

    printf("'%s' aparece %d vezes em '%s'.\n", str2, ocorrencias, str1);

    return 0;
}
