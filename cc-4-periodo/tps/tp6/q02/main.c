#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE 10000
#define MAX_FIELDS 20
#define MAX_ARRAY 100
#define MAX_STR 512

typedef struct
{
    int id;
    char name[MAX_STR];
    char releaseDate[MAX_STR];
    int estimateOwners;
    double price;
    char **supportedLanguages;
    int supportedLanguagesCount;
    int metacriticScore;
    double userScore;
    int achieviments;
    char **publishers;
    int publishersCount;
    char **developers;
    int developersCount;
    char **categories;
    int categoriesCount;
    char **genres;
    int genresCount;
    char **tags;
    int tagsCount;
} Game;

// ---------- Estrutura da Lista Encadeada ----------

typedef struct Celula {
    Game *game;
    struct Celula *prox;
} Celula;

typedef struct {
    Celula *primeiro;
    Celula *ultimo;
    int n;
} Lista;

// ---------- Protótipos das Funções da Lista ----------

void startLista(Lista *lista);
void inserirInicio(Lista *lista, Game *game);
void inserir(Lista *lista, Game *game, int pos);
void inserirFim(Lista *lista, Game *game);
Game* removerInicio(Lista *lista);
Game* remover(Lista *lista, int pos);
Game* removerFim(Lista *lista);
void mostrar(Lista *lista);
void freeLista(Lista *lista);

// ---------- Funções auxiliares ----------

char *trim(char *str)
{
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return str;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';
    return str;
}

void remove_quotes(char *s)
{
    char *start = s;
    while (*start == '\'' || *start == '"')
        start++;
    char *end = s + strlen(s) - 1;
    while (end >= start && (*end == '\'' || *end == '"'))
        *end-- = '\0';
    if (start != s)
        memmove(s, start, strlen(start) + 1);
}

char **parseArray(const char *s, int *count)
{
    *count = 0;
    char *copy = strdup(s);
    char *str = trim(copy);
    if (str[0] == '[')
        str++;
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == ']')
        str[len - 1] = '\0';
    if (strlen(str) == 0)
    {
        free(copy);
        return NULL;
    }
    char **arr = malloc(MAX_ARRAY * sizeof(char *));
    char *token = strtok(str, ",");
    while (token && *count < MAX_ARRAY)
    {
        token = trim(token);
        remove_quotes(token);
        arr[*count] = strdup(token);
        (*count)++;
        token = strtok(NULL, ",");
    }
    free(copy);
    return arr;
}

int parseCSVLine(const char *line, char fields[MAX_FIELDS][MAX_LINE])
{
    int count = 0;
    int inQuotes = 0;
    char buffer[MAX_LINE];
    int j = 0;

    for (int i = 0; line[i] != '\0'; i++)
    {
        char c = line[i];
        if (c == '"')
        {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes)
        {
            buffer[j] = '\0';
            strcpy(fields[count++], trim(buffer));
            j = 0;
        }
        else
        {
            buffer[j++] = c;
        }
    }
    buffer[j] = '\0';
    strcpy(fields[count++], trim(buffer));
    return count;
}

void printArray(char **arr, int count)
{
    printf("[");
    for (int i = 0; i < count; i++)
    {
        printf("%s", arr[i]);
        if (i < count - 1)
            printf(", ");
    }
    printf("]");
}

int monthStrToNum(const char *m)
{
    if (strcasecmp(m, "Jan") == 0)
        return 1;
    if (strcasecmp(m, "Feb") == 0)
        return 2;
    if (strcasecmp(m, "Mar") == 0)
        return 3;
    if (strcasecmp(m, "Apr") == 0)
        return 4;
    if (strcasecmp(m, "May") == 0)
        return 5;
    if (strcasecmp(m, "Jun") == 0)
        return 6;
    if (strcasecmp(m, "Jul") == 0)
        return 7;
    if (strcasecmp(m, "Aug") == 0)
        return 8;
    if (strcasecmp(m, "Sep") == 0)
        return 9;
    if (strcasecmp(m, "Oct") == 0)
        return 10;
    if (strcasecmp(m, "Nov") == 0)
        return 11;
    if (strcasecmp(m, "Dec") == 0)
        return 12;
    return 0;
}

