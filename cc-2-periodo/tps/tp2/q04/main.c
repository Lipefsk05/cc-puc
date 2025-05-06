#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char *id;
    char *category;
    char *name;
    char *director;
    char **actors;
    size_t actors_count;
    char *country;
    Date added_on;
    int year_released;
    char *rating;
    char *runtime;
    char **tags;
    size_t tags_count;
} Show;

int convertMonthToNumber(char *month) {
    if (strcmp(month, "January") == 0) return 1;
    if (strcmp(month, "February") == 0) return 2;
    if (strcmp(month, "March") == 0) return 3;
    if (strcmp(month, "April") == 0) return 4;
    if (strcmp(month, "May") == 0) return 5;
    if (strcmp(month, "June") == 0) return 6;
    if (strcmp(month, "July") == 0) return 7;
    if (strcmp(month, "August") == 0) return 8;
    if (strcmp(month, "September") == 0) return 9;
    if (strcmp(month, "October") == 0) return 10;
    if (strcmp(month, "November") == 0) return 11;
    if (strcmp(month, "December") == 0) return 12;
    return 0;
}

char *convertNumberToMonth(int month_number) {
    char *month = (char *)malloc(25 * sizeof(char));
    switch (month_number) {
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
        default: printf("ERROR: Month not found\n");
    }
    return month;
}

char *intToString(int number) {
    char *str = (char *)malloc(12 * sizeof(char));
    sprintf(str, "%d", number);
    return str;
}

char *formatDate(Date date) {
    char *formatted_date = (char *)calloc(255, sizeof(char));
    char *month = convertNumberToMonth(date.month);
    char *day = intToString(date.day);
    char *year = intToString(date.year);

    strcat(formatted_date, month);
    strcat(formatted_date, " ");
    strcat(formatted_date, day);
    strcat(formatted_date, ", ");
    strcat(formatted_date, year);

    free(month);
    free(day);
    free(year);

    return formatted_date;
}

char *arrayToString(char **array, size_t length) {
    char *result = (char *)calloc(255, sizeof(char));
    for (int i = 0; i < length; i++) {
        strcat(result, array[i]);
        if (i != length - 1) strcat(result, ", ");
    }
    return result;
}

void displayShow(Show *show) {
    char *added_date;
    bool valid_date = (show->added_on.month != 0 && show->added_on.day != 0 && show->added_on.year != 0);

    if (valid_date) {
        added_date = formatDate(show->added_on);
    } else {
        added_date = (char *)calloc(5, sizeof(char));
        strcpy(added_date, "NaN");
    }

    char *actor_list;
    if (show->actors != NULL) {
        actor_list = arrayToString(show->actors, show->actors_count);
    } else {
        actor_list = (char *)calloc(5, sizeof(char));
        strcpy(actor_list, "NaN");
    }

    char *tag_list;
    if (show->tags != NULL) {
        tag_list = arrayToString(show->tags, show->tags_count);
    } else {
        tag_list = (char *)calloc(5, sizeof(char));
        strcpy(tag_list, "NaN");
    }

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           show->id, show->name, show->category, show->director, actor_list, show->country, added_date,
           show->year_released, show->rating, show->runtime, tag_list);

    free(added_date);
    free(tag_list);
    free(actor_list);
}

