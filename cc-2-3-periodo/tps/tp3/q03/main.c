#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ----------------- CONSTANTES GLOBAIS -----------------
#define MAX_SHOWS_IN_DB 1368
#define MAX_LINE_LEN 2048
#define MAX_FIELD_LEN 256
#define CSV_FILE_PATH "/tmp/disneyplus.csv"

// ----------------- ESTRUTURAS DE DADOS -----------------
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

// A estrutura PILHA é implementada como uma lista baseada em array.
typedef struct {
    SHOW *array;
    int tam;      // Número atual de elementos
    int capacity; // Capacidade máxima
} PILHA;

// ----------------- PROTÓTIPOS DAS FUNÇÕES -----------------
// Funções Auxiliares
char* safe_duplicate_string(const char* str);
int get_month_as_int(const char* month_name);
int compare_strings(const void* a, const void* b);

// Funções da struct SHOW
void ler(SHOW *show_item, char *line);
void imprimir(SHOW *show_item);
SHOW clone(SHOW original_show);
void freeShow(SHOW *show_item);

// Funções da struct PILHA
PILHA* new_pilha(int capacity);
void free_pilha(PILHA *p);
void inserir(PILHA *p, SHOW show);
SHOW remover(PILHA *p);
void mostrarRestante(PILHA *p);

// ----------------- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES -----------------

// Duplica uma string de forma segura, alocando memória e tratando erros.
char* safe_duplicate_string(const char* str) {
    if (!str) return NULL;
    char* new_str = (char*)malloc(strlen(str) + 1);
    if (!new_str) {
        perror("Falha ao alocar memoria para duplicar string");
        exit(EXIT_FAILURE);
    }
    strcpy(new_str, str);
    return new_str;
}

// Converte o nome de um mês para seu valor numérico.
int get_month_as_int(const char* month_name) {
    const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++) {
        if (strcmp(month_name, months[i]) == 0) {
            return i + 1;
        }
    }
    return 0; // Mês não encontrado
}

// Função de comparação para qsort.
int compare_strings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}


// ----------------- IMPLEMENTAÇÃO DAS FUNÇÕES DA STRUCT SHOW -----------------

// Cria uma cópia profunda (deep clone) de um SHOW.
SHOW clone(SHOW show) {
    SHOW new_show;
    new_show.show_id = safe_duplicate_string(show.show_id);
    new_show.type = safe_duplicate_string(show.type);
    new_show.title = safe_duplicate_string(show.title);
    new_show.director = safe_duplicate_string(show.director);
    new_show.country = safe_duplicate_string(show.country);
    new_show.rating = safe_duplicate_string(show.rating);
    new_show.duration = safe_duplicate_string(show.duration);
    
    new_show.date_added = show.date_added;
    new_show.release_year = show.release_year;
    
    new_show.castLen = show.castLen;
    if (new_show.castLen > 0) {
        new_show.cast = (char**)calloc(new_show.castLen, sizeof(char*));
        for (size_t i = 0; i < new_show.castLen; i++) {
            new_show.cast[i] = safe_duplicate_string(show.cast[i]);
        }
    } else {
        new_show.cast = NULL;
    }

    new_show.listedLen = show.listedLen;
    if (new_show.listedLen > 0) {
        new_show.listed_in = (char**)calloc(new_show.listedLen, sizeof(char*));
        for (size_t i = 0; i < new_show.listedLen; i++) {
            new_show.listed_in[i] = safe_duplicate_string(show.listed_in[i]);
        }
    } else {
        new_show.listed_in = NULL;
    }
    
    return new_show;
}