void formatDate(const char *in, char *out, size_t outSize)
{
    if (!in || !out || outSize == 0)
        return;
    char mon[16];
    int day = 0;
    int year = 0;
    out[0] = '\0';

    int matched = sscanf(in, " %3s %d , %d", mon, &day, &year);
    if (matched < 3)
    {
        matched = sscanf(in, " %3s %d, %d", mon, &day, &year);
    }
    if (matched < 3)
    {
        matched = sscanf(in, " %d/%d/%d", &day, &year, &year);
        strncpy(out, in, outSize - 1);
        out[outSize - 1] = '\0';
        return;
    }

    int m = monthStrToNum(mon);
    if (m == 0 || day <= 0 || year <= 0)
    {
        strncpy(out, in, outSize - 1);
        out[outSize - 1] = '\0';
        return;
    }

    snprintf(out, outSize, "%02d/%02d/%04d", day, m, year);
}

void printGame(Game *g)
{
    char priceStr[20];
    if (g->price == 0.0)
        strcpy(priceStr, "0.0");
    else
        sprintf(priceStr, "%.2f", g->price);

    char dateBuf[32];
    formatDate(g->releaseDate, dateBuf, sizeof(dateBuf));

    printf("=> %d ## %s ## %s ## %d ## %s ## ",
           g->id, g->name, dateBuf, g->estimateOwners, priceStr);

    printArray(g->supportedLanguages, g->supportedLanguagesCount);
    printf(" ## %d ## %.1f ## %d ## ", g->metacriticScore, g->userScore, g->achieviments);

    printArray(g->publishers, g->publishersCount);
    printf(" ## ");
    printArray(g->developers, g->developersCount);
    printf(" ## ");
    printArray(g->categories, g->categoriesCount);
    printf(" ## ");
    printArray(g->genres, g->genresCount);
    printf(" ## ");
    printArray(g->tags, g->tagsCount);
    printf(" ##\n");
}

// Function to free memory allocated for a Game's dynamic arrays
void freeGameArrays(Game *g)
{
    for (int i = 0; i < g->supportedLanguagesCount; i++)
        free(g->supportedLanguages[i]);
    free(g->supportedLanguages);
    
    for (int i = 0; i < g->publishersCount; i++)
        free(g->publishers[i]);
    free(g->publishers);
    
    for (int i = 0; i < g->developersCount; i++)
        free(g->developers[i]);
    free(g->developers);
    
    for (int i = 0; i < g->categoriesCount; i++)
        free(g->categories[i]);
    free(g->categories);
    
    for (int i = 0; i < g->genresCount; i++)
        free(g->genres[i]);
    free(g->genres);
    
    for (int i = 0; i < g->tagsCount; i++)
        free(g->tags[i]);
    free(g->tags);
}

// Function to copy a Game (deep copy for dynamic arrays)
void copyGame(Game *dest, Game *src)
{
    *dest = *src; // Copy all static fields
    
    // Deep copy arrays
    dest->supportedLanguages = malloc(src->supportedLanguagesCount * sizeof(char *));
    for (int i = 0; i < src->supportedLanguagesCount; i++)
        dest->supportedLanguages[i] = strdup(src->supportedLanguages[i]);
    dest->supportedLanguagesCount = src->supportedLanguagesCount;
    
    dest->publishers = malloc(src->publishersCount * sizeof(char *));
    for (int i = 0; i < src->publishersCount; i++)
        dest->publishers[i] = strdup(src->publishers[i]);
    dest->publishersCount = src->publishersCount;
    
    dest->developers = malloc(src->developersCount * sizeof(char *));
    for (int i = 0; i < src->developersCount; i++)
        dest->developers[i] = strdup(src->developers[i]);
    dest->developersCount = src->developersCount;
    
    dest->categories = malloc(src->categoriesCount * sizeof(char *));
    for (int i = 0; i < src->categoriesCount; i++)
        dest->categories[i] = strdup(src->categories[i]);
    dest->categoriesCount = src->categoriesCount;
    
    dest->genres = malloc(src->genresCount * sizeof(char *));
    for (int i = 0; i < src->genresCount; i++)
        dest->genres[i] = strdup(src->genres[i]);
    dest->genresCount = src->genresCount;
    
    dest->tags = malloc(src->tagsCount * sizeof(char *));
    for (int i = 0; i < src->tagsCount; i++)
        dest->tags[i] = strdup(src->tags[i]);
    dest->tagsCount = src->tagsCount;
}

