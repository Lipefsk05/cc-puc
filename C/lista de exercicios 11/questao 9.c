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

// Estrutura que combina data e hora
struct DataHora {
    struct Data data;
    struct Horario horario;
};

int main() {
    // Declarando uma variável do tipo struct DataHora
    struct DataHora agora;

    // Preenchendo os valores para data e hora
    agora.data.dia = 18;
    agora.data.mes = 6;
    agora.data.ano = 2024;
    agora.horario.horas = 10;
    agora.horario.minutos = 30;
    agora.horario.segundos = 45;

    // Exibindo os valores de data e hora
    printf("Data e Hora atual: %d/%d/%d %02d:%02d:%02d\n", 
           agora.data.dia, agora.data.mes, agora.data.ano,
           agora.horario.horas, agora.horario.minutos, agora.horario.segundos);

    return 0;
}
