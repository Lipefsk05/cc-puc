#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
    int day;
    int mon;
    int yr;
}DT;

typedef struct{
    char *id;
    char *cat;
    char *name;
    char *dir;
    char **actors;
    size_t numActors;
    char *loc;
    DT dt_added;
    int yr_released;
    char *rate;
    char *len;
    char **genres;
    size_t numGenres;
}ENTRY;

ENTRY copyEntry(ENTRY src){
    ENTRY dest;

    dest.id = (char *)calloc(strlen(src.id) + 1,sizeof(char));
    strcpy(dest.id,src.id);

    dest.cat = (char *)calloc(strlen(src.cat) + 1,sizeof(char));
    strcpy(dest.cat,src.cat);

    dest.name = (char *)calloc(strlen(src.name) + 1,sizeof(char));
    strcpy(dest.name,src.name);

    dest.dir = (char *)calloc(strlen(src.dir) + 1,sizeof(char));
    strcpy(dest.dir,src.dir);

    dest.numActors = src.numActors;

    if(dest.numActors > 0){
        dest.actors = (char **)calloc(dest.numActors, sizeof(char *));
        for(int i = 0; i < dest.numActors; i++){
            dest.actors[i] = (char *)calloc(strlen(src.actors[i]) + 1, sizeof(char));
            strcpy(dest.actors[i],src.actors[i]);
        }
    }else{
        dest.actors = NULL;
    }

    dest.loc = (char *)calloc(strlen(src.loc) + 1,sizeof(char));
    strcpy(dest.loc,src.loc);

    dest.dt_added = src.dt_added;

    dest.yr_released = src.yr_released;

    dest.rate = (char *)calloc(strlen(src.rate) + 1,sizeof(char));
    strcpy(dest.rate,src.rate);

    dest.len = (char *)calloc(strlen(src.len) + 1,sizeof(char));
    strcpy(dest.len,src.len);

    dest.numGenres = src.numGenres;

    if(dest.numGenres > 0){
        dest.genres = (char **)calloc(dest.numGenres, sizeof(char *));
        for(int i = 0; i < dest.numGenres; i++){
            dest.genres[i] = (char *)calloc(strlen(src.genres[i]) + 1, sizeof(char));
            strcpy(dest.genres[i],src.genres[i]);
        }
    }else{
        dest.genres = NULL;
    }

    return dest;
}

char* makeLower(char *str){
    int n = strlen(str);
    char *result = (char *)calloc(n + 1,sizeof(char));

    for(int i = 0; i < n; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            result[i] = str[i] + 32;
        }else{
            result[i] = str[i];
        }
    }

    return result;
}

int getMonthNum(char *m){
    int num = 0;

    if(strcmp(m,"January") == 0) num = 1; 
    if(strcmp(m,"February") == 0) num = 2; 
    if(strcmp(m,"March") == 0) num = 3; 
    if(strcmp(m,"April") == 0) num = 4; 
    if(strcmp(m,"May") == 0) num = 5; 
    if(strcmp(m,"June") == 0) num = 6; 
    if(strcmp(m,"July") == 0) num = 7; 
    if(strcmp(m,"August") == 0) num = 8; 
    if(strcmp(m,"September") == 0) num = 9; 
    if(strcmp(m,"October") == 0) num = 10; 
    if(strcmp(m,"November") == 0) num = 11; 
    if(strcmp(m,"December") == 0) num = 12; 

    return num;
}

char *getMonthName(int x){
    char *name = (char *)malloc(25 * sizeof(char));
    
    switch(x){
        case 1:
            strcpy(name,"January");
            break;
        case 2:
            strcpy(name,"February");
            break;
        case 3:
            strcpy(name,"March");
            break;
        case 4:
            strcpy(name,"April");
            break;
        case 5:
            strcpy(name,"May");
            break;
        case 6:
            strcpy(name,"June");
            break;
        case 7:
            strcpy(name,"July");
            break;
        case 8:
            strcpy(name,"August");
            break;
        case 9:
            strcpy(name,"September");
            break;
        case 10:
            strcpy(name,"October");
            break;
        case 11:
            strcpy(name,"November");
            break;
        case 12:
            strcpy(name,"December");
            break;
        default:
            printf("ERROR: Month not found");
            break;
    }

    return name;
}

