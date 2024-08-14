#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool palin(char pa[1000]){


    int tam= strlen(pa)-1;
    int j = tam;

        for(int i=0; i<=(tam/2); i++){
        
        if(pa[i]!=pa[j-i]){
            return false;
        }  
    }
    
    return true;

}

int main(){

    char pa[1000];

    scanf(" %[^\n]", pa);

    while(strcmp(pa, "FIM") != 0){

    if(palin(pa))
    printf("SIM\n");
    
    else printf("NAO\n");

    scanf(" %[^\n]", pa);

    }


    return 0;
}