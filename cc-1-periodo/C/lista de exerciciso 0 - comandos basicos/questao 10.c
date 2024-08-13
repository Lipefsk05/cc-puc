#include <stdio.h>

int main() {
    int hora, minuto;
    int minutos_passados;

    // Leitura da hora
    printf("Digite a hora (0-23): ");
    scanf("%d", &hora);

    // Leitura do minuto
    printf("Digite o minuto (0-59): ");
    scanf("%d", &minuto);

    // Cálculo dos minutos passados desde o início do dia
    minutos_passados = hora * 60 + minuto;

    // Exibição dos minutos passados
    printf("Desde o início do dia, se passaram %d minutos.\n", minutos_passados);

    return 0;
}
