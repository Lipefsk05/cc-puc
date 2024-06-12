#include <stdio.h>

int main() {
    float precoCompra, precoVenda;
    int mercadoriasLucroMenor10 = 0, mercadoriasLucroEntre10e20 = 0, mercadoriasLucroMaior20 = 0;
    float valorTotalCompra = 0, valorTotalVenda = 0, lucroTotal = 0;

    printf("Digite o preço de compra e de venda de cada mercadoria (preço de compra 0 para sair):\n");

    while (1) {
        printf("Preço de compra: ");
        scanf("%f", &precoCompra);

        if (precoCompra == 0) {
            break;
        }

        printf("Preço de venda: ");
        scanf("%f", &precoVenda);

        // Cálculo do lucro
        float lucro = precoVenda - precoCompra;
        float percentualLucro = (lucro / precoCompra) * 100;

        // Atualização dos totais
        valorTotalCompra += precoCompra;
        valorTotalVenda += precoVenda;
        lucroTotal += lucro;

        // Contagem por faixas de lucro
        if (percentualLucro < 10) {
            mercadoriasLucroMenor10++;
        } else if (percentualLucro >= 10 && percentualLucro <= 20) {
            mercadoriasLucroEntre10e20++;
        } else {
            mercadoriasLucroMaior20++;
        }
    }

    // Resultados
    printf("\nResultado:\n");
    printf("Mercadorias com lucro < 10%%: %d\n", mercadoriasLucroMenor10);
    printf("Mercadorias com 10%% <= lucro <= 20%%: %d\n", mercadoriasLucroEntre10e20);
    printf("Mercadorias com lucro > 20%%: %d\n", mercadoriasLucroMaior20);
    printf("\n");
    printf("Valor total de compra: R$%.2f\n", valorTotalCompra);
    printf("Valor total de venda: R$%.2f\n", valorTotalVenda);
    printf("Lucro total: R$%.2f\n", lucroTotal);

    return 0;
}
