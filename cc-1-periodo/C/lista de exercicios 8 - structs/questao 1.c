#include <stdio.h>
#include <string.h>

// Definindo o tamanho máximo do vetor de pessoas
#define MAX_PESSOAS 40

// Estrutura para armazenar os dados de cada pessoa
struct Pessoa {
    char nome[50];
    int dia_aniversario;
    int mes_aniversario;
};

// Função para imprimir as pessoas que fazem aniversário em cada mês
void imprimirAniversariantes(struct Pessoa pessoas[], int num_pessoas) {
    const char *meses[12] = {
        "Janeiro", "Fevereiro", "Março", "Abril",
        "Maio", "Junho", "Julho", "Agosto",
        "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    // Loop pelos meses
    for (int mes = 1; mes <= 12; mes++) {
        printf("Aniversariantes de %s:\n", meses[mes - 1]);

        // Loop pelas pessoas para encontrar os aniversariantes do mês atual
        for (int i = 0; i < num_pessoas; i++) {
            if (pessoas[i].mes_aniversario == mes) {
                printf("%s - Dia %d\n", pessoas[i].nome, pessoas[i].dia_aniversario);
            }
        }
        printf("\n");
    }
}

int main() {
    struct Pessoa pessoas[MAX_PESSOAS] = {
        {"João", 10, 3},     // Exemplo: João faz aniversário dia 10 de março
        {"Maria", 25, 6},    // Exemplo: Maria faz aniversário dia 25 de junho
        // Adicionar mais pessoas aqui
    };

    int num_pessoas = 2; // Número de pessoas no vetor

    // Chamada da função para imprimir os aniversariantes de cada mês
    imprimirAniversariantes(pessoas, num_pessoas);

    return 0;
}
