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
    char *contentType;
    char *title;
    char *director;
    char **cast;
    size_t castSize;
    char *country;
    Date addedDate;
    int releaseYear;
    char *rating;
    char *duration;
    char **genres;
    size_t genresSize;
} MediaItem;

MediaItem cloneMedia(MediaItem original) {
    MediaItem copy;

    copy.id = (char *)calloc(strlen(original.id) + 1, sizeof(char));
    strcpy(copy.id, original.id);

    copy.contentType = (char *)calloc(strlen(original.contentType) + 1, sizeof(char));
    strcpy(copy.contentType, original.contentType);

    copy.title = (char *)calloc(strlen(original.title) + 1, sizeof(char));
    strcpy(copy.title, original.title);

    copy.director = (char *)calloc(strlen(original.director) + 1, sizeof(char));
    strcpy(copy.director, original.director);

    copy.castSize = original.castSize;

    if(copy.castSize > 0) {
        copy.cast = (char **)calloc(copy.castSize, sizeof(char *));
        for(int i = 0; i < copy.castSize; i++) {
            copy.cast[i] = (char *)calloc(strlen(original.cast[i]) + 1, sizeof(char));
            strcpy(copy.cast[i], original.cast[i]);
        }
    } else {
        copy.cast = NULL;
    }

    copy.country = (char *)calloc(strlen(original.country) + 1, sizeof(char));
    strcpy(copy.country, original.country);

    copy.addedDate = original.addedDate;

    copy.releaseYear = original.releaseYear;

    copy.rating = (char *)calloc(strlen(original.rating) + 1, sizeof(char));
    strcpy(copy.rating, original.rating);

    copy.duration = (char *)calloc(strlen(original.duration) + 1, sizeof(char));
    strcpy(copy.duration, original.duration);

    copy.genresSize = original.genresSize;

    if(copy.genresSize > 0) {
        copy.genres = (char **)calloc(copy.genresSize, sizeof(char *));
        for(int i = 0; i < copy.genresSize; i++) {
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

int monthToNumber(char *month) {
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

char *numberToMonth(int num) {
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

char *intToString(int num) {
    char *str = (char *)malloc(12 * sizeof(char));
    sprintf(str, "%d", num);
    return str;
}

char* formatDate(Date date) {
    char *formatted = (char *)calloc(255, sizeof(char));
    char *month = numberToMonth(date.month);
    char *day = intToString(date.day);
    char *year = intToString(date.year);

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

char* arrayToString(char **array, size_t size) {
    char *result = (char *)calloc(255, sizeof(char));

    for(int i = 0; i < size; i++) {
        strcat(result, array[i]);
        if(i != size - 1)
            strcat(result, ", ");
    }

    return result;
}

void printMedia(MediaItem *item) {
    char *dateStr;

    bool hasMonth = (item->addedDate.month != 0);
    bool hasDay = (item->addedDate.day != 0);
    bool hasYear = (item->addedDate.year != 0);

    if(hasMonth && hasDay && hasYear) {
        dateStr = formatDate(item->addedDate);
    } else {
        dateStr = (char *)calloc(5, sizeof(char));
        strcpy(dateStr, "NaN");
    }

    char* castStr;
    if(item->cast != NULL) {
        castStr = arrayToString(item->cast, item->castSize);
    } else {
        castStr = (char *)calloc(5, sizeof(char));
        strcpy(castStr, "NaN");
    }
    
    char* genresStr;
    if(item->genres != NULL) {
        genresStr = arrayToString(item->genres, item->genresSize);
    } else {
        genresStr = (char *)calloc(5, sizeof(char));
        strcpy(genresStr, "NaN");
    }

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           item->id, item->title, item->contentType, item->director, castStr,
           item->country, dateStr, item->releaseYear, item->rating, item->duration, genresStr);

    free(dateStr);
    free(genresStr);
    free(castStr);
}

void parseMedia(MediaItem *item, char *line) {
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
                item->id = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->id, fields[i]);
                break;
            case 1:
                item->contentType = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->contentType, fields[i]);
                break;
            case 2:
                item->title = (char *)calloc((strlen(fields[i]) + 1), sizeof(char));
                strcpy(item->title, fields[i]);
                break;
            case 3:
                item->director = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->director, fields[i]);
                break;
            case 4:
                if(strcmp(fields[i], "NaN") != 0 || strlen(fields[i]) != 0) {
                    int count = 1;
                    int len = strlen(fields[i]);

                    for(int j = 0; j < len; j++)
                        if(fields[i][j] == ',')
                            count++;

                    item->castSize = count;
                    item->cast = (char **)calloc(count, sizeof(char*));
                    
                    for(int j = 0; j < count; j++) {
                        item->cast[j] = (char *)calloc(len, sizeof(char));
                    }

                    for(int j = 0, k = 0, l = 0; j < len; j++) {
                        if(fields[i][j] != ',') {
                            item->cast[k][l++] = fields[i][j];
                        } else if(fields[i][j] == ',') {
                            item->cast[k++][l] = '\0';
                            l = 0;
                            if(fields[i][j + 1] == ' ') {
                                j++;
                            }
                        }
                    }

                    for(int j = 0; j < item->castSize - 1; j++) {
                        int min = j;
                        for(int k = j + 1; k < item->castSize; k++) {
                            if(strcmp(item->cast[k], item->cast[min]) < 0) {
                                min = k;
                            }
                        }
                        char *temp = item->cast[j];
                        item->cast[j] = item->cast[min];
                        item->cast[min] = temp;
                    }
                } else {
                    item->castSize = 0;
                    item->cast = NULL;
                }
                break;
            case 5:
                item->country = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->country, fields[i]);
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

                    item->addedDate.month = monthToNumber(monthStr);
                    item->addedDate.day = atoi(dayStr);
                    item->addedDate.year = atoi(yearStr);
                } else {
                    item->addedDate.month = 3;
                    item->addedDate.day = 1;
                    item->addedDate.year = 1900;
                }
                break;
            case 7:
                item->releaseYear = atoi(fields[i]);
                break;
            case 8:
                item->rating = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->rating, fields[i]);
                break;
            case 9:
                item->duration = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->duration, fields[i]);
                break;
            case 10:
                if(strcmp(fields[i], "NaN") != 0) {
                    int count = 1;
                    int len = strlen(fields[i]);

                    for(int j = 0; j < len; j++)
                        if(fields[i][j] == ',')
                            count++;

                    item->genresSize = count;
                    item->genres = (char **)malloc(count * sizeof(char*));
                    
                    for(int j = 0; j < count; j++) {
                        item->genres[j] = (char *)malloc(len * sizeof(char));
                    }

                    for(int j = 0, k = 0, l = 0; j < len; j++) {
                        if(fields[i][j] != ',') {
                            item->genres[k][l++] = fields[i][j];
                        } else if(fields[i][j] == ',') {
                            item->genres[k++][l] = '\0';
                            l = 0;
                            if(fields[i][j + 1] == ' ') {
                                j++;
                            }
                        }
                    }

                    for(int j = 0; j < item->genresSize - 1; j++) {
                        int min = j;
                        for(int k = j + 1; k < item->genresSize; k++) {
                            if(strcmp(item->genres[k], item->genres[min]) < 0) {
                                min = k;
                            }
                        }
                        char *temp = item->genres[j];
                        item->genres[j] = item->genres[min];
                        item->genres[min] = temp;
                    }
                } else {
                    item->genresSize = 0;
                    item->genres = NULL;
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

void freeMedia(MediaItem *item) {
    free(item->id);
    free(item->contentType);
    free(item->title);
    free(item->director);
    free(item->country);
    free(item->rating);
    free(item->duration);
    if(item->cast != NULL) {
        for(int j = 0; j < item->castSize; j++) {
            free(item->cast[j]);
        }
        free(item->cast);
    }
    if(item->genres != NULL) {
        for(int j = 0; j < item->genresSize; j++) {
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

int compareMediaItems(MediaItem a, MediaItem b, int *movements, int *comparisons) {
    int result = 0;
    if(compareDates(a.addedDate, b.addedDate) != 0) {
        (*comparisons)++;
        result = compareDates(a.addedDate, b.addedDate);
    } else {
        (*comparisons)+=2;
        char *aTitle = convertToLowercase(a.title);
        char *bTitle = convertToLowercase(b.title);

        result = strcmp(aTitle, bTitle);

        free(aTitle);
        free(bTitle);
    }
    return result;
}

void quickSort(MediaItem *array, int left, int right, int *movements, int *comparisons) {
    int i = left, j = right; 
    MediaItem pivot = array[(left + right) / 2];
    while(i <= j) {
        while(compareMediaItems(array[i], pivot, movements, comparisons) < 0) {
            i++;
        }
        while(compareMediaItems(array[j], pivot, movements, comparisons) > 0) {
            j--;
        }
        if(i <= j) {
            (*movements)++;
            MediaItem temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if(left < j) {
        quickSort(array, left, j, movements, comparisons);
    }
    if(right > i) {
        quickSort(array, i, right, movements, comparisons);
    }
}

int main() {
    MediaItem *mediaList = (MediaItem *)calloc(1368, sizeof(MediaItem));

    FILE *dataFile = fopen("/tmp/disneyplus.csv", "r");

    char *lineBuffer = (char *)malloc(1024 * sizeof(char));
    while(fgetc(dataFile) != '\n');

    for(int i = 0; i < 1368; i++) {
        readFileLine(lineBuffer, 1024, dataFile);
        parseMedia((mediaList + i), lineBuffer);
    }
    
    free(lineBuffer);
    fclose(dataFile);

    char *input = (char *)malloc(255 * sizeof(char));
    scanf("%s", input);

    MediaItem *selectedItems = (MediaItem *)calloc(1368, sizeof(MediaItem));
    int selectedCount = 0;

    while(strcmp(input, "FIM") != 0) {
        int id = atoi((input + 1));
        selectedItems[selectedCount++] = cloneMedia(mediaList[--id]);
        scanf("%s", input);
    }

    int moveCount = 0;
    int compCount = 0;
    clock_t startTime = clock();
    quickSort(selectedItems, 0, selectedCount - 1, &moveCount, &compCount);
    clock_t endTime = clock();
    double duration = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    FILE *logFile = fopen("./853431_quicksort.txt", "w");
    fprintf(logFile, "853431\t%d\t%d\t%.6f", compCount, moveCount, duration * 1000);
    fclose(logFile);

    for(int i = 0; i < selectedCount; i++) {
        printMedia(&selectedItems[i]);
    }
    
    for(int i = 0; i < 1368; i++)
        freeMedia(mediaList + i);
    for(int i = 0; i < 1368; i++) {
        freeMedia(selectedItems + i);
    }
    free(mediaList);
    free(selectedItems);

    return 0;
}