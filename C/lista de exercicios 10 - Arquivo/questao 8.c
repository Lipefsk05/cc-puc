#include <stdio.h>

int main() {
    int quantidade_veiculos;
    float valor_aluguel;
    
    // Leitura da quantidade de veículos e valor do aluguel
    printf("Informe a quantidade de veículos da locadora: ");
    scanf("%d", &quantidade_veiculos);
    printf("Informe o valor do aluguel por veículo: R$ ");
    scanf("%f", &valor_aluguel);
    
    // Cálculo do faturamento anual
    float faturamento_anual = (quantidade_veiculos / 3.0) * valor_aluguel * 12;
    
    // Cálculo do valor ganho com multas no mês
    float multa_mes = (quantidade_veiculos / 30.0) * valor_aluguel * 0.2;
    
    // Cálculo do valor gasto com manutenção anual
    float valor_manutencao_anual = (quantidade_veiculos * 0.02) * 600.0;
    
    // Exibindo os resultados na tela
    printf("\n=== Resultados ===\n");
    printf("Faturamento anual da locadora: R$ %.2f\n", faturamento_anual);
    printf("Valor ganho com multas no mês: R$ %.2f\n", multa_mes);
    printf("Valor gasto com manutenção anual: R$ %.2f\n", valor_manutencao_anual);
    
    // Gravando os resultados no arquivo resultado.txt
    FILE *arquivo_resultado = fopen("resultado.txt", "w");
    if (arquivo_resultado == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }
    
    fprintf(arquivo_resultado, "%.2f\n", faturamento_anual);
    fprintf(arquivo_resultado, "%.2f\n", multa_mes);
    fprintf(arquivo_resultado, "%.2f\n", valor_manutencao_anual);
    
    fclose(arquivo_resultado);
    
    printf("\nResultados gravados no arquivo resultado.txt.\n");
    
    return 0;
}
