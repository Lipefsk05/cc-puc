#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int dia;
    int mes;
    int ano;

}Date;

typedef struct{

    char SHOW_ID[10];  
    char TYPE[50];
    char TITLE[250];
    char DIRECTOR[100];
    char *CAST[21]; 
    char COUNTRY[70];
    Date DATE_ADDED;
    int RELEASE_YEAR;
    char RATING[20];
    char DURATION[20];
    char *LISTED_IN[21]; 

}Show;

Show shows[1368];

char* entreAspas(char *str){

    if(str == NULL || strcmp(str, "NaN") == 0) return strdup("NaN");
    
    char *saida = malloc(strlen(str) + 1);
    char *destino = saida;

    int aspas = 0;
    
    for(char *src = str; *src; src++){
        if(*src == '"'){

            if(aspas && *(src+1) == '"'){
                *destino++ = '"';
                src++;
            }
            aspas = !aspas;
        } else{
            *destino++ = *src;
        }
    }

    *destino = '\0';
    
    if(strlen(saida) == 0){
        free(saida);
    
        return strdup("NaN");
    }
    
    return saida;
}

void split(char linha[], char *campos[]){

    char *ponteiro = linha;
    char *inicio;
    
    int qtd = 0;
    
    while(*ponteiro && qtd < 12){
        
        if(*ponteiro == '"'){
            ponteiro++;
            inicio = ponteiro;
            
            while(*ponteiro && !(*ponteiro == '"' && (*(ponteiro+1) == ',' || *(ponteiro+1) == '\0'))) ponteiro++;
            *ponteiro = '\0';
            
            campos[qtd++] = entreAspas(inicio);
            
            if(*(ponteiro+1)) ponteiro += 2;

            else{
                ponteiro++;
            }  
        }
        else{
            
            inicio = ponteiro;
            
            while(*ponteiro && *ponteiro != ',') ponteiro++;
            if(*ponteiro){
                *ponteiro = '\0';
                ponteiro++; 
            }

            campos[qtd++] = strlen(inicio) ? entreAspas(inicio) : strdup("NaN");
        }
    }

    while(qtd < 12){
        campos[qtd++] = strdup("NaN");
    }
}

int acharIndex(char *id){

    return atoi(id + 1) - 1;
}

void ordenarLista(char *destino[], char origem[]){

    if(strcmp(origem, "NaN") == 0){
        destino[0] = strdup("NaN");
        destino[1] = NULL;
    
        return;
    }

    int tam = 0;
    
    char *token = strtok(origem, ",");
    
    while(token != NULL && tam < 20){
        while(*token == ' ') token++;
        
        if(strlen(token) > 0){
            destino[tam++] = strdup(token);
        }
        token = strtok(NULL, ",");
    }
    
    destino[tam] = NULL;

    for(int i = 0; i < tam - 1; i++){
        for(int j = i + 1; j < tam; j++){
    
            if(strcmp(destino[i], destino[j]) > 0){
                char *tmp = destino[i];
                destino[i] = destino[j];
                destino[j] = tmp;
            }
        }
    }
}

void preencherCast(int index, char *origem[]){
    
    int i;
    
    for(i = 0; origem[i] != NULL && i < 20; i++){
        shows[index].CAST[i] = strdup(origem[i]);
    }
    
    shows[index].CAST[i] = NULL;
}

void preencherListed(int index, char *origem[]){

    int i;
    
    for(i = 0; origem[i] != NULL && i < 20; i++){
        shows[index].LISTED_IN[i] = strdup(origem[i]);
    }
    
    shows[index].LISTED_IN[i] = NULL;
}