void parseShow(Show *show, char *line) {
    int len = strlen(line);
    char *attributes[11];
    int attribute_idx = 0, char_idx = 0;
    
    for (int i = 0; i < 11; i++) {
        attributes[i] = (char *)calloc(1024, sizeof(char));
        strcpy(attributes[i], "NaN");
    }
    
    for (int i = 0; i < len && attribute_idx < 11; i++) {
        if (line[i] != ',') {
            if (line[i] == '"') {
                i++;
                while (line[i] != '"') {
                    attributes[attribute_idx][char_idx++] = line[i++];
                }
            } else {
                attributes[attribute_idx][char_idx++] = line[i];
            }
        } else {
            attributes[attribute_idx][char_idx] = '\0';
            char_idx = 0;
            attribute_idx++;
            while (line[i + 1] == ',') {
                attributes[attribute_idx][char_idx++] = 'N';
                attributes[attribute_idx][char_idx++] = 'a';
                attributes[attribute_idx][char_idx++] = 'N';
                attributes[attribute_idx][char_idx] = '\0';
                i++;
                if (attribute_idx < 11) attribute_idx++;
                char_idx = 0;
            }
        }
    }

    for (int i = 0; i < 11; i++) {
        switch (i) {
            case 0:
                show->id = (char *)malloc(strlen(attributes[i]) + 1);
                strcpy(show->id, attributes[i]);
                break;
            case 1:
                show->category = (char *)malloc(strlen(attributes[i]) + 1);
                strcpy(show->category, attributes[i]);
                break;
            case 2:
                show->name = (char *)calloc(strlen(attributes[i]) + 1, sizeof(char));
                strcpy(show->name, attributes[i]);
                break;
            case 3:
                show->director = (char *)malloc(strlen(attributes[i]) + 1);
                strcpy(show->director, attributes[i]);
                break;
            case 4:
                if (strcmp(attributes[i], "NaN") != 0) {
                    int actor_count = 1;
                    int length = strlen(attributes[i]);
                    for (int j = 0; j < length; j++)
                        if (attributes[i][j] == ',') actor_count++;
                    show->actors_count = actor_count;
                    show->actors = (char **)calloc(actor_count, sizeof(char *));
                    for (int j = 0; j < actor_count; j++) {
                        show->actors[j] = (char *)calloc(length, sizeof(char));
                    }

                    for (int j = 0, k = 0, l = 0; j < length; j++) {
                        if (attributes[i][j] != ',') {
                            show->actors[k][l++] = attributes[i][j];
                        } else {
                            show->actors[k++][l] = '\0';
                            l = 0;
                            if (attributes[i][j + 1] == ' ') j++;
                        }
                    }

                    size_t count = show->actors_count;
                    for (int j = 0; j < count - 1; j++) {
                        int smallest = j;
                        for (int k = j + 1; k < count; k++) {
                            if (strcmp(show->actors[k], show->actors[smallest]) < 0) {
                                smallest = k;
                            }
                        }
                        char *temp = show->actors[j];
                        show->actors[j] = show->actors[smallest];
                        show->actors[smallest] = temp;
                    }
                } else {
                    show->actors_count = 0;
                    show->actors = NULL;
                }
                break;
            case 5:
                show->country = (char *)malloc(strlen(attributes[i]) + 1);
                strcpy(show->country, attributes[i]);
                break;
            case 6:
                if (strcmp(attributes[i], "NaN") != 0) {
                    int length = strlen(attributes[i]);
                    char month_str[length], day_str[length], year_str[length];
                    int k;

                    for (int j = 0; j < length; j++) {
                        if (attributes[i][j] != ' ') {
                            month_str[j] = attributes[i][j];
                        } else {
                            month_str[j] = '\0';
                            k = j + 1;
                            j = length;
                        }
                    }

                    for (int j = k, l = 0; j < length; j++) {
                        if (attributes[i][j] != ',') {
                            day_str[l++] = attributes[i][j];
                        } else {
                            day_str[l] = '\0';
                            k = j + 2;
                            j = length;
                        }
                    }

                    for (int j = k, l = 0; j < length; j++) {
                        year_str[l++] = attributes[i][j];
                        if (j == length - 1) year_str[l] = '\0';
                    }

                    show->added_on.month = convertMonthToNumber(month_str);
                    show->added_on.day = atoi(day_str);
                    show->added_on.year = atoi(year_str);
                } else {
                    show->added_on.month = 0;
                    show->added_on.day = 0;
                    show->added_on.year = 0;
                }
                break;
            case 7:
                show->year_released = atoi(attributes[i]);
                break;
            case 8:
                show->rating = (char *)malloc(strlen(attributes[i]) + 1);
                strcpy(show->rating, attributes[i]);
                break;
            case 9:
                show->runtime = (char *)malloc(strlen(attributes[i]) + 1);
                strcpy(show->runtime, attributes[i]);
                break;
            case 10:
                if (strcmp(attributes[i], "NaN") != 0) {
                    int tag_count = 1;
                    int length = strlen(attributes[i]);
                    for (int j = 0; j < length; j++)
                        if (attributes[i][j] == ',') tag_count++;
                    show->tags_count = tag_count;
                    show->tags = (char **)malloc(tag_count * sizeof(char *));
                    for (int j = 0; j < tag_count; j++) {
                        show->tags[j] = (char *)malloc(length * sizeof(char));
                    }

                    for (int j = 0, k = 0, l = 0; j < length; j++) {
                        if (attributes[i][j] != ',') {
                            show->tags[k][l++] = attributes[i][j];
                        } else {
                            show->tags[k++][l] = '\0';
                            l = 0;
                            if (attributes[i][j + 1] == ' ') j++;
                        }
                    }
                } else {
                    show->tags_count = 0;
                    show->tags = NULL;
                }
                break;
        }
    }
}

