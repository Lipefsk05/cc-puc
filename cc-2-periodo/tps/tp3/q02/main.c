#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ----------------- CONSTANTS -----------------
#define MAX_SHOWS 1368
#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256
#define CSV_FILE_PATH "/tmp/disneyplus.csv"

// ----------------- DATA STRUCTURES -----------------
typedef struct {
    int date;
    int month;
    int year;
} DATE;

typedef struct {
    char *show_id;
    char *type;
    char *title;
    char *director;
    char **cast;
    size_t castLen;
    char *country;
    DATE date_added;
    int release_year;
    char *rating;
    char *duration;
    char **listed_in;
    size_t listedLen;
} SHOW;

typedef struct {
    SHOW *array;
    int tam; // Current number of elements in the list
    int capacity; // Max capacity of the list
} LISTA;

// ----------------- FUNCTION PROTOTYPES -----------------
// Helper Functions
char* duplicate_string(const char* str);
int month_to_int(const char* month_name);
char* int_to_month_string(int month_num);
int string_comparator(const void* a, const void* b);

// SHOW struct functions
void ler(SHOW *show_instance, char *line);
void imprimir(SHOW *show_instance);
SHOW clone(SHOW original_show);
void freeShow(SHOW *show_instance);

// LISTA struct functions
LISTA* new_lista(int capacity);
void free_lista(LISTA *lista);
void inserirInicio(LISTA *lista, SHOW show);
void inserir(LISTA *lista, SHOW show, int pos);
void inserirFim(LISTA *lista, SHOW show);
SHOW removerInicio(LISTA *lista);
SHOW remover(LISTA *lista, int pos);
SHOW removerFim(LISTA *lista);
void mostrarRestante(LISTA *lista);

// ----------------- HELPER IMPLEMENTATIONS -----------------

// Safely duplicates a string, handling memory allocation.
char* duplicate_string(const char* str) {
    if (!str) return NULL;
    char* new_str = (char*)malloc(strlen(str) + 1);
    if (new_str) {
        strcpy(new_str, str);
    } else {
        perror("Failed to allocate memory for string duplication");
        exit(EXIT_FAILURE);
    }
    return new_str;
}

// Converts a month name string to its integer representation.
int month_to_int(const char* month_name) {
    const char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    for (int i = 0; i < 12; i++) {
        if (strcmp(month_name, months[i]) == 0) {
            return i + 1;
        }
    }
    return 0; // Return 0 if not found
}

// Converts a month integer to its string representation.
char* int_to_month_string(int month_num) {
    const char* month_str;
    switch (month_num) {
        case 1:  month_str = "January";   break;
        case 2:  month_str = "February";  break;
        case 3:  month_str = "March";     break;
        case 4:  month_str = "April";     break;
        case 5:  month_str = "May";       break;
        case 6:  month_str = "June";      break;
        case 7:  month_str = "July";      break;
        case 8:  month_str = "August";    break;
        case 9:  month_str = "September"; break;
        case 10: month_str = "October";   break;
        case 11: month_str = "November";  break;
        case 12: month_str = "December";  break;
        default: month_str = "Invalid";   break;
    }
    return duplicate_string(month_str);
}

// Comparator function for qsort, used for string arrays.
int string_comparator(const void* a, const void* b) {
    const char* str_a = *(const char**)a;
    const char* str_b = *(const char**)b;
    return strcmp(str_a, str_b);
}

// ----------------- SHOW IMPLEMENTATIONS -----------------

// Deep copies a SHOW struct.
SHOW clone(SHOW show) {
    SHOW new_show;
    new_show.show_id = duplicate_string(show.show_id);
    new_show.type = duplicate_string(show.type);
    new_show.title = duplicate_string(show.title);
    new_show.director = duplicate_string(show.director);
    new_show.country = duplicate_string(show.country);
    new_show.rating = duplicate_string(show.rating);
    new_show.duration = duplicate_string(show.duration);
    
    new_show.date_added = show.date_added;
    new_show.release_year = show.release_year;
    
    new_show.castLen = show.castLen;
    if (new_show.castLen > 0) {
        new_show.cast = (char**)calloc(new_show.castLen, sizeof(char*));
        for (size_t i = 0; i < new_show.castLen; i++) {
            new_show.cast[i] = duplicate_string(show.cast[i]);
        }
    } else {
        new_show.cast = NULL;
    }

    new_show.listedLen = show.listedLen;
    if (new_show.listedLen > 0) {
        new_show.listed_in = (char**)calloc(new_show.listedLen, sizeof(char*));
        for (size_t i = 0; i < new_show.listedLen; i++) {
            new_show.listed_in[i] = duplicate_string(show.listed_in[i]);
        }
    } else {
        new_show.listed_in = NULL;
    }
    
    return new_show;
}

