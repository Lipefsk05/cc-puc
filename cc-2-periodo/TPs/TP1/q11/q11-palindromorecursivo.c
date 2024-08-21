#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool pali(int i, char *pa, int tam){
    if(i>=tam){
    return true;
    }
    else if(pa[i]==pa[tam]){
        return pali(i+1, pa, tam-1);
    }
    else{
        return false;
    }
}

int main(){

    char pa[1000];

    scanf(" %[^\n]", pa);

    while (strcmp(pa, "FIM") != 0){

    int tam=(strlen(pa)-1);

    if(pali(0, pa, tam)){
        printf("SIM\n");  
    }
    else{
    printf("NAO\n");
        }

    scanf(" %[^\n]", pa);

    }

    return 0;
}