void readLineFromFile(char *line, int max_size, FILE *file) {
    if (file == NULL) {
        fprintf(stderr, "Error: NULL file pointer passed to readLineFromFile().\n");
        exit(1);
    }

    if (fgets(line, max_size, file) == NULL) {
        fprintf(stderr, "Error reading line from file or EOF reached.\n");
        exit(1);
    }
    size_t len = strlen(line);
    if (line[len - 1] == '\n') line[len - 1] = '\0';
}

void freeShow(Show *show) {
    free(show->id);
    free(show->category);
    free(show->name);
    free(show->director);
    free(show->country);
    free(show->rating);
    free(show->runtime);
    if (show->actors != NULL) {
        for (int i = 0; i < show->actors_count; i++) {
            free(show->actors[i]);
        }
        free(show->actors);
    }
    if (show->tags != NULL) {
        for (int i = 0; i < show->tags_count; i++) {
            free(show->tags[i]);
        }
        free(show->tags);
    }
}

#include <time.h>

#define MAX_SHOWS 1000
#define MAX_LINE 1024
#define MATRICULA "858158" // Substitua pela sua matrícula real

int main() {
    Show shows[MAX_SHOWS];
    int show_count = 0;
    char line[MAX_LINE];

    // Leitura da primeira parte (registros)
    while (fgets(line, MAX_LINE, stdin)) {
        if (line[0] == '\n' || strcmp(line, "\n") == 0) continue;
        if (line[0] == 'F' && line[1] == 'I' && line[2] == 'M') break;

        readLineFromFile(line, MAX_LINE, stdin); // ou só usar `line` diretamente
        parseShow(&shows[show_count++], line);
    }

    // Leitura da segunda parte (títulos a pesquisar)
    int comparisons = 0;
    clock_t start = clock();

    while (fgets(line, MAX_LINE, stdin)) {
        if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
        if (strcmp(line, "FIM") == 0) break;

        bool found = false;
        for (int i = 0; i < show_count; i++) {
            comparisons++;
            if (strcmp(shows[i].name, line) == 0) {
                found = true;
                break;
            }
        }
        printf("%s\n", found ? "SIM" : "NAO");
    }

    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Gerar arquivo de log
    FILE *log = fopen(MATRICULA "_sequencial.txt", "w");
    if (log != NULL) {
        fprintf(log, "%s\t%f\t%d\n", MATRICULA, elapsed_time, comparisons);
        fclose(log);
    } else {
        fprintf(stderr, "Erro ao criar arquivo de log.\n");
    }

    // Liberar memória
    for (int i = 0; i < show_count; i++) {
        freeShow(&shows[i]);
    }

    return 0;
}