void imprimir(SHOW *show) {
    char date_str[MAX_FIELD_LENGTH];
    if (show->date_added.year != 0) {
        char *month_name = int_to_month_string(show->date_added.month);
        sprintf(date_str, "%s %d, %d", month_name, show->date_added.date, show->date_added.year);
        free(month_name);
    } else {
        strcpy(date_str, "NaN");
    }

    char cast_str[MAX_LINE_LENGTH] = "NaN";
    if (show->castLen > 0) {
        strcpy(cast_str, show->cast[0]);
        for (size_t i = 1; i < show->castLen; i++) {
            strcat(cast_str, ", ");
            strcat(cast_str, show->cast[i]);
        }
    }

    char listed_str[MAX_LINE_LENGTH] = "NaN";
    if (show->listedLen > 0) {
        strcpy(listed_str, show->listed_in[0]);
        for (size_t i = 1; i < show->listedLen; i++) {
            strcat(listed_str, ", ");
            strcat(listed_str, show->listed_in[i]);
        }
    }
    
    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
        show->show_id, show->title, show->type, show->director, cast_str,
        show->country, date_str, show->release_year, show->rating, show->duration, listed_str);
}


// Parses a single line from the CSV file.
void ler(SHOW *show_instance, char *line) {
    // This custom parser is preserved to maintain original functionality
    // with quoted fields and empty values.
    char* fields[11];
    for(int i = 0; i < 11; i++) fields[i] = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));

    int field_idx = 0, char_idx = 0;
    for (int i = 0; line[i] != '\0' && field_idx < 11; i++) {
        if (line[i] == '"') {
            i++; // Skip opening quote
            while (line[i] != '"') {
                fields[field_idx][char_idx++] = line[i++];
            }
        } else if (line[i] == ',') {
            if (char_idx == 0) strcpy(fields[field_idx], "NaN");
            fields[field_idx][char_idx] = '\0';
            field_idx++;
            char_idx = 0;
        } else {
            fields[field_idx][char_idx++] = line[i];
        }
    }
    fields[field_idx][char_idx] = '\0'; // Terminate last field

    // Assigning values from parsed fields
    show_instance->show_id = duplicate_string(fields[0]);
    show_instance->type = duplicate_string(fields[1]);
    show_instance->title = duplicate_string(fields[2]);
    show_instance->director = duplicate_string(fields[3]);
    show_instance->country = duplicate_string(fields[5]);

    if (strcmp(fields[6], "NaN") != 0) {
        char month_str[20], day_str[4], year_str[6];
        sscanf(fields[6], "%s %[^,], %s", month_str, day_str, year_str);
        show_instance->date_added.month = month_to_int(month_str);
        show_instance->date_added.date = atoi(day_str);
        show_instance->date_added.year = atoi(year_str);
    } else {
        show_instance->date_added = (DATE){1, 3, 1900};
    }

    show_instance->release_year = atoi(fields[7]);
    show_instance->rating = duplicate_string(fields[8]);
    show_instance->duration = duplicate_string(fields[9]);

    // Parse and sort 'cast' array
    if (strcmp(fields[4], "NaN") != 0) {
        show_instance->castLen = 1;
        for(int i=0; fields[4][i] != '\0'; i++) if(fields[4][i]==',') show_instance->castLen++;
        show_instance->cast = (char**)calloc(show_instance->castLen, sizeof(char*));
        char* token = strtok(fields[4], ",");
        for(int i=0; token != NULL; i++){
            while(*token == ' ') token++; // Trim leading space
            show_instance->cast[i] = duplicate_string(token);
            token = strtok(NULL, ",");
        }
        qsort(show_instance->cast, show_instance->castLen, sizeof(char*), string_comparator);
    } else {
        show_instance->cast = NULL;
        show_instance->castLen = 0;
    }
    
    // Parse and sort 'listed_in' array
    if (strcmp(fields[10], "NaN") != 0) {
        show_instance->listedLen = 1;
        for(int i=0; fields[10][i] != '\0'; i++) if(fields[10][i]==',') show_instance->listedLen++;
        show_instance->listed_in = (char**)calloc(show_instance->listedLen, sizeof(char*));
        char* token = strtok(fields[10], ",");
        for(int i=0; token != NULL; i++){
            while(*token == ' ') token++; // Trim leading space
            show_instance->listed_in[i] = duplicate_string(token);
            token = strtok(NULL, ",");
        }
        qsort(show_instance->listed_in, show_instance->listedLen, sizeof(char*), string_comparator);
    } else {
        show_instance->listed_in = NULL;
        show_instance->listedLen = 0;
    }

    for(int i=0; i<11; i++) free(fields[i]);
}

// Frees all dynamically allocated memory within a SHOW struct.
void freeShow(SHOW *show) {
    free(show->show_id);
    free(show->type);
    free(show->title);
    free(show->director);
    free(show->country);
    free(show->rating);
    free(show->duration);
    for (size_t i = 0; i < show->castLen; i++) free(show->cast[i]);
    free(show->cast);
    for (size_t i = 0; i < show->listedLen; i++) free(show->listed_in[i]);
    free(show->listed_in);
}

