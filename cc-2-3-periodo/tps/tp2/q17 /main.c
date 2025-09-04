#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <time.h>

bool debugMode = false;
FILE *debugLog;

typedef struct {
    int day;
    int month;
    int year;
} DateInfo;

typedef struct {
    char *id;
    char *contentType;
    char *title;
    char *directorName;
    char **actors;
    size_t actorCount;
    char *country;
    DateInfo addedDate;
    int releaseYear;
    char *rating;
    char *duration;
    char **genres;
    size_t genreCount;
} MediaEntry;

MediaEntry duplicateMedia(MediaEntry original) {
    MediaEntry copy;

    copy.id = (char *)calloc(strlen(original.id) + 1, sizeof(char));
    strcpy(copy.id, original.id);

    copy.contentType = (char *)calloc(strlen(original.contentType) + 1, sizeof(char));
    strcpy(copy.contentType, original.contentType);

    copy.title = (char *)calloc(strlen(original.title) + 1, sizeof(char));
    strcpy(copy.title, original.title);

    copy.directorName = (char *)calloc(strlen(original.directorName) + 1, sizeof(char));
    strcpy(copy.directorName, original.directorName);

    copy.actorCount = original.actorCount;

    if(copy.actorCount > 0) {
        copy.actors = (char **)calloc(copy.actorCount, sizeof(char *));
        for(int i = 0; i < copy.actorCount; i++) {
            copy.actors[i] = (char *)calloc(strlen(original.actors[i]) + 1, sizeof(char));
            strcpy(copy.actors[i], original.actors[i]);
        }
    } else {
        copy.actors = NULL;
    }

    copy.country = (char *)calloc(strlen(original.country) + 1, sizeof(char));
    strcpy(copy.country, original.country);

    copy.addedDate = original.addedDate;

    copy.releaseYear = original.releaseYear;

    copy.rating = (char *)calloc(strlen(original.rating) + 1, sizeof(char));
    strcpy(copy.rating, original.rating);

    copy.duration = (char *)calloc(strlen(original.duration) + 1, sizeof(char));
    strcpy(copy.duration, original.duration);

    copy.genreCount = original.genreCount;

    if(copy.genreCount > 0) {
        copy.genres = (char **)calloc(copy.genreCount, sizeof(char *));
        for(int i = 0; i < copy.genreCount; i++) {
            copy.genres[i] = (char *)calloc(strlen(original.genres[i]) + 1, sizeof(char));
            strcpy(copy.genres[i], original.genres[i]);
        }
    } else {
        copy.genres = NULL;
    }

    return copy;
}

char* convertToLowercase(char *str) {
    int length = strlen(str);
    char *result = (char *)calloc(length + 1, sizeof(char));

    for(int i = 0; i < length; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            result[i] = str[i] + 32;
        } else {
            result[i] = str[i];
        }
    }

    return result;
}

int convertMonthToNumber(char *month) {
    int num = 0;

    if(strcmp(month, "January") == 0) num = 1; 
    if(strcmp(month, "February") == 0) num = 2; 
    if(strcmp(month, "March") == 0) num = 3; 
    if(strcmp(month, "April") == 0) num = 4; 
    if(strcmp(month, "May") == 0) num = 5; 
    if(strcmp(month, "June") == 0) num = 6; 
    if(strcmp(month, "July") == 0) num = 7; 
    if(strcmp(month, "August") == 0) num = 8; 
    if(strcmp(month, "September") == 0) num = 9; 
    if(strcmp(month, "October") == 0) num = 10; 
    if(strcmp(month, "November") == 0) num = 11; 
    if(strcmp(month, "December") == 0) num = 12; 

    return num;
}

char *convertNumberToMonth(int num) {
    char *month = (char *)malloc(25 * sizeof(char));
    
    switch(num) {
        case 1: strcpy(month, "January"); break;
        case 2: strcpy(month, "February"); break;
        case 3: strcpy(month, "March"); break;
        case 4: strcpy(month, "April"); break;
        case 5: strcpy(month, "May"); break;
        case 6: strcpy(month, "June"); break;
        case 7: strcpy(month, "July"); break;
        case 8: strcpy(month, "August"); break;
        case 9: strcpy(month, "September"); break;
        case 10: strcpy(month, "October"); break;
        case 11: strcpy(month, "November"); break;
        case 12: strcpy(month, "December"); break;
        default: printf("ERROR: Month not found"); break;
    }

    return month;
}