char *intToStr(int num){
    char *str = (char *)malloc(12 * sizeof(char));
    sprintf(str,"%d",num);
    return str;
}

char* formatDate(DT dt){
    char *dateStr = (char *)calloc(255 , sizeof(char));
    char *month = getMonthName(dt.mon);
    char *day = intToStr(dt.day);
    char *year = intToStr(dt.yr);

    strcat(dateStr,month);
    strcat(dateStr," ");
    strcat(dateStr,day);
    strcat(dateStr,", ");
    strcat(dateStr,year);

    free(month);
    free(day);
    free(year);

    return dateStr;
}

char* arrToStr(char **arr,size_t n){
    char *str = (char *)calloc(255,sizeof(char));

    for(int i = 0; i < n; i++){
        strcat(str,arr[i]);
        if(i != n -1)
            strcat(str,", ");
    }

    return str;
}

void display(ENTRY *e){
    char *addedDate;

    bool hasMonth = (e->dt_added.mon != 0);
    bool hasDay = (e->dt_added.day != 0);
    bool hasYear = (e->dt_added.yr != 0);

    if(hasMonth && hasDay && hasYear){
        addedDate = formatDate(e->dt_added);
    }else{
        addedDate = (char *)calloc(5,sizeof(char));
        strcpy(addedDate,"NaN");
    }

    char* actorList;
    if(e->actors != NULL){
        actorList = arrToStr(e->actors, e->numActors);
    }else{
        actorList = (char *)calloc(5,sizeof(char));
        strcpy(actorList,"NaN");
    }
    
    char* genreList;
    if(e->genres != NULL){
        genreList = arrToStr(e->genres,e->numGenres);
    }else{
        genreList = (char *)calloc(5,sizeof(char));
        strcpy(genreList,"NaN");
    }

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           e->id,e->name,e->cat,e->dir,actorList,e->loc,addedDate, 
           e->yr_released, e->rate, e->len, genreList);

    free(addedDate);
    free(genreList);
    free(actorList);
}