Date converterData(char *date){

    if(date == NULL || strcmp(date, "NaN") == 0){
        return (Date){0, 0, 0};
    }

    char *partes[3];
    int qtd = 0;

    char *token = strtok(date, " ,");
    
    while(token != NULL && qtd < 3){
        partes[qtd++] = token;
        token = strtok(NULL, " ,");
    }

    if(qtd != 3) return (Date){0, 0, 0};

    char *meses[12] ={"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    int nMeses = 0;
    
    for(int i = 0; i < 12; i++){
        if(strcmp(meses[i], partes[0]) == 0){
            nMeses = i + 1;
            
            break;
        }
    }

    return (Date){atoi(partes[1]), nMeses, atoi(partes[2])};
}

void ler(){

    FILE *file = fopen("/tmp/disneyplus.csv", "r");
    
    if(!file){
        printf("Erro ao abrir o arquivo.\n");
        
        return;
    }

    char linha[2000];
    fgets(linha, 2000, file); 

    while(fgets(linha, 2000, file) != NULL){
        linha[strcspn(linha, "\n")] = '\0';

        char *divisao[12] ={0};
        split(linha, divisao);

        int index = acharIndex(divisao[0]);
        strncpy(shows[index].SHOW_ID, divisao[0], 9);
        shows[index].SHOW_ID[9] = '\0';
        
        strcpy(shows[index].TYPE, divisao[1]);
        strcpy(shows[index].TITLE, divisao[2]);
        strcpy(shows[index].DIRECTOR, divisao[3]);

        char CAST[1000];

        strcpy(CAST, divisao[4]);
        char *CASTArray[21] ={0};
        
        ordenarLista(CASTArray, CAST);
        preencherCast(index, CASTArray);

        strcpy(shows[index].COUNTRY, divisao[5]);
        
        shows[index].DATE_ADDED = converterData(divisao[6]);
        shows[index].RELEASE_YEAR = atoi(divisao[7]);
        
        strcpy(shows[index].RATING, divisao[8]);
        strcpy(shows[index].DURATION, divisao[9]);

        char listed[1000];
        strcpy(listed, divisao[10]);
        
        char *listedArray[21] ={0};
        
        ordenarLista(listedArray, listed);
        preencherListed(index, listedArray);

        for(int i = 0; i < 12; i++){
            free(divisao[i]);
        }
    }

    fclose(file);
}

char* formatarData(Date formatar){
    
    if(formatar.ano == 0) return strdup("NaN");

    char *meses[12] ={"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    char *formatedDate = malloc(30 * sizeof(char));
    sprintf(formatedDate, "%s %d, %d", meses[formatar.mes - 1], formatar.dia, formatar.ano);
    
    return formatedDate;
}

void lerShow(Show sh){

    printf("=> %s ## %s ## %s ## %s ## [", sh.SHOW_ID, sh.TITLE, sh.TYPE, sh.DIRECTOR);
    
    for(int i = 0; sh.CAST[i] != NULL; i++){
        printf("%s%s", sh.CAST[i], (sh.CAST[i+1] ? ", " : ""));
    }
    
    printf("] ## %s ## ", sh.COUNTRY);

    char *formatedDate = formatarData(sh.DATE_ADDED);
    
    printf("%s ## ", formatedDate);
    free(formatedDate);

    printf("%d ## %s ## %s ## [", sh.RELEASE_YEAR, sh.RATING, sh.DURATION);
    
    for(int i = 0; sh.LISTED_IN[i] != NULL; i++){
        printf("%s%s", sh.LISTED_IN[i], (sh.LISTED_IN[i+1] ? ", " : ""));
    }
    printf("] ##\n");
}

Show array[1000];
int n = 0;

void inserirInicio(Show i){
    
    for(int j = n; j > 0; j--){
        array[j] = array[j-1];
    }
    array[0] = i;

    n++;
}

void inserir(Show i, int pos){
    
    if(pos < 0 || pos > n){
        return;
    } 
    
    for(int j = n; j > pos; j--){
        array[j] = array[j-1];
    }
    array[pos] = i;
    
    n++;
}

void inserirFim(Show x){
    
    array[n] = x;
    n++;
}

Show removerInicio(){
    
    if(n == 0) return (Show){0};
    
    Show saida = array[0];
    n--;

    for(int i = 0; i < n; i++){
        array[i] = array[i+1];
    }
    return saida;
}

Show removerFim(){

    if(n == 0) return (Show){0};
    
    return array[--n];
}

Show remover(int pos){

    if(pos < 0 || pos >= n){
        return (Show){0};
    } 
    
    Show saida = array[pos];
    n--;
    
    for(int i = pos; i < n; i++){
        array[i] = array[i+1];
    }
    
    return saida;
}

void mostrar(){
    
    for(int i = 0; i < n; i++){
        lerShow(array[i]);  
    }
}

int main(){

    ler();
    
    char linha[30];
    fgets(linha, 30, stdin);
    
    linha[strcspn(linha, "\n")] = '\0';
    
    while(strcmp(linha, "FIM") != 0){
    
        int index = acharIndex(linha);
    
        if(index >= 0 && index < 1368){
            inserirFim(shows[index]);
        }
    
        fgets(linha, 30, stdin);
        linha[strcspn(linha, "\n")] = '\0';
    }

    fgets(linha, 30, stdin);
    linha[strcspn(linha, "\n")] = '\0';

    int tam = atoi(linha);
    
    for(int i = 0; i < tam; i++){
    
        fgets(linha, 30, stdin);
        linha[strcspn(linha, "\n")] = '\0';
        char *token = strtok(linha, " ");

        if(strcmp(token, "II") == 0){
    
            token = strtok(NULL, " ");
            int index = acharIndex(token);
    
            if(index >= 0 && index < 1368){
                inserirInicio(shows[index]);
            }
        } 
        else if(strcmp(token, "IF") == 0){
        
            token = strtok(NULL, " ");
            int index = acharIndex(token);
            if(index >= 0 && index < 1368){
                inserirFim(shows[index]);
            }
        } 
        else if(strcmp(token, "I*") == 0){
        
            token = strtok(NULL, " ");
            int pos = atoi(token);
        
            token = strtok(NULL, " ");
            int index = acharIndex(token);
        
            if(index >= 0 && index < 1368 && pos >= 0 && pos <= n){
                inserir(shows[index], pos);
            }
        } 
        else if(strcmp(token, "RI") == 0){
        
            Show resp = removerInicio();
            printf("(R) %s\n", resp.TITLE);
        } 
        else if(strcmp(token, "RF") == 0){
        
            Show resp = removerFim();
            printf("(R) %s\n", resp.TITLE);
        } 
        else if(strcmp(token, "R*") == 0){
        
            token = strtok(NULL, " ");
            int pos = atoi(token);
            Show resp = remover(pos);
            printf("(R) %s\n", resp.TITLE);
        }
    }

    mostrar();

    for(int i = 0; i < 1368; i++){
        
        for(int j = 0; shows[i].CAST[j] != NULL; j++){
            free(shows[i].CAST[j]);
        }
        
        for(int j = 0; shows[i].LISTED_IN[j] != NULL; j++){
            free(shows[i].LISTED_IN[j]);
        }
    }

    return 0;
}