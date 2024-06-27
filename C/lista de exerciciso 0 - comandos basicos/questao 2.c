#include <stdio.h>

int main() {
    float salario_minimo, kilowatt_consumido;
    float valor_kilowatt, valor_total, valor_com_desconto;

    // Leitura do valor do salário mínimo
    printf("Digite o valor do salário mínimo: ");
    scanf("%f", &salario_minimo);

    // Leitura da quantidade de kilowatt consumida
    printf("Digite a quantidade de kilowatt consumida: ");
    scanf("%f", &kilowatt_consumido);

    // Cálculo do valor de cada kilowatt
    valor_kilowatt = (salario_minimo / 7) / 100;

    // Cálculo do valor total a ser pago
    valor_total = valor_kilowatt * kilowatt_consumido;

    // Cálculo do valor com desconto de 10%
    valor_com_desconto = valor_total * 0.90;

    // Exibição dos resultados
    printf("Valor de cada kilowatt: R$ %.2f\n", valor_kilowatt);
    printf("Valor total a ser pago: R$ %.2f\n", valor_total);
    printf("Valor a ser pago com desconto de 10%%: R$ %.2f\n", valor_com_desconto);

    return 0;
}