// ----------------- LISTA IMPLEMENTATIONS -----------------

LISTA* new_lista(int capacity) {
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA));
    if(!lista) exit(EXIT_FAILURE);
    lista->array = (SHOW*)calloc(capacity, sizeof(SHOW));
    if(!lista->array) exit(EXIT_FAILURE);
    lista->tam = 0;
    lista->capacity = capacity;
    return lista;
}

void free_lista(LISTA *lista) {
    if (!lista) return;
    // Note: The SHOW elements inside are clones and must be freed
    for (int i = 0; i < lista->tam; i++) {
        freeShow(&lista->array[i]);
    }
    free(lista->array);
    free(lista);
}

void inserirFim(LISTA *lista, SHOW show) {
    if (lista->tam < lista->capacity) {
        lista->array[lista->tam++] = clone(show);
    }
}

void inserirInicio(LISTA *lista, SHOW show) {
    if (lista->tam < lista->capacity) {
        memmove(&lista->array[1], &lista->array[0], lista->tam * sizeof(SHOW));
        lista->array[0] = clone(show);
        lista->tam++;
    }
}

void inserir(LISTA *lista, SHOW show, int pos) {
    if (lista->tam < lista->capacity && pos >= 0 && pos <= lista->tam) {
        memmove(&lista->array[pos + 1], &lista->array[pos], (lista->tam - pos) * sizeof(SHOW));
        lista->array[pos] = clone(show);
        lista->tam++;
    }
}

SHOW removerFim(LISTA *lista) {
    return lista->array[--lista->tam];
}

SHOW removerInicio(LISTA *lista) {
    SHOW removed = lista->array[0];
    lista->tam--;
    memmove(&lista->array[0], &lista->array[1], lista->tam * sizeof(SHOW));
    return removed;
}

SHOW remover(LISTA *lista, int pos) {
    SHOW removed = lista->array[pos];
    lista->tam--;
    memmove(&lista->array[pos], &lista->array[pos + 1], (lista->tam - pos) * sizeof(SHOW));
    return removed;
}

void mostrarRestante(LISTA *lista) {
    for (int i = 0; i < lista->tam; i++) {
        imprimir(&lista->array[i]);
    }
}

// ----------------- MAIN FUNCTION -----------------

int main() {
    SHOW all_shows[MAX_SHOWS];
    char line_buffer[MAX_LINE_LENGTH];

    FILE *file = fopen(CSV_FILE_PATH, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fgets(line_buffer, sizeof(line_buffer), file); // Skip header

    for (int i = 0; i < MAX_SHOWS; i++) {
        fgets(line_buffer, sizeof(line_buffer), file);
        line_buffer[strcspn(line_buffer, "\r\n")] = 0; // Remove newline
        ler(&all_shows[i], line_buffer);
    }
    fclose(file);

    LISTA *lista_shows = new_lista(MAX_SHOWS);
    char input_buffer[MAX_FIELD_LENGTH];

    scanf("%255s", input_buffer);
    while (strcmp(input_buffer, "FIM") != 0) {
        int id = atoi(input_buffer + 1); // Skip 's' prefix
        inserirFim(lista_shows, all_shows[id - 1]);
        scanf("%255s", input_buffer);
    }

    int num_ops;
    scanf("%d", &num_ops);
    
    for (int i = 0; i < num_ops; i++) {
        scanf("%255s", input_buffer);
        if (strcmp(input_buffer, "II") == 0) {
            scanf("%255s", input_buffer);
            inserirInicio(lista_shows, all_shows[atoi(input_buffer + 1) - 1]);
        } else if (strcmp(input_buffer, "IF") == 0) {
            scanf("%255s", input_buffer);
            inserirFim(lista_shows, all_shows[atoi(input_buffer + 1) - 1]);
        } else if (strcmp(input_buffer, "I*") == 0) {
            int pos;
            scanf("%d %255s", &pos, input_buffer);
            inserir(lista_shows, all_shows[atoi(input_buffer + 1) - 1], pos);
        } else if (strcmp(input_buffer, "RI") == 0) {
            SHOW removed = removerInicio(lista_shows);
            printf("(R) %s\n", removed.title);
            freeShow(&removed);
        } else if (strcmp(input_buffer, "RF") == 0) {
            SHOW removed = removerFim(lista_shows);
            printf("(R) %s\n", removed.title);
            freeShow(&removed);
        } else if (strcmp(input_buffer, "R*") == 0) {
            int pos;
            scanf("%d", &pos);
            SHOW removed = remover(lista_shows, pos);
            printf("(R) %s\n", removed.title);
            freeShow(&removed);
        }
    }

    mostrarRestante(lista_shows);

    // Final cleanup
    free_lista(lista_shows);
    for(int i = 0; i < MAX_SHOWS; i++) {
        freeShow(&all_shows[i]);
    }
    
    return EXIT_SUCCESS;
}