#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void swap(char l1, char l2, char *frase){

    for(int i = 0 ; i < strlen(frase) ; i++){

        if(frase[i] == l1){
            frase[i] = l2;
        }
    }
    printf("%s\n", frase);
}

int main(){
    srand(4);

    char l1 = (char) ('a' + (rand() % 26));
    char l2 = (char) ('a' + (rand() % 26));
    char frase[1000];

    do{
        scanf(" %[^\n]", frase);

        if(strcmp(frase, "FIM") != 0)
        swap(l1, l2, frase);
    }
    while(strcmp(frase, "FIM") != 0);

    return 0;
}

