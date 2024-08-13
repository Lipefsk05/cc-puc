#include <stdio.h>
#include <string.h>

// Definindo o número máximo de volumes por área
#define MAX_VOLUMES 500

// Estrutura para armazenar os dados de cada volume
struct Livro {
    int codigo_catalogacao;
    char doacao; // 'S' ou 'N'
    char nome_obra[100];
    char nome_autor[50];
    char editora[50];
    char area[20];
};

// Função para cadastrar os volumes em vetores distintos por área
void cadastrarVolumes(struct Livro exatas[], struct Livro humanas[], struct Livro biologicas[], int *countExatas, int *countHumanas, int *countBiologicas) {
    int codigo;
    printf("Cadastro de Livros:\n\n");

    do {
        printf("Digite o código de catalogação (-1 para sair): ");
        scanf("%d", &codigo);
        getchar(); // Limpar o buffer de entrada

        if (codigo == -1) {
            break;
        }

        struct Livro livro;
        livro.codigo_catalogacao = codigo;

        printf("É uma doação? (S/N): ");
        scanf(" %c", &livro.doacao);
        getchar(); // Limpar o buffer de entrada

        printf("Nome da obra: ");
        fgets(livro.nome_obra, sizeof(livro.nome_obra), stdin);
        livro.nome_obra[strcspn(livro.nome_obra, "\n")] = '\0'; // Remover o caractere de nova linha

        printf("Nome do autor: ");
        fgets(livro.nome_autor, sizeof(livro.nome_autor), stdin);
        livro.nome_autor[strcspn(livro.nome_autor, "\n")] = '\0'; // Remover o caractere de nova linha

        printf("Editora: ");
        fgets(livro.editora, sizeof(livro.editora), stdin);
        livro.editora[strcspn(livro.editora, "\n")] = '\0'; // Remover o caractere de nova linha

        printf("Área (exatas, humanas, biológicas): ");
        fgets(livro.area, sizeof(livro.area), stdin);
        livro.area[strcspn(livro.area, "\n")] = '\0'; // Remover o caractere de nova linha

        // Adicionar o livro ao vetor correspondente à área
        if (strcmp(livro.area, "exatas") == 0) {
            exatas[(*countExatas)++] = livro;
        } else if (strcmp(livro.area, "humanas") == 0) {
            humanas[(*countHumanas)++] = livro;
        } else if (strcmp(livro.area, "biologicas") == 0) {
            biologicas[(*countBiologicas)++] = livro;
        } else {
            printf("Área inválida!\n");
        }

        printf("\n");

    } while (1);
}

// Função para consultar informações de um livro por código de catalogação e área
void consultarLivro(struct Livro exatas[], struct Livro humanas[], struct Livro biologicas[], int countExatas, int countHumanas, int countBiologicas) {
    int codigo;
    char area[20];
    int encontrado = 0;

    printf("Consulta de Livro:\n\n");
    printf("Digite o código de catalogação (-1 para sair): ");
    scanf("%d", &codigo);
    getchar(); // Limpar o buffer de entrada

    if (codigo == -1) {
        return;
    }

    printf("Digite a área (exatas, humanas, biologicas): ");
    fgets(area, sizeof(area), stdin);
    area[strcspn(area, "\n")] = '\0'; // Remover o caractere de nova linha

    if (strcmp(area, "exatas") == 0) {
        for (int i = 0; i < countExatas; i++) {
            if (exatas[i].codigo_catalogacao == codigo) {
                printf("Informações do Livro:\n");
                printf("Código de Catalogação: %d\n", exatas[i].codigo_catalogacao);
                printf("Doação: %c\n", exatas[i].doacao);
                printf("Nome da Obra: %s\n", exatas[i].nome_obra);
                printf("Nome do Autor: %s\n", exatas[i].nome_autor);
                printf("Editora: %s\n", exatas[i].editora);
                printf("Área: %s\n", exatas[i].area);
                encontrado = 1;
                break;
            }
        }
    } else if (strcmp(area, "humanas") == 0) {
        for (int i = 0; i < countHumanas; i++) {
            if (humanas[i].codigo_catalogacao == codigo) {
                printf("Informações do Livro:\n");
                printf("Código de Catalogação: %d\n", humanas[i].codigo_catalogacao);
                printf("Doação: %c\n", humanas[i].doacao);
                printf("Nome da Obra: %s\n", humanas[i].nome_obra);
                printf("Nome do Autor: %s\n", humanas[i].nome_autor);
                printf("Editora: %s\n", humanas[i].editora);
                printf("Área: %s\n", humanas[i].area);
                encontrado = 1;
                break;
            }
        }
    } else if (strcmp(area, "biologicas") == 0) {
        for (int i = 0; i < countBiologicas; i++) {
            if (biologicas[i].codigo_catalogacao == codigo) {
                printf("Informações do Livro:\n");
                printf("Código de Catalogação: %d\n", biologicas[i].codigo_catalogacao);
                printf("Doação: %c\n", biologicas[i].doacao);
                printf("Nome da Obra: %s\n", biologicas[i].nome_obra);
                printf("Nome do Autor: %s\n", biologicas[i].nome_autor);
                printf("Editora: %s\n", biologicas[i].editora);
                printf("Área: %s\n", biologicas[i].area);
                encontrado = 1;
                break;
            }
        }
    } else {
        printf("Área inválida!\n");
    }

    if (!encontrado) {
        printf("Livro não encontrado.\n");
    }
}

int main() {
    // Vetores para armazenar os livros de cada área
    struct Livro exatas[MAX_VOLUMES], humanas[MAX_VOLUMES], biologicas[MAX_VOLUMES];
    int countExatas = 0, countHumanas = 0, countBiologicas = 0;

    // Cadastro dos volumes de cada área
    cadastrarVolumes(exatas, humanas, biologicas, &countExatas, &countHumanas, &countBiologicas);

    // Consulta de informações de um livro
    do {
        consultarLivro(exatas, humanas, biologicas, countExatas, countHumanas, countBiologicas);
    } while (1);

    return 0;
}