int loadGames(Game **gamesOut)
{
    FILE *fp = fopen("/tmp/games.csv", "r");
    if (!fp)
    {
        perror("Erro abrindo /tmp/games.csv");
        exit(1);
    }
    char line[MAX_LINE];
    fgets(line, sizeof(line), fp);
    Game *games = malloc(5000 * sizeof(Game));
    int gameCount = 0;

    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0)
            continue;

        char fields[MAX_FIELDS][MAX_LINE];
        int fieldCount = parseCSVLine(line, fields);
        if (fieldCount < 14)
            continue;

        Game g;
        g.id = atoi(fields[0]);
        strcpy(g.name, fields[1]);
        remove_quotes(g.name);
        trim(g.name);
        strcpy(g.releaseDate, fields[2]);

        g.estimateOwners = atoi(fields[3]);
        g.price = atof(fields[4]);
        g.supportedLanguages = parseArray(fields[5], &g.supportedLanguagesCount);
        g.metacriticScore = atoi(fields[6]);
        g.userScore = atof(fields[7]);
        g.achieviments = atoi(fields[8]);
        g.publishers = parseArray(fields[9], &g.publishersCount);
        g.developers = parseArray(fields[10], &g.developersCount);
        g.categories = parseArray(fields[11], &g.categoriesCount);
        g.genres = parseArray(fields[12], &g.genresCount);
        g.tags = parseArray(fields[13], &g.tagsCount);

        games[gameCount++] = g;
    }

    fclose(fp);
    *gamesOut = games;
    return gameCount;
}

// ---------- Implementação da Lista Encadeada ----------

void startLista(Lista *lista) {
    lista->primeiro = (Celula*)malloc(sizeof(Celula));
    lista->primeiro->prox = NULL;
    lista->ultimo = lista->primeiro;
    lista->n = 0;
}

void inserirInicio(Lista *lista, Game *game) {
    Celula *tmp = (Celula*)malloc(sizeof(Celula));
    tmp->game = game;
    tmp->prox = lista->primeiro->prox;
    lista->primeiro->prox = tmp;
    if (lista->primeiro == lista->ultimo) {
        lista->ultimo = tmp;
    }
    lista->n++;
}

void inserir(Lista *lista, Game *game, int pos) {
    if (pos < 0 || pos > lista->n) {
        printf("Erro ao inserir: posicao invalida!\n");
        return;
    } else if (pos == 0) {
        inserirInicio(lista, game);
    } else if (pos == lista->n) {
        inserirFim(lista, game);
    } else {
        Celula *i = lista->primeiro;
        for (int j = 0; j < pos; j++, i = i->prox);
        Celula *tmp = (Celula*)malloc(sizeof(Celula));
        tmp->game = game;
        tmp->prox = i->prox;
        i->prox = tmp;
        lista->n++;
    }
}

void inserirFim(Lista *lista, Game *game) {
    lista->ultimo->prox = (Celula*)malloc(sizeof(Celula));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->game = game;
    lista->ultimo->prox = NULL;
    lista->n++;
}

Game* removerInicio(Lista *lista) {
    if (lista->primeiro == lista->ultimo) {
        printf("Erro ao remover: lista vazia!\n");
        return NULL;
    }
    Celula *tmp = lista->primeiro->prox;
    Game *resp = tmp->game;
    lista->primeiro->prox = tmp->prox;
    if (tmp == lista->ultimo) {
        lista->ultimo = lista->primeiro;
    }
    free(tmp);
    lista->n--;
    return resp;
}

