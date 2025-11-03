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

long long comparacoes = 0;
long long movimentacoes = 0;

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

// Function to convert date to a comparable format (YYYYMMDD)
int dateToInt(const char *date)
{
    if (!date || strlen(date) == 0)
        return 0;

    // Try different date formats
    int day, month, year;

    // Format: "dd/mm/yyyy"
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) == 3)
    {
        return year * 10000 + month * 100 + day;
    }

    // Format: "Mon dd, yyyy" (e.g., "Oct 18, 2018")
    char monthStr[10];
    if (sscanf(date, "%3s %d, %d", monthStr, &day, &year) == 3)
    {
        month = monthStrToNum(monthStr);
        if (month > 0)
        {
            return year * 10000 + month * 100 + day;
        }
    }

    // If we can't parse, return 0 (will be considered oldest)
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
        sprintf(priceStr, "%.1f", g->price); // MUDADO: %.2f -> %.1f

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

// ---------- Quicksort por Release_date (com AppID como desempate) ----------

// Comparison function for sorting
int compareGames(Game *a, Game *b)
{
    comparacoes++;

    // Compare release dates
    int dateA = dateToInt(a->releaseDate);
    int dateB = dateToInt(b->releaseDate);

    if (dateA != dateB)
    {
        return dateA - dateB;
    }

    // If dates are equal, compare by AppID
    return a->id - b->id;
}

// Partition function for Quicksort
int partition(Game *arr, int low, int high)
{
    Game pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (compareGames(&arr[j], &pivot) <= 0)
        {
            i++;
            // Swap arr[i] and arr[j]
            Game temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            movimentacoes += 3;
        }
    }

    // Swap arr[i+1] and arr[high] (pivot)
    Game temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    movimentacoes += 3;

    return i + 1;
}

// Quicksort recursive function
void quicksort(Game *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Wrapper function for Quicksort
void quickSortWrapper(Game *arr, int n)
{
    quicksort(arr, 0, n - 1);
}

// ---------- MAIN ----------

int main()
{
    Game *games;
    int gameCount = loadGames(&games);

    int ids[500];
    int idCount = 0;
    char input[50];

    while (1)
    {
        if (!fgets(input, sizeof(input), stdin))
            break;
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "FIM") == 0)
            break;
        ids[idCount++] = atoi(input);
    }

    Game *selected = malloc(idCount * sizeof(Game));
    int count = 0;
    for (int i = 0; i < idCount; i++)
    {
        for (int j = 0; j < gameCount; j++)
        {
            if (games[j].id == ids[i])
            {
                copyGame(&selected[count++], &games[j]);
                break;
            }
        }
    }

    // Reset counters
    comparacoes = 0;
    movimentacoes = 0;

    clock_t start = clock();
    quickSortWrapper(selected, count);
    clock_t end = clock();
    double tempo = (double)(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < count; i++)
    {
        printGame(&selected[i]);
    }

    // Create log file - CHANGE "858158" to your actual registration number
    FILE *log = fopen("858158_quicksort.txt", "w");
    if (log)
    {
        fprintf(log, "858158\t%lld\t%lld\t%.6f\n", comparacoes, movimentacoes, tempo);
        fclose(log);
    }

    // Free memory
    for (int i = 0; i < count; i++)
    {
        freeGameArrays(&selected[i]);
    }
    free(selected);

    for (int i = 0; i < gameCount; i++)
    {
        freeGameArrays(&games[i]);
    }
    free(games);

    return 0;
}