void imprimir(SHOW *show) {
    char date_str[MAX_FIELD_LEN];
    if (show->date_added.year != 0 && show->date_added.year != 1900) {
        // A lógica original considerava 1900 como NaN, então mantemos isso.
        const char* month_names[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        sprintf(date_str, "%s %d, %d", month_names[show->date_added.month], show->date_added.date, show->date_added.year);
    } else {
        strcpy(date_str, "NaN");
    }

    char cast_str[MAX_LINE_LEN] = "NaN";
    if (show->castLen > 0) {
        strcpy(cast_str, show->cast[0]);
        for (size_t i = 1; i < show->castLen; i++) {
            strcat(cast_str, ", ");
            strcat(cast_str, show->cast[i]);
        }
    }

    char listed_str[MAX_LINE_LEN] = "NaN";
    if (show->listedLen > 0) {
        strcpy(listed_str, show->listed_in[0]);
        for (size_t i = 1; i < show->listedLen; i++) {
            strcat(listed_str, ", ");
            strcat(listed_str, show->listed_in[i]);
        }
    }
    
    printf("%s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##",
        show->show_id, show->title, show->type, show->director, cast_str,
        show->country, date_str, show->release_year, show->rating, show->duration, listed_str);
}


// Libera toda a memória alocada para um SHOW.
void freeShow(SHOW *show_item) {
    free(show_item->show_id);
    free(show_item->type);
    free(show_item->title);
    free(show_item->director);
    free(show_item->country);
    free(show_item->rating);
    free(show_item->duration);

    if (show_item->cast) {
        for (size_t i = 0; i < show_item->castLen; i++) free(show_item->cast[i]);
        free(show_item->cast);
    }
    if (show_item->listed_in) {
        for (size_t i = 0; i < show_item->listedLen; i++) free(show_item->listed_in[i]);
        free(show_item->listed_in);
    }
}


// Analisa (parse) uma linha do CSV para preencher a struct SHOW.
void ler(SHOW *show_item, char *line) {
    char* fields[11];
    for(int i = 0; i < 11; i++) fields[i] = (char*)calloc(MAX_LINE_LEN, sizeof(char));

    int field_idx = 0, char_idx = 0;
    for (int i = 0; line[i] != '\0' && field_idx < 11; i++) {
        if (line[i] == '"') {
            i++;
            while (line[i] != '"' && line[i] != '\0') {
                fields[field_idx][char_idx++] = line[i++];
            }
        } else if (line[i] == ',') {
            if (char_idx == 0) strcpy(fields[field_idx], "NaN");
            field_idx++;
            char_idx = 0;
        } else {
            fields[field_idx][char_idx++] = line[i];
        }
    }

    show_item->show_id = safe_duplicate_string(fields[0]);
    show_item->type = safe_duplicate_string(fields[1]);
    show_item->title = safe_duplicate_string(fields[2]);
    show_item->director = safe_duplicate_string(fields[3]);
    show_item->country = safe_duplicate_string(fields[5]);

    if (strcmp(fields[6], "NaN") != 0 && strlen(fields[6]) > 0) {
        char month_str[20], day_str[4], year_str[6];
        sscanf(fields[6], "%s %[^,], %s", month_str, day_str, year_str);
        show_item->date_added.month = get_month_as_int(month_str);
        show_item->date_added.date = atoi(day_str);
        show_item->date_added.year = atoi(year_str);
    } else {
        show_item->date_added = (DATE){1, 3, 1900}; // Valor padrão como no original
    }

    show_item->release_year = atoi(fields[7]);
    show_item->rating = safe_duplicate_string(fields[8]);
    show_item->duration = safe_duplicate_string(fields[9]);

    if (strcmp(fields[4], "NaN") != 0 && strlen(fields[4]) > 0) {
        show_item->castLen = 1;
        for(int i=0; fields[4][i] != '\0'; i++) if(fields[4][i]==',') show_item->castLen++;
        show_item->cast = (char**)calloc(show_item->castLen, sizeof(char*));
        char* token = strtok(fields[4], ",");
        for(int i=0; token != NULL; i++){
            while(*token == ' ') token++;
            show_item->cast[i] = safe_duplicate_string(token);
            token = strtok(NULL, ",");
        }
        qsort(show_item->cast, show_item->castLen, sizeof(char*), compare_strings);
    } else {
        show_item->cast = NULL;
        show_item->castLen = 0;
    }
    
    if (strcmp(fields[10], "NaN") != 0 && strlen(fields[10]) > 0) {
        show_item->listedLen = 1;
        for(int i=0; fields[10][i] != '\0'; i++) if(fields[10][i]==',') show_item->listedLen++;
        show_item->listed_in = (char**)calloc(show_item->listedLen, sizeof(char*));
        char* token = strtok(fields[10], ",");
        for(int i=0; token != NULL; i++){
            while(*token == ' ') token++;
            show_item->listed_in[i] = safe_duplicate_string(token);
            token = strtok(NULL, ",");
        }
        qsort(show_item->listed_in, show_item->listedLen, sizeof(char*), compare_strings);
    } else {
        show_item->listed_in = NULL;
        show_item->listedLen = 0;
    }

    for(int i=0; i<11; i++) free(fields[i]);
}


// ----------------- IMPLEMENTAÇÃO DAS FUNÇÕES DA STRUCT PILHA -----------------

// Aloca e inicializa uma nova pilha.
PILHA* new_pilha(int capacity) {
    PILHA *p = (PILHA*)malloc(sizeof(PILHA));
    if (!p) exit(EXIT_FAILURE);
    p->array = (SHOW*)calloc(capacity, sizeof(SHOW));
    if (!p->array) exit(EXIT_FAILURE);
    p->tam = 0;
    p->capacity = capacity;
    return p;
}

// Libera a memória da pilha e de todos os seus elementos.
void free_pilha(PILHA *p) {
    if (!p) return;
    for (int i = 0; i < p->tam; i++) {
        freeShow(&p->array[i]);
    }
    free(p->array);
    free(p);
}

// Insere um elemento no topo da pilha (índice 0).
void inserir(PILHA *p, SHOW show) {
    if (p->tam >= p->capacity) {
        fprintf(stderr, "Erro: Pilha cheia.\n");
        return;
    }
    // Move todos os elementos para a direita para abrir espaço no início.
    memmove(&p->array[1], &p->array[0], p->tam * sizeof(SHOW));
    p->array[0] = clone(show);
    p->tam++;
}

// Remove e retorna o elemento do topo da pilha (índice 0).
SHOW remover(PILHA *p) {
    if (p->tam == 0) {
        fprintf(stderr, "Erro: Pilha vazia.\n");
        exit(EXIT_FAILURE);
    }
    SHOW removed_item = p->array[0];
    p->tam--;
    // Move todos os elementos para a esquerda para preencher o espaço.
    memmove(&p->array[0], &p->array[1], p->tam * sizeof(SHOW));
    return removed_item;
}

// Exibe todos os elementos restantes na pilha com sua formatação de índice específica.
void mostrarRestante(PILHA *p) {
    for (int i = 0; i < p->tam; i++) {
        printf("[%d] ", (p->tam - 1) - i); // Preserva a formatação do índice decrescente
        imprimir(&p->array[i]);
        printf("\n");
    }
}


// ----------------- FUNÇÃO PRINCIPAL -----------------
int main() {
    SHOW db_shows[MAX_SHOWS_IN_DB];
    char line_buffer[MAX_LINE_LEN];

    FILE *file = fopen(CSV_FILE_PATH, "r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return EXIT_FAILURE;
    }
    
    fgets(line_buffer, sizeof(line_buffer), file); // Pula o cabeçalho

    for (int i = 0; i < MAX_SHOWS_IN_DB; i++) {
        if (fgets(line_buffer, sizeof(line_buffer), file)) {
            line_buffer[strcspn(line_buffer, "\r\n")] = 0;
            ler(&db_shows[i], line_buffer);
        }
    }
    fclose(file);

    PILHA *pilha_shows = new_pilha(MAX_SHOWS_IN_DB);
    char input_cmd[MAX_FIELD_LEN];

    scanf("%255s", input_cmd);
    while (strcmp(input_cmd, "FIM") != 0) {
        int id = atoi(input_cmd + 1); // Pula o prefixo 's'
        if (id > 0 && id <= MAX_SHOWS_IN_DB) {
            inserir(pilha_shows, db_shows[id - 1]);
        }
        scanf("%255s", input_cmd);
    }

    int num_ops;
    scanf("%d", &num_ops);
    
    for (int i = 0; i < num_ops; i++) {
        scanf("%255s", input_cmd);
        if (strcmp(input_cmd, "I") == 0) {
            scanf("%255s", input_cmd);
            int id = atoi(input_cmd + 1);
            if (id > 0 && id <= MAX_SHOWS_IN_DB) {
                inserir(pilha_shows, db_shows[id - 1]);
            }
        } else if (strcmp(input_cmd, "R") == 0) {
            if (pilha_shows->tam > 0) {
                SHOW removed = remover(pilha_shows);
                printf("(R) %s\n", removed.title);
                freeShow(&removed); // Libera a memória do item removido
            }
        }
    }

    mostrarRestante(pilha_shows);

    // Limpeza final da memória
    free_pilha(pilha_shows);
    for(int i = 0; i < MAX_SHOWS_IN_DB; i++) {
        freeShow(&db_shows[i]);
    }
    
    return EXIT_SUCCESS;
}