char *convertIntToString(int num) {
    char *str = (char *)malloc(12 * sizeof(char));
    sprintf(str, "%d", num);
    return str;
}

char* formatDateString(DateInfo date) {
    char *formatted = (char *)calloc(255, sizeof(char));
    char *month = convertNumberToMonth(date.month);
    char *day = convertIntToString(date.day);
    char *year = convertIntToString(date.year);

    strcat(formatted, month);
    strcat(formatted, " ");
    strcat(formatted, day);
    strcat(formatted, ", ");
    strcat(formatted, year);

    free(month);
    free(day);
    free(year);

    return formatted;
}

char* convertArrayToString(char **array, size_t size) {
    char *result = (char *)calloc(255, sizeof(char));

    for(int i = 0; i < size; i++) {
        strcat(result, array[i]);
        if(i != size - 1)
            strcat(result, ", ");
    }

    return result;
}

void printMediaEntry(MediaEntry *entry) {
    char *dateStr;

    bool hasMonth = (entry->addedDate.month != 0);
    bool hasDay = (entry->addedDate.day != 0);
    bool hasYear = (entry->addedDate.year != 0);

    if(hasMonth && hasDay && hasYear) {
        dateStr = formatDateString(entry->addedDate);
    } else {
        dateStr = (char *)calloc(5, sizeof(char));
        strcpy(dateStr, "NaN");
    }

    char* actorsStr;
    if(entry->actors != NULL) {
        actorsStr = convertArrayToString(entry->actors, entry->actorCount);
    } else {
        actorsStr = (char *)calloc(5, sizeof(char));
        strcpy(actorsStr, "NaN");
    }
    
    char* genresStr;
    if(entry->genres != NULL) {
        genresStr = convertArrayToString(entry->genres, entry->genreCount);
    } else {
        genresStr = (char *)calloc(5, sizeof(char));
        strcpy(genresStr, "NaN");
    }

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           entry->id, entry->title, entry->contentType, entry->directorName, actorsStr,
           entry->country, dateStr, entry->releaseYear, entry->rating, entry->duration, genresStr);

    free(dateStr);
    free(genresStr);
    free(actorsStr);
}

