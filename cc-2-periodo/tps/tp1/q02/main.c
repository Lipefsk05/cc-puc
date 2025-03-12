#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool palin(char pali[100]){

	int tam = strlen(pali); 
	int j = tam - 1;

	for(int i = 0 ; i < tam / 2 ; i++, j--){

		if(pali[i] != pali[j])
			return 0;
	}
	return 1;

}


int main(){
	char pali[100];

	fgets(pali, sizeof(pali), stdin);
	pali[strcspn(pali, "\n")] = '\0';
	
	while(strcmp(pali, "FIM") != 0){

		if(palin(pali))
			printf("SIM\n");
		else
			printf("NAO\n");

	fgets(pali, sizeof(pali), stdin);
	pali[strcspn(pali, "\n")] = '\0';
	
	}
	return 0;
}
