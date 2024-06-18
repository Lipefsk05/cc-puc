#include <stdio.h>
#include <string.h>

// Definindo o número máximo de registros
#define MAX_REGISTROS 15

// Estrutura para armazenar os dados de cada registro
struct Registro {
    char nome_loja[50];
    char telefone[15];
    float preco;
};

// Função para calcular a média dos preços
float calcularMedia(struct Registro registros[], int num_registros) {
    float soma = 0.0;
    for (int i = 0; i < num_registros; i++) {
        soma += registros[i].preco;
    }
    return soma / num_registros;
}

// Função para exibir as lojas com preço abaixo da média
void exibirLojasAbaixoDaMedia(struct Registro registros[], int num_registros, float media) {
    printf("Lojas com preço abaixo da média de %.2f:\n", media);
    for (int i = 0; i < num_registros; i++) {
        if (registros[i].preco < media) {
            printf("Nome: %s, Telefone: %s\n", registros[i].nome_loja, registros[i].telefone);
        }
    }
}

int main() {
    // Vetor de registros de eletrodomésticos
    struct Registro registros[MAX_REGISTROS] = {
        {"Loja A", "(11) 1234-5678", 1500.0},
        {"Loja B", "(11) 2345-6789", 1200.0},
        {"Loja C", "(11) 3456-7890", 1800.0},
        {"Loja D", "(11) 4567-8901", 1100.0},
        {"Loja E", "(11) 5678-9012", 1300.0},
        {"Loja F", "(11) 6789-0123", 1400.0},
        {"Loja G", "(11) 7890-1234", 1000.0},
        {"Loja H", "(11) 8901-2345", 1600.0},
        {"Loja I", "(11) 9012-3456", 1150.0},
        {"Loja J", "(11) 0123-4567", 1350.0},
        {"Loja K", "(11) 1234-5678", 1250.0},
        {"Loja L", "(11) 2345-6789", 1700.0},
        {"Loja M", "(11) 3456-7890", 1900.0},
        {"Loja N", "(11) 4567-8901", 1650.0},
        {"Loja O", "(11) 5678-9012", 1550.0}
    };

    int num_registros = MAX_REGISTROS;

    // Calcular a média dos preços
    float media = calcularMedia(registros, num_registros);
    printf("Média dos preços: %.2f\n\n", media);

    // Exibir lojas com preço abaixo da média
    exibirLojasAbaixoDaMedia(registros, num_registros, media);

    return 0;
}
