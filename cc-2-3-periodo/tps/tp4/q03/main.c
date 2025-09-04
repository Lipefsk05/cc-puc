#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_STR 256
#define MAX_ARRAY 50
#define MAX_LINE 1024

typedef struct {
    char show_id[MAX_STR];
    char type[MAX_STR];
    char title[MAX_STR];
    char directors[MAX_ARRAY][MAX_STR];
    int director_count;
    char cast[MAX_ARRAY][MAX_STR];
    int cast_count;
    char country[MAX_STR];
    time_t date_added;
    int release_year;
    char rating[MAX_STR];
    char duration[MAX_STR];
    char listed_in[MAX_ARRAY][MAX_STR];
    int listed_in_count;
} Show;

typedef struct No {
    Show* show;
    struct No* esq;
    struct No* dir;
    int altura;
} No;

typedef struct {
    No* raiz;
    int comparacoes;
} Arvore;

void initShow(Show* s) {
    s->show_id[0] = '\0';
    s->type[0] = '\0';
    s->title[0] = '\0';
    s->director_count = 0;
    s->cast_count = 0;
    s->country[0] = '\0';
    s->date_added = 0;
    s->release_year = 0;
    s->rating[0] = '\0';
    s->duration[0] = '\0';
    s->listed_in_count = 0;
}

Show* cloneShow(Show* s) {
    Show* clonado = (Show*)malloc(sizeof(Show));
    initShow(clonado);
    strcpy(clonado->show_id, s->show_id);
    strcpy(clonado->type, s->type);
    strcpy(clonado->title, s->title);
    clonado->director_count = s->director_count;
    for (int i = 0; i < s->director_count; i++) {
        strcpy(clonado->directors[i], s->directors[i]);
    }
    clonado->cast_count = s->cast_count;
    for (int i = 0; i < s->cast_count; i++) {
        strcpy(clonado->cast[i], s->cast[i]);
    }
    strcpy(clonado->country, s->country);
    clonado->date_added = s->date_added;
    clonado->release_year = s->release_year;
    strcpy(clonado->rating, s->rating);
    strcpy(clonado->duration, s->duration);
    clonado->listed_in_count = s->listed_in_count;
    for (int i = 0; i < s->listed_in_count; i++) {
        strcpy(clonado->listed_in[i], s->listed_in[i]);
    }
    return clonado;
}

void ordenar(char arr[][MAX_STR], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[menor], arr[j]) > 0) {
                menor = j;
            }
        }
        if (menor != i) {
            char temp[MAX_STR];
            strcpy(temp, arr[menor]);
            strcpy(arr[menor], arr[i]);
            strcpy(arr[i], temp);
        }
    }
}

void parseArray(const char* input, char output[][MAX_STR], int* count) {
    *count = 0;
    if (strlen(input) == 0) {
        strcpy(output[0], "NaN");
        *count = 1;
        return;
    }
    char temp[MAX_LINE];
    strcpy(temp, input);
    char* token = strtok(temp, ",");
    while (token && *count < MAX_ARRAY) {
        while (*token == ' ') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && *end == ' ') end--;
        *(end + 1) = '\0';
        strcpy(output[*count], token);
        (*count)++;
        token = strtok(NULL, ",");
    }
    ordenar(output, *count);
}

void parseDate(const char* date_str, time_t* output) {
    if (strlen(date_str) == 0) {
        *output = 0;
        return;
    }
    struct tm tm = {0};
    char month[20];
    int day, year;
    if (sscanf(date_str, "%s %d, %d", month, &day, &year) == 3) {
        const char* months[] = {"January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};
        for (int i = 0; i < 12; i++) {
            if (strcmp(month, months[i]) == 0) {
                tm.tm_mon = i;
                break;
            }
        }
        tm.tm_mday = day;
        tm.tm_year = year - 1900;
        tm.tm_isdst = -1;
        *output = mktime(&tm);
    } else {
        *output = 0;
    }
}

void leitura(Show* s, const char* linha) {
    char partes[11][MAX_LINE];
    int parte_idx = 0;
    int dentro_aspas = 0;
    char atual[MAX_LINE] = {0};
    int atual_idx = 0;

    for (int i = 0; linha[i] && parte_idx < 11; i++) {
        if (linha[i] == '"') {
            dentro_aspas = !dentro_aspas;
        } else if (linha[i] == ',' && !dentro_aspas) {
            atual[atual_idx] = '\0';
            char* trimmed = atual;
            while (*trimmed == ' ') trimmed++;
            char* end = trimmed + strlen(trimmed) - 1;
            while (end > trimmed && *end == ' ') end--;
            *(end + 1) = '\0';
            strcpy(partes[parte_idx++], trimmed);
            atual_idx = 0;
        } else {
            atual[atual_idx++] = linha[i];
        }
    }
    atual[atual_idx] = '\0';
    char* trimmed = atual;
    while (*trimmed == ' ') trimmed++;
    char* end = trimmed + strlen(trimmed) - 1;
    while (end > trimmed && *end == ' ') end--;
    *(end + 1) = '\0';
    strcpy(partes[parte_idx++], trimmed);

    strcpy(s->show_id, partes[0]);
    strcpy(s->type, partes[1][0] ? partes[1] : "NaN");
    strcpy(s->title, partes[2][0] ? partes[2] : "NaN");
    parseArray(partes[3], s->directors, &s->director_count);
    parseArray(partes[4], s->cast, &s->cast_count);
    strcpy(s->country, partes[5][0] ? partes[5] : "NaN");
    parseDate(partes[6], &s->date_added);
    s->release_year = atoi(partes[7]);
    strcpy(s->rating, partes[8][0] ? partes[8] : "NaN");
    strcpy(s->duration, partes[9][0] ? partes[9] : "NaN");
    parseArray(partes[10], s->listed_in, &s->listed_in_count);
}

void imprimir(Show* s) {
    printf("=> %s ## %s ## %s ## ", s->show_id, s->title, s->type);
    for (int i = 0; i < s->director_count; i++) {
        printf("%s", s->directors[i]);
        if (i < s->director_count - 1) printf(", ");
    }
    printf(" ## [");
    for (int i = 0; i < s->cast_count; i++) {
        printf("%s", s->cast[i]);
        if (i < s->cast_count - 1) printf(", ");
    }
    printf("] ## %s ## ", s->country);
    if (s->date_added != 0) {
        char date_str[50];
        strftime(date_str, sizeof(date_str), "%B %d, %Y", localtime(&s->date_added));
        printf("%s ## ", date_str);
    } else {
        printf("NaN ## ");
    }
    printf("%d ## %s ## %s ## [", s->release_year, s->rating, s->duration);
    for (int i = 0; i < s->listed_in_count; i++) {
        printf("%s", s->listed_in[i]);
        if (i < s->listed_in_count - 1) printf(", ");
    }
    printf("] ##\n");
}

Arvore* initArvore() {
    Arvore* arv = (Arvore*)malloc(sizeof(Arvore));
    arv->raiz = NULL;
    arv->comparacoes = 0;
    return arv;
}

int altura(No* no) {
    return no ? no->altura : 0;
}

int fatorBalanceamento(No* no) {
    return no ? altura(no->esq) - altura(no->dir) : 0;
}

No* rotacaoDireita(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir)) + 1;
    x->altura = (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir)) + 1;
    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir)) + 1;
    y->altura = (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir)) + 1;
    return y;
}

