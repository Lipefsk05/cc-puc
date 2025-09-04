#include <stdio.h>
#include <string.h>

void combina(char arr1[1000], char arr2[1000], char arr3[1000]){
    
    int tamM, tamm, v;

    if(strlen(arr1) > strlen(arr2)){
        tamM = strlen(arr1);
        tamm = strlen(arr2);
        v = 1;
    }
    else{
        tamM = strlen(arr2);
        tamm = strlen(arr1);
        v = 0;
    }

    for(int i = 0, j = 0 ; i < tamm*2 ; i+=2, j++){
        arr3[i] = arr1[j];  
        arr3[i+1] = arr2[j];
    }

    if(v){
        for(int i = tamm*2, j=tamm; i < tamm*2 + (tamM-tamm) ; i++, j++){
            arr3[i] = arr1[i-tamm];
        }
    }
    else{
        for(int i = tamm*2, j=tamm; i < tamm*2 + (tamM-tamm) ; i++, j++){
            arr3[i] = arr2[i-tamm];
        }
    }

    arr3[tamM + tamm] = '\0';
}

int main(){
    char arr1[1000];
    char arr2[1000];
    char arr3[1000];

    while (scanf("%s %s", arr1, arr2) == 2){
        combina(arr1, arr2, arr3);
        printf("%s\n", arr3);
    }

    return 0;
}