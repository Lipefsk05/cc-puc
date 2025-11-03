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

// ---------- Estrutura da Pilha ----------

typedef struct Celula {
    Game *game;
    struct Celula *prox;
} Celula;

typedef struct {
    Celula *topo;
    int n;
} Pilha;

// ---------- Protótipos das Funções da Pilha ----------

void startPilha(Pilha *pilha);
void empilhar(Pilha *pilha, Game *game);
Game* desempilhar(Pilha *pilha);
void mostrarPilha(Pilha *pilha);
void freePilha(Pilha *pilha);

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
    if (g->supportedLanguages) {
        for (int i = 0; i < g->supportedLanguagesCount; i++)
            free(g->supportedLanguages[i]);
        free(g->supportedLanguages);
    }
    
    if (g->publishers) {
        for (int i = 0; i < g->publishersCount; i++)
            free(g->publishers[i]);
        free(g->publishers);
    }
    
    if (g->developers) {
        for (int i = 0; i < g->developersCount; i++)
            free(g->developers[i]);
        free(g->developers);
    }
    
    if (g->categories) {
        for (int i = 0; i < g->categoriesCount; i++)
            free(g->categories[i]);
        free(g->categories);
    }
    
    if (g->genres) {
        for (int i = 0; i < g->genresCount; i++)
            free(g->genres[i]);
        free(g->genres);
    }
    
    if (g->tags) {
        for (int i = 0; i < g->tagsCount; i++)
            free(g->tags[i]);
        free(g->tags);
    }
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

// ---------- Implementação da Pilha ----------

void startPilha(Pilha *pilha) {
    pilha->topo = NULL;
    pilha->n = 0;
}

void empilhar(Pilha *pilha, Game *game) {
    Celula *nova = (Celula*)malloc(sizeof(Celula));
    nova->game = game;
    nova->prox = pilha->topo;
    pilha->topo = nova;
    pilha->n++;
}

Game* desempilhar(Pilha *pilha) {
    if (pilha->topo == NULL) {
        return NULL;
    }
    Celula *temp = pilha->topo;
    Game *game = temp->game;
    pilha->topo = temp->prox;
    free(temp);
    pilha->n--;
    return game;
}

void mostrarPilha(Pilha *pilha) {
    // Para mostrar na ordem correta (do topo para a base), precisamos inverter temporariamente
    Pilha temp;
    startPilha(&temp);
    
    // Transferir da pilha principal para a temporária
    Celula *atual = pilha->topo;
    while (atual != NULL) {
        empilhar(&temp, atual->game);
        atual = atual->prox;
    }
    
    // Agora mostrar da temporária (que está na ordem correta)
    int pos = 0;
    atual = temp.topo;
    while (atual != NULL) {
        printf("[%d] ", pos++);
        printGame(atual->game);
        atual = atual->prox;
    }
    
    // Liberar a pilha temporária (apenas as células, não os games)
    while (temp.topo != NULL) {
        Celula *tmp = temp.topo;
        temp.topo = temp.topo->prox;
        free(tmp);
    }
}

void freePilha(Pilha *pilha) {
    while (pilha->topo != NULL) {
        Celula *temp = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(temp);
    }
    pilha->n = 0;
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

    Pilha pilha;
    startPilha(&pilha);

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
            empilhar(&pilha, game);
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

        if (strcmp(comando, "I") == 0) {
            token = strtok(NULL, " ");
            int id = atoi(token);
            Game *game = findGameById(games, gameCount, id);
            if (game != NULL) {
                empilhar(&pilha, game);
            }
        }
        else if (strcmp(comando, "R") == 0) {
            Game *removido = desempilhar(&pilha);
            if (removido != NULL) {
                printf("(R) %s\n", removido->name);
            }
        }
    }

    // Mostrar pilha final
    mostrarPilha(&pilha);

    // Free memory
    freePilha(&pilha);
    
    for (int i = 0; i < gameCount; i++)
    {
        freeGameArrays(&games[i]);
    }
    free(games);
    
    return 0;
}