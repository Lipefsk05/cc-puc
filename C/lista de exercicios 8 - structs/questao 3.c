#include <stdio.h>

// Definindo o número máximo de clientes
#define MAX_CLIENTES 500

// Estrutura para armazenar os dados de cada cliente
struct Cliente {
    int codigo_cliente;
    char email[50];
    int horas_acesso;
    char pagina;
};

// Função para calcular o valor a pagar por cada cliente
void calcularValorPagar(struct Cliente clientes[], int num_clientes) {
    float valor_pagar;
    printf("Relatório de Pagamento:\n\n");
    for (int i = 0; i < num_clientes; i++) {
        valor_pagar = 0.0;
        valor_pagar += 35.0; // Valor fixo para as primeiras 20 horas
        if (clientes[i].horas_acesso > 20) {
            valor_pagar += (clientes[i].horas_acesso - 20) * 2.5;
        }
        if (clientes[i].pagina == 'S') {
            valor_pagar += 40.0;
        }
        printf("Código do Cliente: %d\n", clientes[i].codigo_cliente);
        printf("E-mail: %s\n", clientes[i].email);
        printf("Número de horas de acesso: %d\n", clientes[i].horas_acesso);
        printf("Possui página pessoal: %c\n", clientes[i].pagina);
        printf("Valor a pagar: R$ %.2f\n\n", valor_pagar);
    }
}

int main() {
    // Vetor de clientes
    struct Cliente clientes[MAX_CLIENTES] = {
        {1, "cliente1@email.com", 25, 'N'},
        {2, "cliente2@email.com", 18, 'S'},
        {3, "cliente3@email.com", 30, 'N'}
        // Adicionar mais clientes aqui
    };

    int num_clientes = 3; // Número de clientes no vetor

    // Chamada da função para calcular o valor a pagar por cada cliente
    calcularValorPagar(clientes, num_clientes);

    return 0;
}
