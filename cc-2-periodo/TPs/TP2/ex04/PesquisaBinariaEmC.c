#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define maxLinha 160
#define MAX_SELECTED 801 // Número máximo de Pokémons selecionados

typedef struct date {
    int dia;
    int mes;
    int ano;
} date;

typedef struct pokemon {
    int id;
    int generation;
    char* name;
    char* description;
    char* type1;
    char* type2;
    char* abilities;
    double weight;
    double height;
    int captureRate;
    bool isLegendary;
    char* captureDate;
} pokemon;

pokemon pokemons[801];
pokemon selectedPokemons[MAX_SELECTED]; // Array para os Pokémons selecionados
int selectedCount = 0; // Contador de Pokémons selecionados

void substring(const char* original, char* data, int length) {
    strncpy(data, original + (strlen(original) - 11), length);
    data[length] = '\0';
}

void preencherPokedex() {
    FILE* file = fopen("/tmp/pokemon.csv", "r");
    if (file == NULL) {
        return;
    }

    char linha[maxLinha];
    fgets(linha, maxLinha, file);
    int i = 0;

    while (fgets(linha, maxLinha, file) && i < 801) {
        char data[13];
        substring(linha, data, 12);
        char* token1 = strtok(linha, "\"");
        char* primeiraParte = token1;
        char* token2 = strtok(NULL, "\"");
        char* habilidades = token2 ? strdup(token2) : NULL;
        char* token3 = strtok(NULL, "\"");
        char* segundaParte = token3;

        char* tok = strtok(primeiraParte, ",");
        pokemons[i].id = atoi(tok);

        tok = strtok(NULL, ",");
        pokemons[i].generation = atoi(tok);

        tok = strtok(NULL, ",");
        pokemons[i].name = strdup(tok ? tok : "");

        tok = strtok(NULL, ",");
        pokemons[i].description = strdup(tok ? tok : "");

        tok = strtok(NULL, ",");
        pokemons[i].type1 = strdup(tok ? tok : "");

        tok = strtok(NULL, ",");
        pokemons[i].type2 = (tok && strlen(tok) > 0) ? strdup(tok) : strdup("0");

        pokemons[i].abilities = habilidades ? habilidades : strdup("");

        char* tok2 = strtok(segundaParte, ",");
        pokemons[i].weight = (tok2 && strlen(tok2) > 0) ? strtod(tok2, NULL) : 0;

        tok2 = strtok(NULL, ",");
        pokemons[i].height = (tok2 && strlen(tok2) > 0) ? strtod(tok2, NULL) : 0;

        tok2 = strtok(NULL, ",");
        pokemons[i].captureRate = atoi(tok2);

        tok2 = strtok(NULL, ",");
        pokemons[i].isLegendary = (tok2 && atoi(tok2) != 0);

        tok2 = strtok(NULL, ",");
        pokemons[i].captureDate = strdup(data);

        i++;
    }

    fclose(file);
}

char* tratarTipos(int n) {
    char* resultado = (char*)malloc(maxLinha * sizeof(char));
    if (strcmp(pokemons[n - 1].type2, "0") == 0) {
        sprintf(resultado, "['%s']", pokemons[n - 1].type1);
    } else {
        sprintf(resultado, "['%s', '%s']", pokemons[n - 1].type1, pokemons[n - 1].type2);
    }
    return resultado;
}

char* tratarLendario(int n) {
    return pokemons[n - 1].isLegendary ? "true" : "false";
}

char* toString(int n) {
    char* resultado = (char*)malloc(maxLinha * sizeof(char));
    char* tipos = tratarTipos(n);
    char* lendario = tratarLendario(n);

    sprintf(resultado, "[#%d -> %s: %s - %s - %s - %.1lfkg - %.1lfm - %d%% - %s - %d gen] - %s", 
            pokemons[n - 1].id, pokemons[n - 1].name, pokemons[n - 1].description, tipos, 
            pokemons[n - 1].abilities, pokemons[n - 1].weight, pokemons[n - 1].height, 
            pokemons[n - 1].captureRate, lendario, pokemons[n - 1].generation, 
            pokemons[n - 1].captureDate);

    free(tipos); // Liberar memória alocada para tipos
    free(lendario); // Liberar memória alocada para lendário
    return resultado;
}

bool isFim(char* str) {
    return strcmp(str, "FIM") != 0; // Se não for FIM, retorna true
}

// Função de busca binária para verificar se o nome do Pokémon está entre os selecionados
bool binarySearch(char* target) {
    int left = 0;
    int right = selectedCount - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(selectedPokemons[mid].name, target);
        
        if (cmp == 0) {
            return true; // Nome encontrado
        } else if (cmp < 0) {
            left = mid + 1; // Pesquisa na metade superior
        } else {
            right = mid - 1; // Pesquisa na metade inferior
        }
    }
    return false; // Nome não encontrado
}

int main() {
    preencherPokedex();

    char* str = (char*)malloc(10 * sizeof(char));

    // Recebendo IDs de Pokémons
    do {
        fgets(str, 10, stdin);
        str[strcspn(str, "\n")] = 0;

        if (isFim(str)) {
            int n = atoi(str);
            for (int i = 0; i < 801; i++) {
                if (pokemons[i].id == n) {
                    selectedPokemons[selectedCount++] = pokemons[i]; // Adiciona o Pokémon selecionado
                    break; // Para não adicionar mais de uma vez
                }
            }
        }
    } while (isFim(str));

    // Recebendo nomes de Pokémons para busca
    while (true) {
        fgets(str, 100, stdin);
        str[strcspn(str, "\n")] = 0;

        if (strcmp(str, "FIM") == 0) {
            break; // Para ao receber "FIM"
        }

        if (binarySearch(str)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
    }

    // Liberar a memória alocada
    for (int i = 0; i < 801; i++) {
        free(pokemons[i].name);
        free(pokemons[i].description);
        free(pokemons[i].type1);
        free(pokemons[i].type2);
        free(pokemons[i].abilities);
        free(pokemons[i].captureDate);
    }
    free(str); // Liberar a memória alocada para str

    return 0;
}
