#include <stdio.h>

void calcular_estatisticas() {
    int num_filhos, total_filhos = 0, num_pessoas = 0;
    float salario, total_salario = 0.0;

    printf("Digite o salário e o número de filhos (ou -1 para terminar):\n");

    while (1) {
        printf("Salário: ");
        scanf("%f", &salario);
        if (salario == -1) break;

        printf("Número de filhos: ");
        scanf("%d", &num_filhos);
        if (num_filhos == -1) break;

        total_salario += salario;
        total_filhos += num_filhos;
        num_pessoas++;
    }

    if (num_pessoas > 0) {
        printf("Média de salário: %.2f\n", total_salario / num_pessoas);
        printf("Média de número de filhos: %.2f\n", (float)total_filhos / num_pessoas);
    } else {
        printf("Nenhum dado foi inserido.\n");
    }
}

int main() {
    calcular_estatisticas();
    return 0;
}