void parseMediaEntry(MediaEntry *entry, char *line) {
    int length = strlen(line);
    char *fields[11];
    int fieldNum = 0;
    int charPos = 0;
    
    for(int i = 0; i < 11; i++) {
        fields[i] = (char *)calloc(1024, sizeof(char));
        strcpy(fields[i], "NaN");
    }
    
    for(int i = 0; i < length && fieldNum < 11; i++) {
        if(line[i] != ',') {
            if(line[i] == '"') {
                i++;
                while(line[i] != '"') {
                    fields[fieldNum][charPos++] = line[i++];
                }
            } else {
                fields[fieldNum][charPos++] = line[i];
            }
        } else {
            fields[fieldNum][charPos] = '\0';
            charPos = 0;
            fieldNum++;
            while(line[i + 1] == ',') {
                fields[fieldNum][charPos++] = 'N';
                fields[fieldNum][charPos++] = 'a';
                fields[fieldNum][charPos++] = 'N';
                fields[fieldNum][charPos] = '\0';
                i++;
                if(fieldNum < 11)
                    fieldNum++;
                charPos = 0;
            }
        }
    }

    for(int i = 0; i < 11; i++) {
        switch(i) {
            case 0:
                entry->id = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(entry->id, fields[i]);
                break;
            case 1:
                entry->contentType = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(entry->contentType, fields[i]);
                break;
            case 2:
                entry->title = (char *)calloc((strlen(fields[i]) + 1), sizeof(char));
                strcpy(entry->title, fields[i]);
                break;
            case 3:
                entry->directorName = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(entry->directorName, fields[i]);
                break;
            case 4:
                if(strcmp(fields[i], "NaN") != 0 || strlen(fields[i]) != 0) {
                    int count = 1;
                    int len = strlen(fields[i]);

                    for(int j = 0; j < len; j++)
                        if(fields[i][j] == ',')
                            count++;

                    entry->actorCount = count;
                    entry->actors = (char **)calloc(count, sizeof(char*));
                    
                    for(int j = 0; j < count; j++) {
                        entry->actors[j] = (char *)calloc(len, sizeof(char));
                    }

                    for(int j = 0, k = 0, l = 0; j < len; j++) {
                        if(fields[i][j] != ',') {
                            entry->actors[k][l++] = fields[i][j];
                        } else if(fields[i][j] == ',') {
                            entry->actors[k++][l] = '\0';
                            l = 0;
                            if(fields[i][j + 1] == ' ') {
                                j++;
                            }
                        }
                    }

                    for(int j = 0; j < entry->actorCount - 1; j++) {
                        int min = j;
                        for(int k = j + 1; k < entry->actorCount; k++) {
                            if(strcmp(entry->actors[k], entry->actors[min]) < 0) {
                                min = k;
                            }
                        }
                        char *temp = entry->actors[j];
                        entry->actors[j] = entry->actors[min];
                        entry->actors[min] = temp;
                    }
                } else {
                    entry->actorCount = 0;
                    entry->actors = NULL;
                }
                break;
            case 5:
                entry->country = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(entry->country, fields[i]);
                break;
            case 6:
                if(strcmp(fields[i], "NaN") != 0) {
                    int len = strlen(fields[i]);
                    char monthStr[len];
                    char dayStr[len];
                    char yearStr[len];

                    int pos;
                    for(int j = 0; j < len; j++) {
                        if(fields[i][j] != ' ') {
                            monthStr[j] = fields[i][j];
                        } else {
                            monthStr[j] = '\0';
                            pos = j + 1;
                            j = len;
                        }
                    }
                    for(int j = pos, l = 0; j < len; j++) {
                        if(fields[i][j] != ',') {
                            dayStr[l++] = fields[i][j];
                        } else {
                            dayStr[l] = '\0';
                            pos = j + 2;
                            j = len;
                        }
                    }
                    for(int j = pos, l = 0; j < len; j++) {
                        yearStr[l++] = fields[i][j];
                        if(j == len - 1)
                            yearStr[l] = '\0';
                    }

                    entry->addedDate.month = convertMonthToNumber(monthStr);
                    entry->addedDate.day = atoi(dayStr);
                    entry->addedDate.year = atoi(yearStr);
                } else {
                    entry->addedDate.month = 3;
                    entry->addedDate.day = 1;
                    entry->addedDate.year = 1900;
                }
                break;
            case 7:
                entry->releaseYear = atoi(fields[i]);
                break;
            case 8:
                entry->rating = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(entry->rating, fields[i]);
                break;
            case 9:
                entry->duration = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(entry->duration, fields[i]);
                break;
            case 10:
                if(strcmp(fields[i], "NaN") != 0) {
                    int count = 1;
                    int len = strlen(fields[i]);

                    for(int j = 0; j < len; j++)
                        if(fields[i][j] == ',')
                            count++;

                    entry->genreCount = count;
                    entry->genres = (char **)malloc(count * sizeof(char*));
                    
                    for(int j = 0; j < count; j++) {
                        entry->genres[j] = (char *)malloc(len * sizeof(char));
                    }

                    for(int j = 0, k = 0, l = 0; j < len; j++) {
                        if(fields[i][j] != ',') {
                            entry->genres[k][l++] = fields[i][j];
                        } else if(fields[i][j] == ',') {
                            entry->genres[k++][l] = '\0';
                            l = 0;
                            if(fields[i][j + 1] == ' ') {
                                j++;
                            }
                        }
                    }

                    for(int j = 0; j < entry->genreCount - 1; j++) {
                        int min = j;
                        for(int k = j + 1; k < entry->genreCount; k++) {
                            if(strcmp(entry->genres[k], entry->genres[min]) < 0) {
                                min = k;
                            }
                        }
                        char *temp = entry->genres[j];
                        entry->genres[j] = entry->genres[min];
                        entry->genres[min] = temp;
                    }
                } else {
                    entry->genreCount = 0;
                    entry->genres = NULL;
                }
                break;
        }
    }
}

