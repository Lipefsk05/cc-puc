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
    char *origin;
    Date added_date;
    int year;
    char *age_rating;
    char *length;
    char **genres;
    size_t genre_count;
} Media;

Media copyMedia(Media original) {
    Media copy;

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

    copy.origin = (char *)calloc(strlen(original.origin) + 1, sizeof(char));
    strcpy(copy.origin, original.origin);

    copy.added_date = original.added_date;

    copy.year = original.year;

    copy.age_rating = (char *)calloc(strlen(original.age_rating) + 1, sizeof(char));
    strcpy(copy.age_rating, original.age_rating);

    copy.length = (char *)calloc(strlen(original.length) + 1, sizeof(char));
    strcpy(copy.length, original.length);

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

char* convertToLower(char *str) {
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

int getMonthNumber(char *month) {
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

char *getMonthName(int month) {
    char *name = (char *)malloc(25 * sizeof(char));
    
    switch(month) {
        case 1: strcpy(name, "January"); break;
        case 2: strcpy(name, "February"); break;
        case 3: strcpy(name, "March"); break;
        case 4: strcpy(name, "April"); break;
        case 5: strcpy(name, "May"); break;
        case 6: strcpy(name, "June"); break;
        case 7: strcpy(name, "July"); break;
        case 8: strcpy(name, "August"); break;
        case 9: strcpy(name, "September"); break;
        case 10: strcpy(name, "October"); break;
        case 11: strcpy(name, "November"); break;
        case 12: strcpy(name, "December"); break;
        default: printf("ERROR: Month not found"); break;
    }

    return name;
}

char *intToString(int num) {
    char *str = (char *)malloc(12 * sizeof(char));
    sprintf(str, "%d", num);
    return str;
}

char* formatDate(Date date) {
    char *formatted = (char *)calloc(255, sizeof(char));
    char *month = getMonthName(date.month);
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

char* arrayToStr(char **array, size_t size) {
    char *result = (char *)calloc(255, sizeof(char));

    for(int i = 0; i < size; i++) {
        strcat(result, array[i]);
        if(i != size - 1)
            strcat(result, ", ");
    }

    return result;
}

void display(Media *item) {
    char *date_str;

    bool hasMonth = (item->added_date.month != 0);
    bool hasDay = (item->added_date.day != 0);
    bool hasYear = (item->added_date.year != 0);

    if(hasMonth && hasDay && hasYear) {
        date_str = formatDate(item->added_date);
    } else {
        date_str = (char *)calloc(5, sizeof(char));
        strcpy(date_str, "NaN");
    }

    char* actors_str;
    if(item->actors != NULL) {
        actors_str = arrayToStr(item->actors, item->actor_count);
    } else {
        actors_str = (char *)calloc(5, sizeof(char));
        strcpy(actors_str, "NaN");
    }
    
    char* genres_str;
    if(item->genres != NULL) {
        genres_str = arrayToStr(item->genres, item->genre_count);
    } else {
        genres_str = (char *)calloc(5, sizeof(char));
        strcpy(genres_str, "NaN");
    }

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           item->id, item->name, item->category, item->director_name, actors_str,
           item->origin, date_str, item->year, item->age_rating, item->length, genres_str);

    free(date_str);
    free(genres_str);
    free(actors_str);
}

void parse(Media *item, char *line) {
    int length = strlen(line);
    char *fields[11];
    int field_num = 0;
    int char_pos = 0;
    
    for(int i = 0; i < 11; i++) {
        fields[i] = (char *)calloc(1024, sizeof(char));
        strcpy(fields[i], "NaN");
    }
    
    for(int i = 0; i < length && field_num < 11; i++) {
        if(line[i] != ',') {
            if(line[i] == '"') {
                i++;
                while(line[i] != '"') {
                    fields[field_num][char_pos++] = line[i++];
                }
            } else {
                fields[field_num][char_pos++] = line[i];
            }
        } else {
            fields[field_num][char_pos] = '\0';
            char_pos = 0;
            field_num++;
            while(line[i + 1] == ',') {
                fields[field_num][char_pos++] = 'N';
                fields[field_num][char_pos++] = 'a';
                fields[field_num][char_pos++] = 'N';
                fields[field_num][char_pos] = '\0';
                i++;
                if(field_num < 11)
                    field_num++;
                char_pos = 0;
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
                item->category = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->category, fields[i]);
                break;
            case 2:
                item->name = (char *)calloc((strlen(fields[i]) + 1), sizeof(char));
                strcpy(item->name, fields[i]);
                break;
            case 3:
                item->director_name = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->director_name, fields[i]);
                break;
            case 4:
                if(strcmp(fields[i], "NaN") != 0 || strlen(fields[i]) != 0) {
                    int count = 1;
                    int len = strlen(fields[i]);

                    for(int j = 0; j < len; j++)
                        if(fields[i][j] == ',')
                            count++;

                    item->actor_count = count;
                    item->actors = (char **)calloc(count, sizeof(char*));
                    
                    for(int j = 0; j < count; j++) {
                        item->actors[j] = (char *)calloc(len, sizeof(char));
                    }

                    for(int j = 0, k = 0, l = 0; j < len; j++) {
                        if(fields[i][j] != ',') {
                            item->actors[k][l++] = fields[i][j];
                        } else if(fields[i][j] == ',') {
                            item->actors[k++][l] = '\0';
                            l = 0;
                            if(fields[i][j + 1] == ' ') {
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
                item->origin = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->origin, fields[i]);
                break;
            case 6:
                if(strcmp(fields[i], "NaN") != 0) {
                    int len = strlen(fields[i]);
                    char month_str[len];
                    char day_str[len];
                    char year_str[len];

                    int pos;
                    for(int j = 0; j < len; j++) {
                        if(fields[i][j] != ' ') {
                            month_str[j] = fields[i][j];
                        } else {
                            month_str[j] = '\0';
                            pos = j + 1;
                            j = len;
                        }
                    }
                    for(int j = pos, l = 0; j < len; j++) {
                        if(fields[i][j] != ',') {
                            day_str[l++] = fields[i][j];
                        } else {
                            day_str[l] = '\0';
                            pos = j + 2;
                            j = len;
                        }
                    }
                    for(int j = pos, l = 0; j < len; j++) {
                        year_str[l++] = fields[i][j];
                        if(j == len - 1)
                            year_str[l] = '\0';
                    }

                    item->added_date.month = getMonthNumber(month_str);
                    item->added_date.day = atoi(day_str);
                    item->added_date.year = atoi(year_str);
                } else {
                    item->added_date.month = 3;
                    item->added_date.day = 1;
                    item->added_date.year = 1900;
                }
                break;
            case 7:
                item->year = atoi(fields[i]);
                break;
            case 8:
                item->age_rating = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->age_rating, fields[i]);
                break;
            case 9:
                item->length = (char *)malloc((strlen(fields[i]) + 1) * sizeof(char));
                strcpy(item->length, fields[i]);
                break;
            case 10:
                if(strcmp(fields[i], "NaN") != 0) {
                    int count = 1;
                    int len = strlen(fields[i]);

                    for(int j = 0; j < len; j++)
                        if(fields[i][j] == ',')
                            count++;

                    item->genre_count = count;
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
        fprintf(stderr, "Error reading line from file or EOF reached.\n");
        exit(1);
    }
    
    size_t len = strlen(buffer);
    if(buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

void cleanupMedia(Media *item) {
    free(item->id);
    free(item->category);
    free(item->name);
    free(item->director_name);
    free(item->origin);
    free(item->age_rating);
    free(item->length);
    
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

bool compareMedia(Media first, Media second, int *comparisons) {
    int firstYear = first.year;
    int secondYear = second.year;
    char *firstName = convertToLower(first.name);
    char *secondName = convertToLower(second.name);

    bool result = (firstYear == secondYear &&
            strcmp(firstName, secondName) < 0);

    if(result)
        *comparisons += 2;

    free(firstName);
    free(secondName);

    return result;
}

int findMaxYear(Media *array, int size) {
    int max = array[0].year;
    for(int i = 0; i < size; i++) {
        if(max < array[i].year) {
            max = array[i].year;
        }
    }
    return max;
}

Media* sortByDigit(Media *array, int size, int exp, int *moves, int *comparisons) {
    Media *output = (Media *)calloc(size, sizeof(Media));  
    int count[10] = {0};

    for(int i = 0; i < size; count[(array[i].year / exp) % 10]++ , i++);

    for(int i = 1; i < 10; count[i] += count[i - 1], i++);

    for(int i = size - 1; i >= 0; i--) {
        (*moves)++;
        output[count[(array[i].year / exp) % 10] - 1] = copyMedia(array[i]);
        count[(array[i].year / exp) % 10]--;
    }

    for(int i = 0; i < size; i++) {
        (*moves)++;
        array[i] = output[i];
    }

    return output;
}

void radixSort(Media *array, int size, int *moves, int *comparisons) {
    int max = findMaxYear(array, size);
    Media *output;
    
    for(int exp = 1; max / exp > 0; exp *= 10) {
        output = sortByDigit(array, size, exp, moves, comparisons);
    }

    // Insertion sort to handle titles with same year
    for(int i = 1; i < size; i++) {
        Media temp = output[i];
        int j = i - 1;
        while(j >= 0 && compareMedia(temp, output[j], comparisons)) {
            (*moves)++;
            output[j + 1] = output[j];
            j--;
        }
        if(i != (j + 1)) {
            (*moves)++;
            output[j + 1] = temp;
        }
    }

    for(int i = 0; i < size; i++) {
        display(output + i);
    }
    free(output);
}

int main() {
    Media *catalog = (Media *)calloc(1368, sizeof(Media));

    FILE *dataFile = fopen("/tmp/disneyplus.csv", "r");

    char *lineBuffer = (char *)malloc(1024 * sizeof(char));
    while(fgetc(dataFile) != '\n');

    for(int i = 0; i < 1368; i++) {
        readCSVLine(lineBuffer, 1024, dataFile);
        parse((catalog + i), lineBuffer);
    }
    
    free(lineBuffer);
    fclose(dataFile);

    char *input = (char *)malloc(255 * sizeof(char));
    scanf("%s", input);

    Media selected[1368];
    int selectedCount = 0;

    while(strcmp(input, "FIM") != 0) {
        int id = atoi((input + 1));
        selected[selectedCount++] = copyMedia(catalog[--id]);
        scanf("%s", input);
    }

    int moveCount = 0;
    int compareCount = 0;
    clock_t startTime = clock();
    radixSort(selected, selectedCount, &moveCount, &compareCount);
    clock_t endTime = clock();
    double timeTaken = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    FILE *logFile = fopen("./853431_radixsort.txt", "w");
    fprintf(logFile, "853431\t%d\t%d\t%.6f", compareCount, moveCount, timeTaken * 1000);
    fclose(logFile);

    for(int i = 0; i < 1368; i++)
        cleanupMedia(catalog + i);
    free(catalog);

    return 0;
}