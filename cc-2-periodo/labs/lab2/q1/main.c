#include <stdio.h>
#include <string.h>

void comb(char *str1, char *str2){
        
    char temp[3000];
        
    int tam1 = strlen(str1);
    int tam2 = strlen(str2);
    int taM, tam;
    int 
    cont = 0;

    if(tam1<tam2){   
        taM = tam2;
        tam = tam1;
    }
    else{
        tam = tam2;
        taM = tam1;
    }

    for(int i = 0; i < tam ; i++){
            
        temp[cont++] = str1[i];
        temp[cont++] = str2[i];
    }

    for(int i = tam ; i < taM ; i++){
        if(tam1 > tam2)
            temp[cont++] = str1[i];
        else
            temp[cont++] = str2[i];
    }

    temp[cont] = '\0';

    printf("%s\n", temp);

}

int main(){

    char str1[1000];
    char str2[1000];

    while(scanf("%s", str1) != EOF){
        getchar();
        scanf("%s", str2);
        comb(str1, str2);
    }

    return 0;
    }