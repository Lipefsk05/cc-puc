#include <stdio.h>

// Estrutura para representar a hora
struct Horario {
    int horas;
    int minutos;
    int segundos;
};

// Estrutura para representar a data
struct Data {
    int dia;
    int mes;
    int ano;
};

// Estrutura para representar a venda de um produto
struct Venda {
    char nome[100]; // Nome do produto
    float preco;    // Preço do produto
    int quantidade; // Quantidade vendida
    struct Data data;      // Data da venda
    struct Horario horario; // Hora da venda
};

int main() {
    // Declarando uma variável do tipo struct Venda
    struct Venda venda;

    // Preenchendo os valores para a venda
    printf("Digite o nome do produto: ");
    scanf("%99[^\n]", venda.nome); // Lê até 99 caracteres (evita overflow)
    printf("Digite o preço do produto: ");
    scanf("%f", &venda.preco);
    printf("Digite a quantidade vendida: ");
    scanf("%d", &venda.quantidade);
    printf("Digite a data da venda (dia mes ano): ");
    scanf("%d %d %d", &venda.data.dia, &venda.data.mes, &venda.data.ano);
    printf("Digite a hora da venda (horas minutos segundos): ");
    scanf("%d %d %d", &venda.horario.horas, &venda.horario.minutos, &venda.horario.segundos);

    // Exibindo os valores da venda
    printf("\nDetalhes da Venda:\n");
    printf("Nome do produto: %s\n", venda.nome);
    printf("Preço do produto: R$ %.2f\n", venda.preco);
    printf("Quantidade vendida: %d\n", venda.quantidade);
    printf("Data da venda: %d/%d/%d\n", venda.data.dia, venda.data.mes, venda.data.ano);
    printf("Hora da venda: %02d:%02d:%02d\n", venda.horario.horas, venda.horario.minutos, venda.horario.segundos);

    return 0;
}
