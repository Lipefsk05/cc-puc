// avl.c
// Compile: gcc -std=c11 -O2 -o avl avl.c
// Execute: ./avl < input.txt
// input.txt: linhas com IDs até FIM, depois linhas com nomes até FIM

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Game {
    int id;
    char *name;
    char *releaseDate;
    int estimateOwners;
    double price;
    char **supportedLanguages; int suppCount;
    int metacriticScore;
    double userScore;
    int achieviments;
    char **publishers; int pubCount;
    char **developers; int devCount;
    char **categories; int catCount;
    char **genres; int genCount;
    char **tags; int tagCount;
} Game;

typedef struct Node {
    Game *game;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

FILE *logF = NULL;

// -------------------- util string helpers --------------------
static char *strdup_safe(const char *s) {
    if (!s) return NULL;
    char *r = malloc(strlen(s) + 1);
    if (!r) { perror("malloc"); exit(1); }
    strcpy(r, s);
    return r;
}

static char *trim_inplace(char *s) {
    if (!s) return s;
    // trim leading
    while (*s && isspace((unsigned char)*s)) s++;
    // If we shifted head, make copy
    char *start = s;
    // trim trailing
    char *end = start + strlen(start) - 1;
    while (end >= start && isspace((unsigned char)*end)) { *end = '\0'; end--; }
    return strdup_safe(start); // return newly allocated trimmed copy
}

// remove surrounding quotes or apostrophes
static char *strip_quotes(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    size_t i = 0, j = n;
    while (i < n && isspace((unsigned char)s[i])) i++;
    while (j > i && isspace((unsigned char)s[j-1])) j--;
    if (j - i >= 2 && ((s[i] == '"' && s[j-1] == '"') || (s[i] == '\'' && s[j-1] == '\''))) {
        // interior substring
        char *r = malloc(j - i - 1 + 1);
        if (!r) { perror("malloc"); exit(1); }
        memcpy(r, s + i + 1, j - i - 2);
        r[j - i - 2] = '\0';
        return r;
    } else {
        // simple trim copy
        char *r = malloc(j - i + 1);
        if (!r) { perror("malloc"); exit(1); }
        memcpy(r, s + i, j - i);
        r[j - i] = '\0';
        return r;
    }
}

// parse array-like string: "[a, b, c]" or "[]" or maybe "['a','b']"
static char **parse_array_field(const char *s, int *outCount) {
    *outCount = 0;
    if (!s) return NULL;
    // trim
    const char *p = s;
    while (*p && isspace((unsigned char)*p)) p++;
    size_t len = strlen(p);
    if (len >= 2 && p[0] == '[' && p[len-1] == ']') {
        // interior
        char *inner = strndup(p+1, len-2);
        // split on commas (not supporting nested quotes here because arrays are simple)
        char *cur = inner;
        char *token;
        char **arr = NULL;
        while ((token = strsep(&cur, ",")) != NULL) {
            char *ttrim = trim_inplace(token);
            // remove surrounding quotes/apostrophes
            char *clean = strip_quotes(ttrim);
            free(ttrim);
            // if empty after trimming, skip
            int allws = 1;
            for (int i = 0; clean && clean[i]; ++i) if (!isspace((unsigned char)clean[i])) { allws = 0; break; }
            if (clean && !allws && strlen(clean) > 0) {
                arr = realloc(arr, sizeof(char*) * (*outCount + 1));
                arr[*outCount] = clean;
                (*outCount)++;
            } else {
                free(clean);
            }
        }
        free(inner);
        if (*outCount == 0) {
            free(arr);
            return NULL;
        }
        return arr;
    } else {
        // not bracketed: maybe empty string
        return NULL;
    }
}

// -------------------- CSV parsing --------------------
// Parse CSV line where fields may be quoted and contain commas.
// returns array of pointers (must be freed) and sets count.
static char **parse_csv_line(const char *line, int *count) {
    *count = 0;
    if (!line) return NULL;
    const char *p = line;
    int inQuotes = 0;
    char *buf = malloc(strlen(line) + 1);
    if (!buf) { perror("malloc"); exit(1); }
    int bi = 0;
    char **fields = NULL;
    for (size_t i = 0; ; ++i) {
        char c = line[i];
        if (c == '"' ) {
            inQuotes = !inQuotes;
            buf[bi++] = c; // keep quotes for later parsing simplification
        } else if ((c == ',' && !inQuotes) || c == '\0' || c == '\n') {
            buf[bi] = '\0';
            // allocate and copy trimmed field
            char *field = strdup_safe(buf);
            fields = realloc(fields, sizeof(char*) * ((*count)+1));
            fields[*count] = field;
            (*count)++;
            bi = 0;
            if (c == '\0' || c == '\n') break;
        } else {
            buf[bi++] = c;
        }
    }
    free(buf);
    return fields;
}

// -------------------- Game list --------------------
typedef struct GameList {
    Game **items;
    int size;
    int cap;
} GameList;

static void game_list_init(GameList *gl) {
    gl->items = NULL; gl->size = 0; gl->cap = 0;
}
static void game_list_add(GameList *gl, Game *g) {
    if (gl->size == gl->cap) {
        gl->cap = gl->cap ? gl->cap * 2 : 16;
        gl->items = realloc(gl->items, sizeof(Game*) * gl->cap);
    }
    gl->items[gl->size++] = g;
}
static Game *find_game_by_id(GameList *gl, int id) {
    for (int i = 0; i < gl->size; ++i) if (gl->items[i]->id == id) return gl->items[i];
    return NULL;
}

// -------------------- AVL helpers --------------------
static int max_int(int a, int b) { return a > b ? a : b; }
static int height(Node *n) { return n ? n->height : 0; }

static Node *new_node(Game *g) {
    Node *n = malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->game = g;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

static Node *rotate_right(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max_int(height(y->left), height(y->right)) + 1;
    x->height = max_int(height(x->left), height(x->right)) + 1;
    return x;
}
static Node *rotate_left(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max_int(height(x->left), height(x->right)) + 1;
    y->height = max_int(height(y->left), height(y->right)) + 1;
    return y;
}

static int get_balance(Node *n) {
    if (!n) return 0;
    return height(n->left) - height(n->right);
}

// Insert by game->name. If already exists, don't insert.
static Node *avl_insert(Node *node, Game *g, int *inserted) {
    if (!node) {
        *inserted = 1;
        if (logF) fprintf(logF, "INSERCAO: %s inserido com sucesso!\n", g->name);
        return new_node(g);
    }
    int cmp = strcmp(g->name, node->game->name);
    if (cmp < 0) node->left = avl_insert(node->left, g, inserted);
    else if (cmp > 0) node->right = avl_insert(node->right, g, inserted);
    else { // equal
        *inserted = 0;
        if (logF) fprintf(logF, "INSERCAO: %s ja existente!\n", g->name);
        return node;
    }
    node->height = 1 + max_int(height(node->left), height(node->right));
    int balance = get_balance(node);
    // Left Left
    if (balance > 1 && strcmp(g->name, node->left->game->name) < 0)
        return rotate_right(node);
    // Right Right
    if (balance < -1 && strcmp(g->name, node->right->game->name) > 0)
        return rotate_left(node);
    // Left Right
    if (balance > 1 && strcmp(g->name, node->left->game->name) > 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    // Right Left
    if (balance < -1 && strcmp(g->name, node->right->game->name) < 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

// -------------------- Search with path --------------------
// Build path string starting "raiz" then " esq"/" dir"
static int search_with_path(Node *root, const char *name, char **outPath) {
    // create dynamic string
    size_t cap = 64;
    char *buf = malloc(cap);
    if (!buf) { perror("malloc"); exit(1); }
    strcpy(buf, "raiz");
    size_t len = strlen(buf);
    Node *cur = root;
    while (cur) {
        int cmp = strcmp(name, cur->game->name);
        if (cmp == 0) {
            *outPath = buf;
            return 1;
        } else if (cmp < 0) {
            // append " esq"
            const char *add = " esq";
            size_t need = len + strlen(add) + 1;
            if (need > cap) { cap = need*2; buf = realloc(buf, cap); if (!buf){perror("realloc"); exit(1);} }
            strcat(buf, add); len += strlen(add);
            cur = cur->left;
        } else {
            const char *add = " dir";
            size_t need = len + strlen(add) + 1;
            if (need > cap) { cap = need*2; buf = realloc(buf, cap); if (!buf){perror("realloc"); exit(1);} }
            strcat(buf, add); len += strlen(add);
            cur = cur->right;
        }
    }
    *outPath = buf;
    return 0;
}

// -------------------- CSV -> Game conversion --------------------
static long parse_long_def(const char *s, long def) {
    if (!s || strlen(s)==0) return def;
    return strtol(s, NULL, 10);
}
static double parse_double_def(const char *s, double def) {
    if (!s || strlen(s)==0) return def;
    return strtod(s, NULL);
}

static Game *make_game_from_fields(char **fields, int fcount) {
    // Expect indexes [0..13]
    if (fcount < 14) return NULL;
    Game *g = calloc(1, sizeof(Game));
    g->id = (int)parse_long_def(fields[0], 0);
    g->name = strip_quotes(fields[1]);
    g->releaseDate = strip_quotes(fields[2]);
    g->estimateOwners = (int)parse_long_def(fields[3], 0);
    g->price = parse_double_def(fields[4], 0.0);
    g->supportedLanguages = parse_array_field(fields[5], &g->suppCount);
    g->metacriticScore = (int)parse_long_def(fields[6], 0);
    g->userScore = parse_double_def(fields[7], 0.0);
    g->achieviments = (int)parse_long_def(fields[8], 0);
    g->publishers = parse_array_field(fields[9], &g->pubCount);
    g->developers = parse_array_field(fields[10], &g->devCount);
    g->categories = parse_array_field(fields[11], &g->catCount);
    g->genres = parse_array_field(fields[12], &g->genCount);
    g->tags = parse_array_field(fields[13], &g->tagCount);
    return g;
}

// -------------------- cleanup helpers (not exhaustive) --------------------
static void free_game(Game *g) {
    if (!g) return;
    free(g->name);
    free(g->releaseDate);
    for (int i=0;i<g->suppCount;i++) free(g->supportedLanguages[i]);
    free(g->supportedLanguages);
    for (int i=0;i<g->pubCount;i++) free(g->publishers[i]);
    free(g->publishers);
    for (int i=0;i<g->devCount;i++) free(g->developers[i]);
    free(g->developers);
    for (int i=0;i<g->catCount;i++) free(g->categories[i]);
    free(g->categories);
    for (int i=0;i<g->genCount;i++) free(g->genres[i]);
    free(g->genres);
    for (int i=0;i<g->tagCount;i++) free(g->tags[i]);
    free(g->tags);
    free(g);
}

// -------------------- main --------------------
int main(void) {
    // open CSV
    const char *csvpath = "/tmp/games.csv";
    FILE *f = fopen(csvpath, "r");
    if (!f) {
        fprintf(stderr, "Erro ao abrir %s\n", csvpath);
        return 1;
    }
    char *line = NULL;
    size_t lcap = 0;
    ssize_t linelen;

    // skip header line
    if ((linelen = getline(&line, &lcap, f)) == -1) {
        fprintf(stderr, "CSV vazio\n");
        fclose(f);
        return 1;
    }

    GameList gl; game_list_init(&gl);

    // read all game lines
    while ((linelen = getline(&line, &lcap, f)) != -1) {
        // remove newline at end
        while (linelen > 0 && (line[linelen-1] == '\n' || line[linelen-1] == '\r')) { line[--linelen] = '\0'; }
        int fcount = 0;
        char **fields = parse_csv_line(line, &fcount);
        if (fcount >= 1) {
            Game *g = make_game_from_fields(fields, fcount);
            if (g) game_list_add(&gl, g);
        }
        for (int i=0;i<fcount;i++) free(fields[i]);
        free(fields);
    }
    free(line);
    fclose(f);

    // open log file
    logF = fopen("858158_arvoreBinaria.txt", "w");
    if (!logF) {
        fprintf(stderr, "Aviso: nao foi possivel criar arquivo de log.\n");
    }

    // AVL root
    Node *root = NULL;

    // Stage 1: read IDs until FIM (stdin)
    char *input_line = NULL;
    size_t in_cap = 0;
    ssize_t in_len;
    // read IDs
    while ((in_len = getline(&input_line, &in_cap, stdin)) != -1) {
        // trim newline
        while (in_len > 0 && (input_line[in_len-1] == '\n' || input_line[in_len-1] == '\r')) { input_line[--in_len] = '\0'; }
        // skip empty
        if (in_len == 0) continue;
        if (strcasecmp(input_line, "FIM") == 0) break;
        // parse id
        char *trim = trim_inplace(input_line);
        int id = atoi(trim);
        free(trim);
        Game *g = find_game_by_id(&gl, id);
        if (g) {
            int inserted = 0;
            root = avl_insert(root, g, &inserted);
        } else {
            // id nao encontrado -> ignore
        }
    }

    // Stage 2: read names until FIM and perform searches
    while ((in_len = getline(&input_line, &in_cap, stdin)) != -1) {
        while (in_len > 0 && (input_line[in_len-1] == '\n' || input_line[in_len-1] == '\r')) { input_line[--in_len] = '\0'; }
        if (in_len == 0) continue;
        if (strcasecmp(input_line, "FIM") == 0) break;
        // The user gives a name line; compare exactly as stored (case-sensitive like Java)
        char *name_query = strdup_safe(input_line);
        char *path = NULL;
        int found = search_with_path(root, name_query, &path);
        printf("%s: %s %s\n", name_query, path, found ? "SIM" : "NAO");
        free(path);
        free(name_query);
    }

    // cleanup
    if (logF) fclose(logF);
    free(input_line);

    // free games
    for (int i=0;i<gl.size;i++) free_game(gl.items[i]);
    free(gl.items);

    // Note: not freeing tree nodes for brevity (program soon exits)
    return 0;
}
