#include <stdio.h>

// Definição da estrutura para representar horas, minutos e segundos
struct Horario {
    int horas;
    int minutos;
    int segundos;
};

int main() {
    // Declarando uma variável do tipo struct Horario
    struct Horario agora;

    // Preenchendo os valores para horas, minutos e segundos
    agora.horas = 10;
    agora.minutos = 30;
    agora.segundos = 45;

    // Exibindo os valores
    printf("Horario atual: %d:%d:%d\n", agora.horas, agora.minutos, agora.segundos);

    return 0;
}
