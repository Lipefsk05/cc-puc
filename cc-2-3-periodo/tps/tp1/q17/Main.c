#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool palin(char pali[100], int tam, int i, int j){

    if(i >= j)
        return true;

    if(pali[i] != pali[j])
        return false;

    return palin(pali, tam, i + 1, j - 1);

}


int main(){
	char pali[100];

	fgets(pali, sizeof(pali), stdin);
	pali[strcspn(pali, "\n")] = '\0';
	
	while(strcmp(pali, "FIM") != 0){

		if(palin(pali, strlen(pali), 0, strlen(pali) - 1))
			printf("SIM\n");
		else
			printf("NAO\n");

	fgets(pali, sizeof(pali), stdin);
	pali[strcspn(pali, "\n")] = '\0';
	
	}
	return 0;
}
