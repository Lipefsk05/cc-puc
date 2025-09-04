#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ----------------- CONSTANTES GLOBAIS -----------------
#define DATABASE_SIZE 1368
#define QUEUE_CAPACITY 5 // Tamanho fixo da fila circular
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

// Estrutura para a Fila Circular
typedef struct {
    SHOW *array;
    int front;    // Índice do início da fila
    int rear;     // Índice de onde o próximo item será inserido
    int count;    // Número atual de elementos na fila
} FILA_C;

// ----------------- PROTÓTIPOS DAS FUNÇÕES -----------------
// Funções Auxiliares
char* safe_strdup(const char* str);
int month_name_to_int(const char* month_name);
int compare_str_ptr(const void* a, const void* b);

// Funções da struct SHOW
void ler(SHOW *show_item, char *line);
void imprimir(SHOW *show_item);
SHOW clone(SHOW original_show);
void freeShow(SHOW *show_item);

// Funções da struct FILA_C
FILA_C* new_fila();
void free_fila(FILA_C *q);
void inserir(FILA_C *q, SHOW show);
SHOW remover(FILA_C *q);
int getMedia(FILA_C *q);
bool estaCheia(FILA_C *q);
bool estaVazia(FILA_C *q);
void mostrarRestante(FILA_C *q);


// ----------------- IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES -----------------

char* safe_strdup(const char* str) {
    if (!str) return NULL;
    char* new_str = (char*)malloc(strlen(str) + 1);
    if (!new_str) {
        perror("Falha ao alocar memoria para string");
        exit(EXIT_FAILURE);
    }
    strcpy(new_str, str);
    return new_str;
}

int month_name_to_int(const char* month_name) {
    const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++) {
        if (strcmp(month_name, months[i]) == 0) return i + 1;
    }
    return 0;
}

int compare_str_ptr(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}


// ----------------- IMPLEMENTAÇÃO DAS FUNÇÕES DA STRUCT SHOW -----------------

SHOW clone(SHOW show) {
    SHOW new_show;
    new_show.show_id = safe_strdup(show.show_id);
    new_show.type = safe_strdup(show.type);
    new_show.title = safe_strdup(show.title);
    new_show.director = safe_strdup(show.director);
    new_show.country = safe_strdup(show.country);
    new_show.rating = safe_strdup(show.rating);
    new_show.duration = safe_strdup(show.duration);
    
    new_show.date_added = show.date_added;
    new_show.release_year = show.release_year;
    
    new_show.castLen = show.castLen;
    if (new_show.castLen > 0) {
        new_show.cast = (char**)calloc(new_show.castLen, sizeof(char*));
        for (size_t i = 0; i < new_show.castLen; i++) new_show.cast[i] = safe_strdup(show.cast[i]);
    } else {
        new_show.cast = NULL;
    }

    new_show.listedLen = show.listedLen;
    if (new_show.listedLen > 0) {
        new_show.listed_in = (char**)calloc(new_show.listedLen, sizeof(char*));
        for (size_t i = 0; i < new_show.listedLen; i++) new_show.listed_in[i] = safe_strdup(show.listed_in[i]);
    } else {
        new_show.listed_in = NULL;
    }
    return new_show;
}

void imprimir(SHOW *show) {
    char date_str[MAX_FIELD_LEN];
    if (show->date_added.year != 0 && show->date_added.year != 1900) {
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
    
    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
        show->show_id, show->title, show->type, show->director, cast_str,
        show->country, date_str, show->release_year, show->rating, show->duration, listed_str);
}

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

void ler(SHOW *show_item, char *line) {
    // A lógica de parsing manual é preservada para manter a funcionalidade original
    char* fields[11];
    for(int i = 0; i < 11; i++) fields[i] = (char*)calloc(MAX_LINE_LEN, sizeof(char));

    int field_idx = 0, char_idx = 0;
    for (int i = 0; line[i] != '\0' && field_idx < 11; i++) {
        if (line[i] == '"') {
            i++;
            while (line[i] != '"' && line[i] != '\0') fields[field_idx][char_idx++] = line[i++];
        } else if (line[i] == ',') {
            if (char_idx == 0) strcpy(fields[field_idx], "NaN");
            field_idx++;
            char_idx = 0;
        } else {
            fields[field_idx][char_idx++] = line[i];
        }
    }

    show_item->show_id = safe_strdup(fields[0]);
    show_item->type = safe_strdup(fields[1]);
    show_item->title = safe_strdup(fields[2]);
    show_item->director = safe_strdup(fields[3]);
    show_item->country = safe_strdup(fields[5]);

    if (strcmp(fields[6], "NaN") != 0 && strlen(fields[6]) > 0) {
        char month_str[20], day_str[4], year_str[6];
        sscanf(fields[6], "%s %[^,], %s", month_str, day_str, year_str);
        show_item->date_added.month = month_name_to_int(month_str);
        show_item->date_added.date = atoi(day_str);
        show_item->date_added.year = atoi(year_str);
    } else {
        show_item->date_added = (DATE){1, 3, 1900};
    }

    show_item->release_year = atoi(fields[7]);
    show_item->rating = safe_strdup(fields[8]);
    show_item->duration = safe_strdup(fields[9]);

    if (strcmp(fields[4], "NaN") != 0 && strlen(fields[4]) > 0) {
        show_item->castLen = 1;
        for(int i=0; fields[4][i] != '\0'; i++) if(fields[4][i]==',') show_item->castLen++;
        show_item->cast = (char**)calloc(show_item->castLen, sizeof(char*));
        char* token = strtok(fields[4], ",");
        for(int i=0; token != NULL; i++){
            while(*token == ' ') token++;
            show_item->cast[i] = safe_strdup(token);
            token = strtok(NULL, ",");
        }
        qsort(show_item->cast, show_item->castLen, sizeof(char*), compare_str_ptr);
    } else {
        show_item->cast = NULL; show_item->castLen = 0;
    }
    
    if (strcmp(fields[10], "NaN") != 0 && strlen(fields[10]) > 0) {
        show_item->listedLen = 1;
        for(int i=0; fields[10][i] != '\0'; i++) if(fields[10][i]==',') show_item->listedLen++;
        show_item->listed_in = (char**)calloc(show_item->listedLen, sizeof(char*));
        char* token = strtok(fields[10], ",");
        for(int i=0; token != NULL; i++){
            while(*token == ' ') token++;
            show_item->listed_in[i] = safe_strdup(token);
            token = strtok(NULL, ",");
        }
        qsort(show_item->listed_in, show_item->listedLen, sizeof(char*), compare_str_ptr);
    } else {
        show_item->listed_in = NULL; show_item->listedLen = 0;
    }
    for(int i=0; i<11; i++) free(fields[i]);
}


