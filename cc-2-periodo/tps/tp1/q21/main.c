#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void inverte(char p[], int tam){
    if(tam < 0){
        return;
    }

    printf("%c", p[tam]);

    return inverte(p, tam - 1);
}

int main(){
    char p[1000];
    
    fgets(p, sizeof(p), stdin);
    p[strcspn(p, "\n")] = '\0';
	
	while(strcmp(p, "FIM") != 0){
        
        int tam = strlen(p) - 1;
        
        inverte(p, tam);
        printf("\n");
        fgets(p, sizeof(p), stdin);
        p[strcspn(p, "\n")] = '\0';
	}
	return 0;

}