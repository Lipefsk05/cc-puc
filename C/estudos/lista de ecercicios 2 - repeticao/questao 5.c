#include <stdio.h>

int main() {
    float salarios[100];
    int num_filhos[100];
    int count = 0;

    // Entrada de dados
    while (1) {
        float salario;
        int filhos;
        
        printf("Digite o salário (ou um valor negativo para encerrar): ");
        scanf("%f", &salario);
        if (salario < 0) {
            break;
        }
        
        printf("Digite o número de filhos: ");
        scanf("%d", &filhos);
        
        salarios[count] = salario;
        num_filhos[count] = filhos;
        count++;
    }

    // Cálculo das estatísticas
    float soma_salarios = 0;
    int soma_filhos = 0;
    float maior_salario = 0;
    int pessoas_ate_100 = 0;
    
    for (int i = 0; i < count; i++) {
        soma_salarios += salarios[i];
        soma_filhos += num_filhos[i];
        if (salarios[i] > maior_salario) {
            maior_salario = salarios[i];
        }
        if (salarios[i] <= 100) {
            pessoas_ate_100++;
        }
    }
    
    float media_salarios = soma_salarios / count;
    float media_filhos = (float)soma_filhos / count;
    float percentual_ate_100 = ((float)pessoas_ate_100 / count) * 100;

    // Exibição dos resultados
    printf("Média do salário da população: R$%.2f\n", media_salarios);
    printf("Média do número de filhos: %.2f\n", media_filhos);
    printf("Maior salário: R$%.2f\n", maior_salario);
    printf("Percentual de pessoas com salário até R$100,00: %.2f%%\n", percentual_ate_100);

    return 0;
}
