#include <stdio.h>

int main() {
    char opcao;
    double salarioAtual, novoSalario;

    printf("Digite a opção (A, B ou C): ");
    scanf(" %c", &opcao);

    printf("Digite o salário atual do funcionário: ");
    scanf("%lf", &salarioAtual);

    switch (opcao) {
        case 'A':
        case 'a':
            novoSalario = salarioAtual * 1.08;
            break;
        case 'B':
        case 'b':
            novoSalario = salarioAtual * 1.11;
            break;
        case 'C':
        case 'c':
            if (salarioAtual <= 1000) {
                novoSalario = salarioAtual + 350.00;
            } else {
                novoSalario = salarioAtual + 200.00;
            }
            break;
        default:
            printf("Opção inválida.\n");
            return 1;
    }

    printf("Novo salário: R$ %.2lf\n", novoSalario);

    return 0;
}
