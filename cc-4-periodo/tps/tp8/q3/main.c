#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 1000
#define MAX_LINE 10000
#define TAM_TAB 21

typedef struct Game {
    int id;
    char name[MAX_NAME];
    char releaseDate[50];
    int estimateOwners;
    double price;
} Game;

typedef struct NodeHash {
    Game game;
    struct NodeHash *prox;
} NodeHash;

void parse_csv_line(char *line, Game *game) {
    char *ptr = line;
    int field = 0;
    int in_quotes = 0;
    char buffer[MAX_NAME];
    int buf_index = 0;
    
    while (*ptr) {
        if (*ptr == '"') {
            in_quotes = !in_quotes;
            ptr++;
            continue;
        }
        
        if (*ptr == ',' && !in_quotes) {
            buffer[buf_index] = '\0';
            
            switch(field) {
                case 0:
                    game->id = atoi(buffer);
                    break;
                case 1:
                    strcpy(game->name, buffer);
                    break;
                case 2:
                    strcpy(game->releaseDate, buffer);
                    break;
                case 3:
                    game->estimateOwners = atoi(buffer);
                    break;
                case 4:
                    game->price = atof(buffer);
                    break;
            }
            
            field++;
            buf_index = 0;
            ptr++;
            continue;
        }
        
        if (buf_index < MAX_NAME - 1) {
            buffer[buf_index++] = *ptr;
        }
        ptr++;
    }
    
    // Último campo
    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        if (field == 4) {
            game->price = atof(buffer);
        }
    }
}

Game* buscar_jogo_por_id(Game* jogos, int total, int id) {
    for (int i = 0; i < total; i++) {
        if (jogos[i].id == id) {
            return &jogos[i];
        }
    }
    return NULL;
}

int calcular_ascii(const char *nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += (int)nome[i];
    }
    return soma;
}

int hash(const char *nome) {
    int ascii = calcular_ascii(nome);
    return ascii % TAM_TAB;
}

void inserir_na_tabela(NodeHash** tabela, Game* game) {
    int pos = hash(game->name);
    
    NodeHash* novo = malloc(sizeof(NodeHash));
    novo->game = *game;
    novo->prox = tabela[pos];
    tabela[pos] = novo;
}

int pesquisar_na_tabela(NodeHash** tabela, const char* nome) {
    int pos = hash(nome);
    NodeHash* atual = tabela[pos];
    
    while (atual != NULL) {
        if (strcmp(atual->game.name, nome) == 0) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void liberar_tabela(NodeHash** tabela) {
    for (int i = 0; i < TAM_TAB; i++) {
        NodeHash* atual = tabela[i];
        while (atual != NULL) {
            NodeHash* temp = atual;
            atual = atual->prox;
            free(temp);
        }
        tabela[i] = NULL;
    }
}

int main() {
    FILE* arquivo = fopen("/tmp/games.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    
    char linha[MAX_LINE];
    fgets(linha, sizeof(linha), arquivo);
    
    Game jogos[5000];
    int total_jogos = 0;
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL && total_jogos < 5000) {
        linha[strcspn(linha, "\n")] = '\0';
        linha[strcspn(linha, "\r")] = '\0';
        
        parse_csv_line(linha, &jogos[total_jogos]);
        total_jogos++;
    }
    
    fclose(arquivo);
    
    NodeHash* tabela[TAM_TAB];
    for (int i = 0; i < TAM_TAB; i++) {
        tabela[i] = NULL;
    }
    
    char input[MAX_NAME];
    
    // Primeira parte: ler IDs
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) continue;
        if (strcasecmp(input, "FIM") == 0) break;
        
        int id = atoi(input);
        Game* jogo = buscar_jogo_por_id(jogos, total_jogos, id);
        if (jogo != NULL) {
            inserir_na_tabela(tabela, jogo);
        }
    }
    
    // Criar arquivo de log
    FILE* log = fopen("858158_hashIndireta.txt", "w");
    if (log) {
        for (int i = 0; i < TAM_TAB; i++) {
            NodeHash* atual = tabela[i];
            while (atual != NULL) {
                fprintf(log, "%s inserido com sucesso na posicao %d da tabela\n", 
                        atual->game.name, i);
                atual = atual->prox;
            }
        }
        fclose(log);
    }
    
    // Segunda parte: pesquisar nomes
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) continue;
        if (strcasecmp(input, "FIM") == 0) break;
        
        int pos = hash(input);
        int encontrado = pesquisar_na_tabela(tabela, input);
        printf("%s (Posicao: %d) %s\n", input, pos, encontrado ? "SIM" : "NAO");
    }
    
    liberar_tabela(tabela);
    
    return 0;
}