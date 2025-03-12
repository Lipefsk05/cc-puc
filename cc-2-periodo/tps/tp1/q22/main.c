#include <stdio.h>
#include <string.h>

int somar(char nms[1000],int tam, int soma, int i){

    if(i >= tam)
        return soma;
    
    soma += nms[i] - '0';

    return somar(nms, tam, soma, i + 1);

}

int main(){
    
    char nms[1000];
    
    fgets(nms, sizeof(nms), stdin);
    nms[strcspn(nms, "\n")] = '\0';

    
    while(strcmp(nms, "FIM") != 0){

        int tam = strlen(nms);
        printf("%i\n", somar(nms, tam, 0, 0));
    
        fgets(nms, sizeof(nms), stdin);
        nms[strcspn(nms, "\n")] = '\0';

    }


    return 0;
}