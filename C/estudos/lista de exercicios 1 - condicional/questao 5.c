#include <stdio.h>

int main() {
    const int numAp = 75;
    const float desconto = 0.25; 

    float valorDiaria;

    printf("Digite o valor da diaria:\n");
    scanf("%f", &valorDiaria);

  
    float valorDiariaPromo = valorDiaria * (1 - desconto);

    int apOcupados80 = numAp * 0.8;
    int apOcupados50 = numAp * 0.5;

    float valorTotal80 = apOcupados80 * valorDiariaPromo;
    float valorTotal50 = apOcupados50 * valorDiaria;

    float diferenca = valorTotal80 - valorTotal50;

    printf("Valor da diaria promocional: %.2f\n", valorDiariaPromo);
    printf("Valor total com 80%% de ocupacao e diaria promocional: %.2f\n", valorTotal80);
    printf("Valor total com 50%% de ocupacao e diaria normal: %.2f\n", valorTotal50);
    printf("Diferenca entre estes dois valores: %.2f\n", diferenca);

    return 0;
}