No* inserirNo(No* no, Show* s, Arvore* arv) {
    if (!no) {
        No* novo = (No*)malloc(sizeof(No));
        novo->show = cloneShow(s);
        novo->esq = novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    int cmp = strcmp(s->title, no->show->title);
    if (cmp < 0) {
        no->esq = inserirNo(no->esq, s, arv);
    } else if (cmp > 0) {
        no->dir = inserirNo(no->dir, s, arv);
    } else {
        return no;
    }

    no->altura = (altura(no->esq) > altura(no->dir) ? altura(no->esq) : altura(no->dir)) + 1;
    int balance = fatorBalanceamento(no);

    if (balance > 1 && strcmp(s->title, no->esq->show->title) < 0) {
        return rotacaoDireita(no);
    }
    if (balance < -1 && strcmp(s->title, no->dir->show->title) > 0) {
        return rotacaoEsquerda(no);
    }
    if (balance > 1 && strcmp(s->title, no->esq->show->title) > 0) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }
    if (balance < -1 && strcmp(s->title, no->dir->show->title) < 0) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

void inserir(Arvore* arv, Show* s) {
    arv->raiz = inserirNo(arv->raiz, s, arv);
}

int pesquisarNo(No* no, const char* s, Arvore* arv) {
    if (!no) {
        arv->comparacoes++;
        return 0;
    }
    int cmp = strcmp(s, no->show->title);
    if (cmp == 0) {
        arv->comparacoes++;
        return 1;
    }
    printf(cmp < 0 ? " esq" : " dir");
    arv->comparacoes++;
    return pesquisarNo(cmp < 0 ? no->esq : no->dir, s, arv);
}

int pesquisar(Arvore* arv, const char* s) {
    printf("raiz");
    return pesquisarNo(arv->raiz, s, arv);
}

void freeNo(No* no) {
    if (no) {
        freeNo(no->esq);
        freeNo(no->dir);
        free(no->show);
        free(no);
    }
}

void freeArvore(Arvore* arv) {
    freeNo(arv->raiz);
    free(arv);
}

int main() {
    Arvore* arv = initArvore();
    clock_t inicio = clock();
    char entrada[MAX_STR];
    FILE* fp;

    while (fgets(entrada, MAX_STR, stdin) && strcmp(entrada, "FIM\n") != 0) {
        entrada[strcspn(entrada, "\n")] = '\0';
        fp = fopen("/tmp/disneyplus.csv", "r");
        if (!fp) {
            printf("Erro ao acessar o arquivo\n");
            continue;
        }
        char linha[MAX_LINE];
        fgets(linha, MAX_LINE, fp);
        int encontrado = 0;

        while (fgets(linha, MAX_LINE, fp) && !encontrado) {
            char id_prefix[MAX_STR];
            snprintf(id_prefix, sizeof(id_prefix), "%s,", entrada);
            if (strncmp(linha, id_prefix, strlen(id_prefix)) == 0) {
                Show tmp;
                initShow(&tmp);
                leitura(&tmp, linha);
                inserir(arv, &tmp);
                encontrado = 1;
            }
        }
        if (!encontrado) {
            printf("Show ID %s não encontrado.\n", entrada);
        }
        fclose(fp);
    }

    while (fgets(entrada, MAX_STR, stdin) && strcmp(entrada, "FIM\n") != 0) {
        entrada[strcspn(entrada, "\n")] = '\0';
        if (pesquisar(arv, entrada)) {
            printf(" SIM\n");
        } else {
            printf(" NAO\n");
        }
    }

    clock_t fim = clock();
    double tempo_exec = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;

    FILE* log = fopen("matricula_avl.txt", "w");
    if (log) {
        fprintf(log, "858158\t%.0f\t%d\n", tempo_exec, arv->comparacoes);
        fclose(log);
    } else {
        printf("Erro ao criar arquivo de log\n");
    }

    freeArvore(arv);
    return 0;
}