// ----------------- IMPLEMENTAÇÃO DAS FUNÇÕES DA STRUCT FILA_C -----------------

FILA_C* new_fila() {
    FILA_C *q = (FILA_C*)malloc(sizeof(FILA_C));
    if (!q) exit(EXIT_FAILURE);
    q->array = (SHOW*)calloc(QUEUE_CAPACITY, sizeof(SHOW));
    if (!q->array) exit(EXIT_FAILURE);
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    return q;
}

void free_fila(FILA_C *q) {
    if (!q) return;
    // Libera cada SHOW clonado que ainda está na fila
    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % QUEUE_CAPACITY;
        freeShow(&q->array[index]);
    }
    free(q->array);
    free(q);
}

bool estaCheia(FILA_C *q) { return q->count == QUEUE_CAPACITY; }
bool estaVazia(FILA_C *q) { return q->count == 0; }

int getMedia(FILA_C *q) {
    if (estaVazia(q)) return 0;
    long long total_year = 0; // Use long long para evitar overflow
    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % QUEUE_CAPACITY;
        total_year += q->array[index].release_year;
    }
    // Arredondamento para o inteiro mais próximo
    return (int)((double)total_year / q->count + 0.5);
}

// Remove o elemento mais antigo da fila.
SHOW remover(FILA_C *q) {
    if (estaVazia(q)) {
        fprintf(stderr, "Erro: Fila esta vazia!\n");
        exit(EXIT_FAILURE);
    }
    SHOW removed_item = q->array[q->front];
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    q->count--;
    return removed_item;
}

// Insere um novo elemento na fila. Se a fila estiver cheia, o mais antigo é removido.
void inserir(FILA_C *q, SHOW show) {
    if (estaCheia(q)) {
        SHOW discarded_item = remover(q);
        // Libera a memória do item descartado para evitar vazamentos
        freeShow(&discarded_item);
    }
    q->array[q->rear] = clone(show);
    q->rear = (q->rear + 1) % QUEUE_CAPACITY;
    q->count++;
    printf("[Media] %d\n", getMedia(q));
}

void mostrarRestante(FILA_C *q) {
    for (int i = 0; i < q->count; i++) {
        int array_index = (q->front + i) % QUEUE_CAPACITY;
        // A lógica de impressão do índice é mantida para corresponder à saída original
        printf("[%d] ", i);
        imprimir(&q->array[array_index]);
    }
}


// ----------------- FUNÇÃO PRINCIPAL -----------------

int main() {
    SHOW db_shows[DATABASE_SIZE];
    char line_buffer[MAX_LINE_LEN];

    FILE *file = fopen(CSV_FILE_PATH, "r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return EXIT_FAILURE;
    }
    fgets(line_buffer, sizeof(line_buffer), file); // Pula cabeçalho

    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (fgets(line_buffer, sizeof(line_buffer), file)) {
            line_buffer[strcspn(line_buffer, "\r\n")] = 0;
            ler(&db_shows[i], line_buffer);
        }
    }
    fclose(file);

    FILA_C *fila_shows = new_fila();
    char input_buffer[MAX_FIELD_LEN];

    scanf("%255s", input_buffer);
    while (strcmp(input_buffer, "FIM") != 0) {
        int id = atoi(input_buffer + 1);
        if (id > 0 && id <= DATABASE_SIZE) {
            inserir(fila_shows, db_shows[id - 1]);
        }
        scanf("%255s", input_buffer);
    }

    int num_ops;
    scanf("%d", &num_ops);
    for (int i = 0; i < num_ops; i++) {
        scanf("%255s", input_buffer);
        if (strcmp(input_buffer, "I") == 0) {
            scanf("%255s", input_buffer);
            int id = atoi(input_buffer + 1);
            if (id > 0 && id <= DATABASE_SIZE) {
                inserir(fila_shows, db_shows[id - 1]);
            }
        } else if (strcmp(input_buffer, "R") == 0) {
            if (!estaVazia(fila_shows)) {
                SHOW removed = remover(fila_shows);
                printf("(R) %s\n", removed.title);
                freeShow(&removed);
            }
        }
    }

    // A função mostrarRestante original não imprimia uma nova linha, então não adicionamos aqui.
    // mostrarRestante(fila_shows);

    // Limpeza final da memória
    free_fila(fila_shows);
    for(int i = 0; i < DATABASE_SIZE; i++) {
        freeShow(&db_shows[i]);
    }
    
    return EXIT_SUCCESS;
}