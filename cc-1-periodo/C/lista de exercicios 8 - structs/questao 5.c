#include <stdio.h>

// Definindo a estrutura para armazenar as informações do cliente
struct Cliente {
    char nome[50];
    char endereco[100];
    char telefone[15];
};

int main() {
    // Declarando uma variável do tipo Cliente para armazenar os dados de cada cliente
    struct Cliente cliente1, cliente2;

    // Cadastro do primeiro cliente
    printf("Cadastro do primeiro cliente:\n");
    printf("Nome: ");
    fgets(cliente1.nome, sizeof(cliente1.nome), stdin);
    cliente1.nome[strcspn(cliente1.nome, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Endereço: ");
    fgets(cliente1.endereco, sizeof(cliente1.endereco), stdin);
    cliente1.endereco[strcspn(cliente1.endereco, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Telefone: ");
    fgets(cliente1.telefone, sizeof(cliente1.telefone), stdin);
    cliente1.telefone[strcspn(cliente1.telefone, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("\n");

    // Cadastro do segundo cliente
    printf("Cadastro do segundo cliente:\n");
    printf("Nome: ");
    fgets(cliente2.nome, sizeof(cliente2.nome), stdin);
    cliente2.nome[strcspn(cliente2.nome, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Endereço: ");
    fgets(cliente2.endereco, sizeof(cliente2.endereco), stdin);
    cliente2.endereco[strcspn(cliente2.endereco, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Telefone: ");
    fgets(cliente2.telefone, sizeof(cliente2.telefone), stdin);
    cliente2.telefone[strcspn(cliente2.telefone, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("\n");

    // Exibindo os dados dos clientes cadastrados
    printf("Clientes cadastrados:\n");
    printf("Cliente 1:\n");
    printf("Nome: %s\n", cliente1.nome);
    printf("Endereço: %s\n", cliente1.endereco);
    printf("Telefone: %s\n\n", cliente1.telefone);

    printf("Cliente 2:\n");
    printf("Nome: %s\n", cliente2.nome);
    printf("Endereço: %s\n", cliente2.endereco);
    printf("Telefone: %s\n", cliente2.telefone);

    return 0;
}
