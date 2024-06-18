#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para obter o nome do mês por extenso
char* nomeMes(int mes) {
    switch (mes) {
        case 1:
            return "Janeiro";
        case 2:
            return "Fevereiro";
        case 3:
            return "Março";
        case 4:
            return "Abril";
        case 5:
            return "Maio";
        case 6:
            return "Junho";
        case 7:
            return "Julho";
        case 8:
            return "Agosto";
        case 9:
            return "Setembro";
        case 10:
            return "Outubro";
        case 11:
            return "Novembro";
        case 12:
            return "Dezembro";
        default:
            return "Mês inválido";
    }
}

int main() {
    char data[11]; // dd/mm/aaaa
    int dia, mes, ano;

    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    fgets(data, sizeof(data), stdin);

    // Converter a string para inteiros
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    // Verificar se a data é válida
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1 || ano > 9999) {
        printf("Data inválida!\n");
        return 1;
    }

    // Imprimir a data por extenso
    printf("Você nasceu em %02d de %s de %04d\n", dia, nomeMes(mes), ano);

    return 0;
}
