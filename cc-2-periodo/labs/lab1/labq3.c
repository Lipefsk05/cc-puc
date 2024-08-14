#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int maimin(char *stg){
    
    int tam = strlen(stg)-1;

    int mai=0;
    
    for(int i=0 ; i<=tam ; i++){
        
        if((stg[i]>=65 && stg[i]<=90)){
        mai++;
        }
    }

    return mai;

}

int main(){ 

    char stg[1000];

    
    do{
        scanf(" %[^\n]", stg);
        if(strcmp(stg, "FIM") != 0)
        printf("%i\n", maimin(stg));
    }

    while(strcmp(stg, "FIM") != 0);

    return 0;
}
