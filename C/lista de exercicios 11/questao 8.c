#include <stdio.h>

// Definição da estrutura para representar dia, mês e ano
struct Data {
    int dia;
    int mes;
    int ano;
};

int main() {
    // Declarando uma variável do tipo struct Data
    struct Data hoje;

    // Preenchendo os valores para dia, mês e ano
    hoje.dia = 18;
    hoje.mes = 6;
    hoje.ano = 2024;

    // Exibindo os valores
    printf("Data de hoje: %d/%d/%d\n", hoje.dia, hoje.mes, hoje.ano);

    return 0;
}