void parseEntry(ENTRY *e, char *line){
    int n = strlen(line);
    char *fields[11];
    int k = 0;
    int pos = 0;
    for(int i = 0; i < 11; i++){
        fields[i] = (char *)calloc(1024,sizeof(char));
        strcpy(fields[i],"NaN");
    }
    for(int i = 0; i < n && k < 11; i++){
        if(line[i] != ','){
            if(line[i] == '"'){
                i++;
                while(line[i] != '"'){
                    fields[k][pos++] = line[i++];
                }
            }else{
                fields[k][pos++] = line[i];
            }
        }else{
            fields[k][pos] = '\0';
            pos = 0;
            k++;
            while(line[i + 1] == ','){
                fields[k][pos++] = 'N';
                fields[k][pos++] = 'a';
                fields[k][pos++] = 'N';
                fields[k][pos] = '\0';
                i++;
                if(k < 11)
                    k++;
                pos = 0;
            }
        }
    }

    for(int i = 0; i < 11; i++){
        switch(i){
            case 0:
                {
                    size_t len = strlen(fields[i]);
                    e->id =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(e->id,fields[i]);
                    break;
                }
            case 1:
                {
                    size_t len = strlen(fields[i]);
                    e->cat =(char *)malloc((len + 1)* sizeof(char));
                    strcpy(e->cat,fields[i]);
                    break;
                }
            case 2:
                {
                    size_t len = strlen(fields[i]);
                    e->name =(char *)calloc((len + 1) , sizeof(char));
                    strcpy(e->name,fields[i]);
                    break;
                }
            case 3:
                {
                    size_t len = strlen(fields[i]);
                    e->dir =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(e->dir,fields[i]);
                    break;
                }
            case 4:
                {
                    if(strcmp(fields[i],"NaN") != 0 || strlen(fields[i]) != 0){
                        int count = 1;
                        int len = strlen(fields[i]);

                        for(int j = 0; j < len; j++)
                            if(fields[i][j] == ',')
                                count++;

                        e->numActors = count;

                        e->actors = (char **)calloc(count , sizeof(char*));
                        for(int j = 0; j < count;j++){
                            *(e->actors + j) = (char *)calloc(len , sizeof(char));
                        }

                        for(int j = 0,k = 0,l = 0; j < len; j++){
                            if(fields[i][j] != ','){
                                e->actors[k][l++] = fields[i][j];
                            }else if(fields[i][j] == ','){
                                e->actors[k++][l] = '\0';
                                l = 0;
                                if(fields[i][j + 1] == ' '){
                                    j++;
                                }
                            }
                        }

                        size_t s_len = e->numActors;
                        for(int j = 0; j < s_len - 1; j++){
                            int min = j;
                            for(int k = j + 1; k < s_len; k++){
                                if(strcmp(e->actors[k],e->actors[min]) < 0){
                                    min = k;
                                }
                            }
                            char *temp = e->actors[j];
                            e->actors[j] = e->actors[min];
                            e->actors[min] = temp;
                        }

                    }else{
                        e->numActors = 0;
                        e->actors = NULL;
                    }
                    break;
                }
            case 5:
                {
                    size_t len = strlen(fields[i]);
                    e->loc =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(e->loc,fields[i]);
                    break;
                }
            case 6:
                {
                    if(strcmp(fields[i],"NaN") != 0){
                        int len = strlen(fields[i]);
                        char month[len];
                        char day[len];
                        char year[len];

                        int k;
                        for(int j = 0; j < len; j++){
                            if(fields[i][j] != ' '){
                                month[j] = fields[i][j];
                            }else{
                                month[j] = '\0';
                                k = j + 1;
                                j = len;
                            }
                        }
                        for(int j = k,l = 0; j < len; j++){
                            if(fields[i][j] != ','){
                                day[l++] = fields[i][j];
                            }else{
                                day[l] = '\0';
                                k = j + 2;
                                j = len;
                            }
                        }
                        for(int j = k,l = 0; j < len; j++){
                            year[l++] = fields[i][j];
                            if(j == len - 1)
                                year[l] = '\0';
                        }

                        e->dt_added.mon = getMonthNum(month);
                        e->dt_added.day = atoi(day);
                        e->dt_added.yr = atoi(year);
                    }else{
                        e->dt_added.mon = 3;
                        e->dt_added.day = 1;
                        e->dt_added.yr = 1900;
                    }
                    break;
                }
            case 7:
                e->yr_released = atoi(fields[i]);
                break;
            case 8:
                {
                    size_t len = strlen(fields[i]);
                    e->rate =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(e->rate,fields[i]);
                    break;
                }
            case 9:
                {
                    size_t len = strlen(fields[i]);
                    e->len =(char *)malloc((len + 1) * sizeof(char));
                    strcpy(e->len,fields[i]);
                    break;
                }
            case 10:
                {
                    if(strcmp(fields[i],"NaN") != 0){
                        int count = 1;
                        int len = strlen(fields[i]);

                        for(int j = 0; j < len; j++)
                            if(fields[i][j] == ',')
                                count++;

                        e->numGenres = count;

                        e->genres = (char **)malloc(count * sizeof(char*));
                        for(int j = 0; j < count;j++){
                            *(e->genres + j) = (char *)malloc(len * sizeof(char));
                        }

                        for(int j = 0,k = 0,l = 0; j < len; j++){
                            if(fields[i][j] != ','){
                                e->genres[k][l++] = fields[i][j];
                            }else if(fields[i][j] == ','){
                                e->genres[k++][l] = '\0';
                                l = 0;
                                if(fields[i][j + 1] == ' '){
                                    j++;
                                }
                            }
                        }

                        size_t s_len = e->numGenres;
                        for(int j = 0; j < s_len - 1; j++){
                            int min = j;
                            for(int k = j + 1; k < s_len; k++){
                                if(strcmp(e->genres[k],e->genres[min]) < 0){
                                    min = k;
                                }
                            }
                            char *temp = e->genres[j];
                            e->genres[j] = e->genres[min];
                            e->genres[min] = temp;
                        }

                    }else{
                        e->numGenres = 0;
                        e->genres = NULL;
                    }
                    break;
                }
        }
    }
}

