#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int maimin(int i, char *stg){
    
    int mai=0;
    
    int tam = strlen(stg)-1;

    if(i>=tam){
        return mai;
    }else if((stg[i]>=65 && stg[i]<=90)){
        return maimin(i+1, stg)
    }

}

int main(){ 

    char stg[1000];

    
    do{
        scanf(" %[^\n]", stg);
        if(strcmp(stg, "FIM") != 0)
        printf("%i\n", maimin(0, stg));
    }

    while(strcmp(stg, "FIM") != 0);

    return 0;
}