void readFileLine(char *buffer, int maxSize, FILE *file) {
    if (file == NULL) {
        fprintf(stderr, "Error: NULL file pointer passed to readFileLine().\n");
        exit(1);
    }

    if (fgets(buffer, maxSize, file) == NULL) {
        fprintf(stderr, "Error reading line from file or EOF reached.\n");
        exit(1);
    }
    size_t len = strlen(buffer);
    if(buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

void freeMediaEntry(MediaEntry *entry) {
    free(entry->id);
    free(entry->contentType);
    free(entry->title);
    free(entry->directorName);
    free(entry->country);
    free(entry->rating);
    free(entry->duration);
    if(entry->actors != NULL) {
        for(int j = 0; j < entry->actorCount; j++) {
            free(entry->actors[j]);
        }
        free(entry->actors);
    }
    if(entry->genres != NULL) {
        for(int j = 0; j < entry->genreCount; j++) {
            free(entry->genres[j]);
        }
        free(entry->genres);
    }
}

void swapEntries(MediaEntry *a, MediaEntry *b) {
    MediaEntry temp = *a;
    *a = *b;
    *b = temp;
}

int compareMediaEntries(MediaEntry a, MediaEntry b, int *comparisons) {
    (*comparisons)++;
    
    int cmp = strcmp(a.directorName, b.directorName);
    if (cmp != 0) return cmp;
    
    return strcmp(a.title, b.title);
}

void heapifyEntries(MediaEntry *arr, int n, int i, int *comparisons) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compareMediaEntries(arr[left], arr[smallest], comparisons) > 0)
        smallest = left;

    if (right < n && compareMediaEntries(arr[right], arr[smallest], comparisons) > 0)
        smallest = right;

    if (smallest != i) {
        swapEntries(&arr[i], &arr[smallest]);
        heapifyEntries(arr, n, smallest, comparisons);
    }
}

void partialHeapSortEntries(MediaEntry *arr, int n, int k, int *movements, int *comparisons) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyEntries(arr, n, i, comparisons);

    for (int i = n - 1; i >= 0; i--) {
        swapEntries(&arr[0], &arr[i]);
        (*movements)++;
        heapifyEntries(arr, i, 0, comparisons);
    }
}

int main() {
    if(debugMode) {
        debugLog = fopen("./ex17log.txt", "w");
        fprintf(debugLog, "-- MAIN --\n");
    }
    
    MediaEntry *mediaList = (MediaEntry *)calloc(1368, sizeof(MediaEntry));

    FILE *dataFile = fopen("/tmp/disneyplus.csv", "r");

    char *lineBuffer = (char *)malloc(1024 * sizeof(char));
    while(fgetc(dataFile) != '\n');

    for(int i = 0; i < 1368; i++) {
        readFileLine(lineBuffer, 1024, dataFile);
        parseMediaEntry((mediaList + i), lineBuffer);
    }
    
    free(lineBuffer);
    fclose(dataFile);

    char *input = (char *)malloc(255 * sizeof(char));
    scanf("%s", input);

    MediaEntry selectedEntries[1368];
    int selectedCount = 0;

    while(strcmp(input, "FIM") != 0) {
        int id = atoi((input + 1));
        selectedEntries[selectedCount++] = duplicateMedia(mediaList[--id]);
        scanf("%s", input);
    }

    int moveCount = 0;
    int compCount = 0;
    clock_t startTime = clock();
    partialHeapSortEntries(selectedEntries, selectedCount, 10, &moveCount, &compCount);
    clock_t endTime = clock();
    double duration = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    FILE *logFile = fopen("./853431_heapsortParcial.txt", "w");
    fprintf(logFile, "853431\t%d\t%d\t%.6f", compCount, moveCount, duration * 1000);
    fclose(logFile);

    for(int i = 0; i < 10; i++) {
        printMediaEntry(&selectedEntries[i]);
    }
    
    for(int i = 0; i < 1368; i++)
        freeMediaEntry(mediaList + i);
    free(mediaList);

    if(debugMode) {
        fclose(debugLog);
    }

    return 0;
}