void readCSVLine(char *line,int size, FILE *f){
    if (f == NULL) {
        fprintf(stderr, "Error: NULL file pointer passed to readCSVLine().\n");
        exit(1);
    }

    if (fgets(line, size, f) == NULL) {
        fprintf(stderr, "Error reading file line or EOF reached.\n");
        exit(1);
    }
    size_t len = strlen(line);
    if(line[len - 1] == '\n')
        line[len - 1] = '\0';
}

void freeEntry(ENTRY *e){
    free(e->id);
    free(e->cat);
    free(e->name);
    free(e->dir);
    free(e->loc);
    free(e->rate);
    free(e->len);
    if(e->actors != NULL){
        for(int j = 0; j < e->numActors; j++){
            free(*(e->actors + j));
        }
        free(e->actors);
    }
    if(e->genres != NULL){
        for(int j = 0; j < e->numGenres; j++){
            free(*(e->genres + j));
        }
        free(e->genres);
    }
}

bool shouldSwap(ENTRY a, ENTRY b, int *cmp){
    char *aCat = makeLower(a.cat);
    char *bCat = makeLower(b.cat);
    char *aName = makeLower(a.name);
    char *bName = makeLower(b.name);

    bool cond1 = strcmp(aCat,bCat) < 0;

    if(cond1)
        *cmp += 1;

    bool cond2 = (strcmp(aCat,bCat) == 0 &&
            strcmp(aName,bName) < 0);

    if(cond2)
        *cmp += 3;

    free(aCat);
    free(bCat);
    free(aName);
    free(bName);

    return (cond1 || cond2);
}

void gapInsertion(ENTRY *arr,int gap, int h, int *moves, int *compares, int size){
    for(int i = (gap + h); i < size; i+=h){
        ENTRY temp = arr[i];
        int j = i - h;
        while(j >= 0 && shouldSwap(temp, arr[j], compares)){
            *moves += 1;
            arr[j + h] = arr[j];
            j -= h;
        }
        if((i + h) != i){
            *moves += 1;
            arr[j + h] = temp;
        }
    }
}

void shellSort(ENTRY *arr, int size,int *moves, int *compares){
    int h = 1;
    do{h = (h * 3) + 1;} while(h < size);
    do{
        h /= 3;
        for(int gap = 0; gap < h; gap++){
            gapInsertion(arr,gap, h,moves,compares, size);
        }
    }while(h != 1);
}

int main(){
    ENTRY *data = (ENTRY *)calloc(1368,sizeof(ENTRY));

    FILE *input = fopen("/tmp/disneyplus.csv", "r");

    char *csvLine = (char *)malloc(1024*sizeof(char));
    while(fgetc(input) != '\n');

    for(int i = 0; i < 1368; i++){
        readCSVLine(csvLine, 1024, input);
        parseEntry((data + i),csvLine);
    }
    free(csvLine);
    fclose(input);

    char *inputID = (char *)malloc(255 * sizeof(char));
    scanf("%s",inputID);

    ENTRY selected[1368];
    int selectedCount = 0;

    while(strcmp(inputID,"FIM") != 0){
        int idx = atoi((inputID + 1));
        selected[selectedCount++] = copyEntry(data[--idx]);
        scanf("%s",inputID);
    }

    int moves = 0;
    int compares = 0;
    clock_t start = clock();
    shellSort(selected,selectedCount, &moves,&compares);
    clock_t end = clock();
    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    FILE *logFile = fopen("./853431_shellsort.txt","w");
    fprintf(logFile,"853431\t%d\t%d\t%.6f",compares,moves,timeTaken * 1000);
    fclose(logFile);

    for(int i = 0; i < selectedCount; i++){
        display(&selected[i]);
    }
    
    for(int i = 0; i < 1368; i++)
        freeEntry(data + i);
    free(data);

    return 0;
}