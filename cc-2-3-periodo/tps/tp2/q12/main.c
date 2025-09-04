#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char *id;
    char *category;
    char *name;
    char *director_name;
    char **actors;
    size_t actor_count;
    char *origin_country;
    Date added_date;
    int year_released;
    char *age_rating;
    char *runtime;
    char **genres;
    size_t genre_count;
} MediaItem;

MediaItem copyMediaItem(MediaItem original) {
    MediaItem copy;

    copy.id = (char *)calloc(strlen(original.id) + 1, sizeof(char));
    strcpy(copy.id, original.id);

    copy.category = (char *)calloc(strlen(original.category) + 1, sizeof(char));
    strcpy(copy.category, original.category);

    copy.name = (char *)calloc(strlen(original.name) + 1, sizeof(char));
    strcpy(copy.name, original.name);

    copy.director_name = (char *)calloc(strlen(original.director_name) + 1, sizeof(char));
    strcpy(copy.director_name, original.director_name);

    copy.actor_count = original.actor_count;

    if(copy.actor_count > 0) {
        copy.actors = (char **)calloc(copy.actor_count, sizeof(char *));
        for(int i = 0; i < copy.actor_count; i++) {
            copy.actors[i] = (char *)calloc(strlen(original.actors[i]) + 1, sizeof(char));
            strcpy(copy.actors[i], original.actors[i]);
        }
    } else {
        copy.actors = NULL;
    }

    copy.origin_country = (char *)calloc(strlen(original.origin_country) + 1, sizeof(char));
    strcpy(copy.origin_country, original.origin_country);

    copy.added_date = original.added_date;

    copy.year_released = original.year_released;

    copy.age_rating = (char *)calloc(strlen(original.age_rating) + 1, sizeof(char));
    strcpy(copy.age_rating, original.age_rating);

    copy.runtime = (char *)calloc(strlen(original.runtime) + 1, sizeof(char));
    strcpy(copy.runtime, original.runtime);

    copy.genre_count = original.genre_count;

    if(copy.genre_count > 0) {
        copy.genres = (char **)calloc(copy.genre_count, sizeof(char *));
        for(int i = 0; i < copy.genre_count; i++) {
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

int getMonthNumber(char *monthName) {
    int monthNum = 0;

    if(strcmp(monthName, "January") == 0) monthNum = 1; 
    if(strcmp(monthName, "February") == 0) monthNum = 2; 
    if(strcmp(monthName, "March") == 0) monthNum = 3; 
    if(strcmp(monthName, "April") == 0) monthNum = 4; 
    if(strcmp(monthName, "May") == 0) monthNum = 5; 
    if(strcmp(monthName, "June") == 0) monthNum = 6; 
    if(strcmp(monthName, "July") == 0) monthNum = 7; 
    if(strcmp(monthName, "August") == 0) monthNum = 8; 
    if(strcmp(monthName, "September") == 0) monthNum = 9; 
    if(strcmp(monthName, "October") == 0) monthNum = 10; 
    if(strcmp(monthName, "November") == 0) monthNum = 11; 
    if(strcmp(monthName, "December") == 0) monthNum = 12; 

    return monthNum;
}

char *getMonthName(int monthNum) {
    char *monthName = (char *)malloc(25 * sizeof(char));
    
    switch(monthNum) {
        case 1: strcpy(monthName, "January"); break;
        case 2: strcpy(monthName, "February"); break;
        case 3: strcpy(monthName, "March"); break;
        case 4: strcpy(monthName, "April"); break;
        case 5: strcpy(monthName, "May"); break;
        case 6: strcpy(monthName, "June"); break;
        case 7: strcpy(monthName, "July"); break;
        case 8: strcpy(monthName, "August"); break;
        case 9: strcpy(monthName, "September"); break;
        case 10: strcpy(monthName, "October"); break;
        case 11: strcpy(monthName, "November"); break;
        case 12: strcpy(monthName, "December"); break;
        default: printf("ERROR: Month not found"); break;
    }

    return monthName;
}

char *intToString(int num) {
    char *str = (char *)malloc(12 * sizeof(char));
    sprintf(str, "%d", num);
    return str;
}

char* formatDate(Date date) {
    char *dateStr = (char *)calloc(255, sizeof(char));
    char *monthName = getMonthName(date.month);
    char *dayStr = intToString(date.day);
    char *yearStr = intToString(date.year);

    strcat(dateStr, monthName);
    strcat(dateStr, " ");
    strcat(dateStr, dayStr);
    strcat(dateStr, ", ");
    strcat(dateStr, yearStr);

    free(monthName);
    free(dayStr);
    free(yearStr);

    return dateStr;
}

char* arrayToCSV(char **array, size_t length) {
    char *result = (char *)calloc(255, sizeof(char));

    for(int i = 0; i < length; i++) {
        strcat(result, array[i]);
        if(i != length - 1)
            strcat(result, ", ");
    }

    return result;
}

void displayMedia(MediaItem *item) {
    char *dateStr;

    bool hasMonth = (item->added_date.month != 0);
    bool hasDay = (item->added_date.day != 0);
    bool hasYear = (item->added_date.year != 0);

    if(hasMonth && hasDay && hasYear) {
        dateStr = formatDate(item->added_date);
    } else {
        dateStr = (char *)calloc(5, sizeof(char));
        strcpy(dateStr, "NaN");
    }

    char* actorsStr;
    if(item->actors != NULL) {
        actorsStr = arrayToCSV(item->actors, item->actor_count);
    } else {
        actorsStr = (char *)calloc(5, sizeof(char));
        strcpy(actorsStr, "NaN");
    }
    
    char* genresStr;
    if(item->genres != NULL) {
        genresStr = arrayToCSV(item->genres, item->genre_count);
    } else {
        genresStr = (char *)calloc(5, sizeof(char));
        strcpy(genresStr, "NaN");
    }

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           item->id, item->name, item->category, item->director_name, actorsStr, 
           item->origin_country, dateStr, item->year_released, item->age_rating, 
           item->runtime, genresStr);

    free(dateStr);
    free(genresStr);
    free(actorsStr);
}

void parseData(MediaItem *item, char *line) {
    int lineLength = strlen(line);
    char *attributes[11];
    int attrIndex = 0;
    int charIndex = 0;
    
    for(int i = 0; i < 11; i++) {
        attributes[i] = (char *)calloc(1024, sizeof(char));
        strcpy(attributes[i], "NaN");
    }
    
    for(int i = 0; i < lineLength && attrIndex < 11; i++) {
        if(line[i] != ',') {
            if(line[i] == '"') {
                i++;
                while(line[i] != '"') {
                    attributes[attrIndex][charIndex++] = line[i++];
                }
            } else {
                attributes[attrIndex][charIndex++] = line[i];
            }
        } else {
            attributes[attrIndex][charIndex] = '\0';
            charIndex = 0;
            attrIndex++;
            while(line[i + 1] == ',') {
                attributes[attrIndex][charIndex++] = 'N';
                attributes[attrIndex][charIndex++] = 'a';
                attributes[attrIndex][charIndex++] = 'N';
                attributes[attrIndex][charIndex] = '\0';
                i++;
                if(attrIndex < 11)
                    attrIndex++;
                charIndex = 0;
            }
        }
    }

    for(int i = 0; i < 11; i++) {
        switch(i) {
            case 0:
                item->id = strdup(attributes[i]);
                break;
            case 1:
                item->category = strdup(attributes[i]);
                break;
            case 2:
                item->name = strdup(attributes[i]);
                break;
            case 3:
                item->director_name = strdup(attributes[i]);
                break;
            case 4:
                if(strcmp(attributes[i], "NaN") != 0 || strlen(attributes[i]) != 0) {
                    int count = 1;
                    int len = strlen(attributes[i]);

                    for(int j = 0; j < len; j++)
                        if(attributes[i][j] == ',')
                            count++;

                    item->actor_count = count;
                    item->actors = (char **)calloc(count, sizeof(char*));
                    
                    for(int j = 0; j < count; j++) {
                        item->actors[j] = (char *)calloc(len, sizeof(char));
                    }

                    for(int j = 0, k = 0, l = 0; j < len; j++) {
                        if(attributes[i][j] != ',') {
                            item->actors[k][l++] = attributes[i][j];
                        } else if(attributes[i][j] == ',') {
                            item->actors[k++][l] = '\0';
                            l = 0;
                            if(attributes[i][j + 1] == ' ') {
                                j++;
                            }
                        }
                    }

                    for(int j = 0; j < item->actor_count - 1; j++) {
                        int min = j;
                        for(int k = j + 1; k < item->actor_count; k++) {
                            if(strcmp(item->actors[k], item->actors[min]) < 0) {
                                min = k;
                            }
                        }
                        char *temp = item->actors[j];
                        item->actors[j] = item->actors[min];
                        item->actors[min] = temp;
                    }
                } else {
                    item->actor_count = 0;
                    item->actors = NULL;
                }
                break;
            case 5:
                item->origin_country = strdup(attributes[i]);
                break;
            case 6:
                if(strcmp(attributes[i], "NaN") != 0) {
                    int len = strlen(attributes[i]);
                    char monthStr[len];
                    char dayStr[len];
                    char yearStr[len];

                    int pos;
                    for(int j = 0; j < len; j++) {
                        if(attributes[i][j] != ' ') {
                            monthStr[j] = attributes[i][j];
                        } else {
                            monthStr[j] = '\0';
                            pos = j + 1;
                            j = len;
                        }
                    }
                    for(int j = pos, k = 0; j < len; j++) {
                        if(attributes[i][j] != ',') {
                            dayStr[k++] = attributes[i][j];
                        } else {
                            dayStr[k] = '\0';
                            pos = j + 2;
                            j = len;
                        }
                    }
                    for(int j = pos, k = 0; j < len; j++) {
                        yearStr[k++] = attributes[i][j];
                        if(j == len - 1)
                            yearStr[k] = '\0';
                    }

                    item->added_date.month = getMonthNumber(monthStr);
                    item->added_date.day = atoi(dayStr);
                    item->added_date.year = atoi(yearStr);
                } else {
                    item->added_date.month = 3;
                    item->added_date.day = 1;
                    item->added_date.year = 1900;
                }
                break;
            case 7:
                item->year_released = atoi(attributes[i]);
                break;
            case 8:
                item->age_rating = strdup(attributes[i]);
                break;
            case 9:
                item->runtime = strdup(attributes[i]);
                break;
            case 10:
                if(strcmp(attributes[i], "NaN") != 0) {
                    int count = 1;
                    int len = strlen(attributes[i]);

                    for(int j = 0; j < len; j++)
                        if(attributes[i][j] == ',')
                            count++;

                    item->genre_count = count;
                    item->genres = (char **)calloc(count, sizeof(char*));
                    
                    for(int j = 0; j < count; j++) {
                        item->genres[j] = (char *)calloc(len, sizeof(char));
                    }

                    for(int j = 0, k = 0, l = 0; j < len; j++) {
                        if(attributes[i][j] != ',') {
                            item->genres[k][l++] = attributes[i][j];
                        } else if(attributes[i][j] == ',') {
                            item->genres[k++][l] = '\0';
                            l = 0;
                            if(attributes[i][j + 1] == ' ') {
                                j++;
                            }
                        }
                    }

                    for(int j = 0; j < item->genre_count - 1; j++) {
                        int min = j;
                        for(int k = j + 1; k < item->genre_count; k++) {
                            if(strcmp(item->genres[k], item->genres[min]) < 0) {
                                min = k;
                            }
                        }
                        char *temp = item->genres[j];
                        item->genres[j] = item->genres[min];
                        item->genres[min] = temp;
                    }
                } else {
                    item->genre_count = 0;
                    item->genres = NULL;
                }
                break;
        }
    }
}

void readCSVLine(char *buffer, int size, FILE *file) {
    if (file == NULL) {
        fprintf(stderr, "Error: NULL file pointer passed to readCSVLine().\n");
        exit(1);
    }

    if (fgets(buffer, size, file) == NULL) {
        fprintf(stderr, "Error reading line from file or end of file reached.\n");
        exit(1);
    }
    
    size_t len = strlen(buffer);
    if(buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

void freeMediaItem(MediaItem *item) {
    free(item->id);
    free(item->category);
    free(item->name);
    free(item->director_name);
    free(item->origin_country);
    free(item->age_rating);
    free(item->runtime);
    
    if(item->actors != NULL) {
        for(int j = 0; j < item->actor_count; j++) {
            free(item->actors[j]);
        }
        free(item->actors);
    }
    
    if(item->genres != NULL) {
        for(int j = 0; j < item->genre_count; j++) {
            free(item->genres[j]);
        }
        free(item->genres);
    }
}

int compareDates(Date date1, Date date2) {
    int result = 0;

    if(result == 0 && date1.year != date2.year) {
        result = (date1.year < date2.year) ? -1 : 1;
    }
    if(result == 0 && date1.month != date2.month) {
        result = (date1.month < date2.month) ? -1 : 1;
    }
    if(result == 0 && date1.day != date2.day) {
        result = (date1.day < date2.day) ? -1 : 1;
    }

    return result;
}

bool shouldSwap(MediaItem current, MediaItem next, int *comparisons) {
    char *currentTitle = convertToLowercase(current.name);
    char *nextTitle = convertToLowercase(next.name);

    bool condition1 = compareDates(current.added_date, next.added_date) > 0;
    if(condition1) *comparisons += 1;

    bool condition2 = (compareDates(current.added_date, next.added_date) == 0 &&
                     strcmp(currentTitle, nextTitle) > 0);
    if(condition2) *comparisons += 3;

    free(currentTitle);
    free(nextTitle);

    return (condition1 || condition2);
}

void bubbleSort(MediaItem *array, int length, int *swaps, int *comparisons) {
    for(int i = 0; i < length - 1; i++) {
        for(int j = 0; j < length - i - 1; j++) {
            if(shouldSwap(array[j], array[j + 1], comparisons)) {
                *swaps += 1;
                MediaItem temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    MediaItem *mediaList = (MediaItem *)calloc(1368, sizeof(MediaItem));

    FILE *inputFile = fopen("/tmp/disneyplus.csv", "r");

    char *lineBuffer = (char *)malloc(1024 * sizeof(char));
    while(fgetc(inputFile) != '\n');

    for(int i = 0; i < 1368; i++) {
        readCSVLine(lineBuffer, 1024, inputFile);
        parseData(&mediaList[i], lineBuffer);
    }
    
    free(lineBuffer);
    fclose(inputFile);

    char *inputID = (char *)malloc(255 * sizeof(char));
    scanf("%s", inputID);

    MediaItem *selectedItems = (MediaItem *)calloc(1368, sizeof(MediaItem));
    int selectedCount = 0;

    while(strcmp(inputID, "FIM") != 0) {
        int id = atoi((inputID + 1));
        selectedItems[selectedCount++] = copyMediaItem(mediaList[--id]);
        scanf("%s", inputID);
    }

    int swapCount = 0;
    int comparisonCount = 0;
    clock_t startTime = clock();
    bubbleSort(selectedItems, selectedCount, &swapCount, &comparisonCount);
    clock_t endTime = clock();
    double executionTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    FILE *logFile = fopen("./853431_bubble.txt", "w");
    fprintf(logFile, "853431\t%d\t%d\t%.6f", comparisonCount, swapCount, executionTime * 1000);
    fclose(logFile);

    for(int i = 0; i < selectedCount; i++) {
        displayMedia(&selectedItems[i]);
    }

    for(int i = 0; i < 1368; i++)
        freeMediaItem(&mediaList[i]);
    for(int i = 0; i < 1368; i++) {
        freeMediaItem(&selectedItems[i]);
    }
    free(mediaList);

    return 0;
}