Game* remover(Lista *lista, int pos) {
    Game *resp = NULL;
    if (lista->primeiro == lista->ultimo) {
        printf("Erro ao remover: lista vazia!\n");
    } else if (pos < 0 || pos >= lista->n) {
        printf("Erro ao remover: posicao invalida!\n");
    } else if (pos == 0) {
        resp = removerInicio(lista);
    } else if (pos == lista->n - 1) {
        resp = removerFim(lista);
    } else {
        Celula *i = lista->primeiro;
        for (int j = 0; j < pos; j++, i = i->prox);
        Celula *tmp = i->prox;
        i->prox = tmp->prox;
        resp = tmp->game;
        free(tmp);
        lista->n--;
    }
    return resp;
}

Game* removerFim(Lista *lista) {
    if (lista->primeiro == lista->ultimo) {
        printf("Erro ao remover: lista vazia!\n");
        return NULL;
    }
    Celula *i;
    for (i = lista->primeiro; i->prox != lista->ultimo; i = i->prox);
    Game *resp = lista->ultimo->game;
    lista->ultimo = i;
    free(i->prox);
    i->prox = NULL;
    lista->n--;
    return resp;
}

void mostrar(Lista *lista) {
    int j = 0;
    for (Celula *i = lista->primeiro->prox; i != NULL; i = i->prox, j++) {
        printf("[%d] ", j);
        printGame(i->game);
    }
}

void freeLista(Lista *lista) {
    Celula *atual = lista->primeiro->prox;
    while (atual != NULL) {
        Celula *tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    free(lista->primeiro);
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->n = 0;
}

// ---------- Função para encontrar jogo por ID ----------

Game* findGameById(Game *games, int gameCount, int id) {
    for (int i = 0; i < gameCount; i++) {
        if (games[i].id == id) {
            return &games[i];
        }
    }
    return NULL;
}

// ---------- MAIN ----------

int main()
{
    Game *games;
    int gameCount = loadGames(&games);

    Lista lista;
    startLista(&lista);

    char input[50];

    // Primeira parte: ler IDs até FIM
    while (1)
    {
        if (!fgets(input, sizeof(input), stdin))
            break;
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "FIM") == 0)
            break;
        int id = atoi(input);
        Game *game = findGameById(games, gameCount, id);
        if (game != NULL) {
            inserirFim(&lista, game);
        }
    }

    // Segunda parte: ler operações
    int n;
    scanf("%d", &n);
    getchar(); // Consumir newline

    for (int i = 0; i < n; i++) {
        if (!fgets(input, sizeof(input), stdin))
            break;
        input[strcspn(input, "\n")] = '\0';
        
        char *token = strtok(input, " ");
        char comando[3];
        strcpy(comando, token);

        if (strcmp(comando, "II") == 0) {
            token = strtok(NULL, " ");
            int id = atoi(token);
            Game *game = findGameById(games, gameCount, id);
            if (game != NULL) {
                inserirInicio(&lista, game);
            }
        }
        else if (strcmp(comando, "I*") == 0) {
            token = strtok(NULL, " ");
            int pos = atoi(token);
            token = strtok(NULL, " ");
            int id = atoi(token);
            Game *game = findGameById(games, gameCount, id);
            if (game != NULL) {
                inserir(&lista, game, pos);
            }
        }
        else if (strcmp(comando, "IF") == 0) {
            token = strtok(NULL, " ");
            int id = atoi(token);
            Game *game = findGameById(games, gameCount, id);
            if (game != NULL) {
                inserirFim(&lista, game);
            }
        }
        else if (strcmp(comando, "RI") == 0) {
            Game *removido = removerInicio(&lista);
            if (removido != NULL) {
                printf("(R) %s\n", removido->name);
            }
        }
        else if (strcmp(comando, "R*") == 0) {
            token = strtok(NULL, " ");
            int pos = atoi(token);
            Game *removido = remover(&lista, pos);
            if (removido != NULL) {
                printf("(R) %s\n", removido->name);
            }
        }
        else if (strcmp(comando, "RF") == 0) {
            Game *removido = removerFim(&lista);
            if (removido != NULL) {
                printf("(R) %s\n", removido->name);
            }
        }
    }

    // Mostrar lista final
    mostrar(&lista);

    // Free memory
    freeLista(&lista);
    
    for (int i = 0; i < gameCount; i++)
    {
        freeGameArrays(&games[i]);
    }
    free(games);
    
    return 0;
}